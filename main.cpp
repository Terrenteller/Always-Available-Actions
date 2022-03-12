#ifdef WIN32
#include <windows.h>
#endif

#include <QtWidgets>

#include "CArgumentProcessor.h"
#include "CSingleApplication.h"
#include "CSystemTrayIcon.h"

int main( int argc , char *argv[] )
{
	QApplication application( argc , argv );
	application.setWindowIcon( QIcon( ":/resources/icons/SystemTray.png" ) );

	CSingleApplication singleApplication( "AlwaysAvailableActions" );
	if( !singleApplication.claimPrimary() )
	{
		singleApplication.sendArgsToPrimary( argc , argv );
		return 0;
	}

	// Don't allow something trying to send arguments
	// to the primary instance accidentally start the program
	if( argc > 1 )
		return 0;

	CSystemTrayIcon *trayIcon = new CSystemTrayIcon( NULL );
	trayIcon->refresh();

	CBuiltinActionFactory *builtinActions = CBuiltinActionFactory::instance();
	QObject::connect( builtinActions , &CBuiltinActionFactory::refreshed , trayIcon , &CSystemTrayIcon::refresh );

	CArgumentProcessor *argProcessor = CArgumentProcessor::instance();
	QObject::connect(
		&singleApplication,
		&CSingleApplication::argsReceived,
		[=]( QStringList &args )
		{
			argProcessor->process( args );
		} );
	QObject::connect(
		argProcessor,
		&CArgumentProcessor::showMessage,
		[=]( const QString &title , const QString &message )
		{
			trayIcon->showMessage( title , message , QSystemTrayIcon::NoIcon );
		} );
	QObject::connect(
		argProcessor,
		&CArgumentProcessor::showInformation,
		[=]( const QString &title , const QString &message )
		{
			trayIcon->showMessage( title , message , QSystemTrayIcon::Information );
		} );
	QObject::connect(
		argProcessor,
		&CArgumentProcessor::showWarning,
		[=]( const QString &title , const QString &message )
		{
			trayIcon->showMessage( title , message , QSystemTrayIcon::Warning );
		} );
	QObject::connect(
		argProcessor,
		&CArgumentProcessor::showCritical,
		[=]( const QString &title , const QString &message )
		{
			trayIcon->showMessage( title , message , QSystemTrayIcon::Critical );
		} );

#ifdef WIN32
	// Recommended for ShellExecute
	CoInitializeEx( NULL , COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE );
#endif
	int ret = application.exec();
#ifdef WIN32
	CoUninitialize();
#endif

	delete trayIcon;
	return ret;
}
