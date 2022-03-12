#include "CAlwaysAction.h"

CAlwaysAction::CAlwaysAction( const QString &absoluteSourcePath )
{
	setSourcePath( absoluteSourcePath );
	setEditable( true );

	CProgramActionStep *curStep = NULL;
	bool lastStepExplicitlySynchronous = false; // FIXME: This is terrible. Clean it up.

	QList< QPair< QString , QString > > keyValues = Util::readSimpleKeyValueFile( absoluteSourcePath );
	for( const QPair< QString , QString > &keyValue : qAsConst( keyValues ) )
	{
		QString key = keyValue.first;
		QString value = keyValue.second;
		if( !key.isEmpty() )
		{
			if( key == "name" )
			{
				setDisplayName( value );
			}
			else if( key == "platforms" )
			{
				setPlatforms( value.split( ' ' , QString::SkipEmptyParts ) );
			}
			else if( key == "program" )
			{
				if( curStep )
				{
					appendStep( curStep );
					lastStepExplicitlySynchronous = false;
				}

				curStep = new CProgramActionStep( value );
			}
			else if( key == "arg" )
			{
				if( curStep )
					curStep->addArg( value );
			}
			else if( key == "silent" )
			{
				if( curStep )
					curStep->setSilent( Util::isStringTrueOrEmpty( value ) );
			}
			else if( key == "async" )
			{
				if( curStep )
				{
					bool async = Util::isStringTrueOrEmpty( value );
					lastStepExplicitlySynchronous = async == false;
					curStep->setAsync( async );
				}
			}
#if 0
			// TODO: Disabled until actions are threaded and long waits won't freeze the GUI
			else if( key == "timeout" )
			{
				bool ok = false;
				int timeoutMillis = value.toInt( &ok );
				if( ok )
					curStep->setTimeoutMillis( timeoutMillis );
			}
#endif
		}
	}

	if( curStep )
	{
		curStep->setAsync( !lastStepExplicitlySynchronous );
		appendStep( curStep );
	}
}

CAlwaysAction::~CAlwaysAction()
{
	for( int index = 0 ; index < actionSteps.count() ; index++ )
		delete actionSteps[ index ];
}

bool CAlwaysAction::isValid( void ) const
{
	bool invalid = displayName.isEmpty()
		|| !actionSteps.count()
	#ifdef WIN32
		|| ( !platforms.isEmpty() && !platforms.contains( "windows" , Qt::CaseInsensitive ) );
	#else
		|| ( !platforms.isEmpty() && !platforms.contains( "linux" , Qt::CaseInsensitive ) );
	#endif

	return !invalid;
}

QString CAlwaysAction::getSourcePath( void ) const
{
	return sourcePath;
}

void CAlwaysAction::setSourcePath( const QString &absoluteSourcePath )
{
	QFileInfo fileInfo( absoluteSourcePath );
	if( fileInfo.isAbsolute() )
		sourcePath = fileInfo.absoluteFilePath();
}

bool CAlwaysAction::isEditable( void ) const
{
	return editable;
}

void CAlwaysAction::setEditable( bool editable )
{
	this->editable = editable;
}

QString CAlwaysAction::getDisplayName( void ) const
{
	return displayName;
}

void CAlwaysAction::setDisplayName( const QString &name )
{
	this->displayName = name;
}

QStringList CAlwaysAction::getPlatforms( void ) const
{
	return platforms;
}

void CAlwaysAction::setPlatforms( const QStringList &platforms )
{
	this->platforms = platforms;
}

void CAlwaysAction::appendStep( IActionStep *step )
{
	actionSteps.append( step );
}

CSqueakyAction* CAlwaysAction::createAction( void )
{
	CSqueakyAction *action = new CSqueakyAction( displayName , NULL );
	connect( action , &CSqueakyAction::triggeredLeft , this , &CAlwaysAction::executeSteps );
	connect( action , &CSqueakyAction::triggeredMiddle , this , &CAlwaysAction::openSourcePath );

	return action;
}

void CAlwaysAction::executeSteps( void )
{
	// TODO: Execute steps in another thread so we can wait for finished without freezing the GUI.
	// In the meantime, put expensive/complicated actions in a script for a the last step.
	// Bonus points if we can defer detachment until AAA exit so we can report more exit codes.
	QDir workingDirectory( getSourcePath() );
	QFileInfo actionInfo( getSourcePath() );
	if( actionInfo.isFile() )
		workingDirectory.cdUp();

	for( int index = 0 ; index < actionSteps.count() ; index++ )
	{
		int exitCode = actionSteps.at( index )->execute( workingDirectory );
		if( exitCode != 0 )
		{
			QString message = QString( "Step %1 exited with code %2" ).arg( index ).arg( exitCode );

			if( exitCode < 0 )
				emit CArgumentProcessor::instance()->showCritical( getDisplayName() , message );
			else
				emit CArgumentProcessor::instance()->showWarning( getDisplayName() , message );

			break;
		}
	}
}

void CAlwaysAction::openSourcePath( void )
{
	QString absoluteEditPath = QDir::toNativeSeparators( getSourcePath() );
	QFileInfo fileInfo( absoluteEditPath );
	if( fileInfo.isSymLink() || fileInfo.isDir() )
		Util::startDetached( CProgramSettings::instance()->getFileBrowser() , absoluteEditPath );
	else if( fileInfo.isFile() )
		Util::startDetached( CProgramSettings::instance()->getTextEditor() , absoluteEditPath );
}
