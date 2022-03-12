#include "CBuiltinActionFactory.h"

CBuiltinActionFactory::CBuiltinActionFactory()
{
	// Nothing to do
}

QAction* CBuiltinActionFactory::createRefreshAction( void )
{
	QAction *refreshAction = new QAction( "Refresh" , NULL );
	connect( refreshAction , &QAction::triggered , this , &CBuiltinActionFactory::refresh );

	return refreshAction;
}

QAction* CBuiltinActionFactory::createConfigureAction( void )
{
	QAction *configureAction = new QAction( "Configure" , NULL );
	configureAction->setEnabled( !CProgramSettings::instance()->getFileBrowser().isEmpty() );
	connect( configureAction , &QAction::triggered , this , &CBuiltinActionFactory::configure );

	return configureAction;
}

QAction* CBuiltinActionFactory::createExitAction( void )
{
	QAction *exitAction = new QAction( "Exit" , NULL );
	connect( exitAction , &QAction::triggered , this , &CBuiltinActionFactory::exit );

	return exitAction;
}

void CBuiltinActionFactory::refresh( void )
{
	CProgramSettings::instance()->refresh();
	emit refreshed();
}

void CBuiltinActionFactory::configure( void )
{
	// TODO: Simple dialog?
}

void CBuiltinActionFactory::exit( void )
{
	QCoreApplication::instance()->exit( 0 );
}
