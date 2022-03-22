#include "CSystemTrayIcon.h"

namespace
{

bool compareMenus( QMenu *first , QMenu *second )
{
	return QString::compare( first->title() , second->title() , Qt::CaseInsensitive ) <= 0;
}

bool compareActions( QAction *first , QAction *second )
{
	return QString::compare( first->iconText() , second->iconText() , Qt::CaseInsensitive ) <= 0;
}

} // ::

CSystemTrayIcon::CSystemTrayIcon( QObject *parent /* = NULL */ )
{
	Q_UNUSED( parent )

	trayMenu = new CSqueakyMenu( "AAA" , NULL );

	setIcon( QIcon( ":/resources/icons/SystemTray.png" ) );
	connect( this , &QSystemTrayIcon::activated , this , &CSystemTrayIcon::systemTrayIconActivated );

	show(); // The icon will not respond to user interaction otherwise, regardless of appearance
}

CSystemTrayIcon::~CSystemTrayIcon()
{
	for( CAlwaysAction *action : qAsConst( allActions ) )
		delete action;
	allActions.clear();

	delete trayMenu;
}

void CSystemTrayIcon::refresh( void )
{
	trayMenu->clear();
	for( CAlwaysAction *action : qAsConst( allActions ) )
		delete action;
	allActions.clear();

	trayMenu->setTearOffEnabled( true );
	buildMenu( QCoreApplication::applicationDirPath() + "/actions" , trayMenu );
	trayMenu->addSeparator();
	trayMenu->addAction( CBuiltinActionFactory::instance()->createRefreshAction() );
	//actionMenu->addAction( CSharedActionFactory::instance()->createConfigureAction() );
	trayMenu->addAction( CBuiltinActionFactory::instance()->createExitAction() );
}

void CSystemTrayIcon::buildMenu( const QString &absoluteDirPath , CSqueakyMenu *menu )
{
	QDir dir( absoluteDirPath );
	dir.setFilter( QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoDotAndDotDot );
	if( !dir.isAbsolute() )
		return;

	QFileInfoList fileInfos = dir.entryInfoList();
	QList< QMenu* > subDirMenus;
	QList< QAction* > actions;

	for( const QFileInfo &fileInfo : qAsConst( fileInfos ) )
	{
		QString absoluteFilePath = QDir::toNativeSeparators( fileInfo.absoluteFilePath() );
		CAlwaysMenu *subDirMenu = NULL;
		CAlwaysAction *action = NULL;

		if( fileInfo.isSymLink() )
		{
			// Handle symlinks first since they could be a file or directory
#ifdef WIN32
			// symlinks are shortcuts on Windows
			CShellExecuteActionStep *step = new CShellExecuteActionStep( "open" , absoluteFilePath , "" , "" );

			action = new CAlwaysAction( absoluteFilePath );
			action->setDisplayName( fileInfo.baseName() );
			action->setEditable( false );
			action->appendStep( step );
#else
			QFileInfo symLinkTargetInfo( fileInfo.symLinkTarget() );
			if( symLinkTargetInfo.isDir() )
			{
				QString program = CProgramSettings::instance()->getFileBrowser();
				QString arg = symLinkTargetInfo.absoluteFilePath();
				CProgramActionStep *step = new CProgramActionStep( program , arg );

				action = new CAlwaysAction( absoluteFilePath );
				action->setDisplayName( fileInfo.fileName() );
				action->setEditable( false );
				action->appendStep( step );
			}
#endif
		}
		else if( fileInfo.isFile() )
		{
			if( fileInfo.fileName().endsWith( ".aaa" ) )
				action = new CAlwaysAction( absoluteFilePath );
		}
		else if( fileInfo.isDir() )
		{
			subDirMenu = new CAlwaysMenu( fileInfo.fileName() , NULL );
			subDirMenu->setDirectoryPath( absoluteFilePath );
			buildMenu( absoluteFilePath , subDirMenu );
		}

		if( subDirMenu )
		{
			// FIXME: LXDE doesn't respect either of these for tear-off menus.
			// Or do tear-off menus not copy the attributes and flags?
			//subDirMenu->setAttribute( Qt::WA_AlwaysStackOnTop , true );
			//subDirMenu->setWindowFlag( Qt::WindowStaysOnTopHint , true );

			if( subDirMenu->actions().length() )
				subDirMenus.append( subDirMenu );
			else
				delete subDirMenu;

			subDirMenu = NULL;
		}

		if( action )
		{
			if( action->isValid() )
			{
				actions.append( action->createAction() );
				allActions.append( action );
			}
			else
				delete action;

			action = NULL;
		}
	}

	if( subDirMenus.count() )
	{
		std::sort( subDirMenus.begin() , subDirMenus.end() , compareMenus );
		for( QMenu *subDirMenu : qAsConst( subDirMenus ) )
			menu->addMenu( subDirMenu );
	}

	if( actions.count() )
	{
		std::sort( actions.begin() , actions.end() , compareActions );
		menu->addActions( actions );
	}

	// TODO: Show documentation? Open the actions directory?
	if( !subDirMenus.count() && !actions.count() && menu == trayMenu )
		menu->addAction( "Empty" )->setDisabled( true );
}

void CSystemTrayIcon::systemTrayIconActivated( QSystemTrayIcon::ActivationReason reason )
{
	switch( reason )
	{
		case QSystemTrayIcon::Trigger:
		case QSystemTrayIcon::Context:
			trayMenu->popup( QCursor::pos() );
			break;
		case QSystemTrayIcon::MiddleClick:
			openApplicationDirectory();
			break;
		default: {}
	}
}

void CSystemTrayIcon::openApplicationDirectory( void )
{
	QString path = QDir::toNativeSeparators( QCoreApplication::applicationDirPath() );
	Util::startDetached( CProgramSettings::instance()->getFileBrowser() , path );
}
