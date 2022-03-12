#include "CProgramActionStep.h"

CProgramActionStep::CProgramActionStep( const QString &program , const QStringList &args /* = QStringList() */ )
{
	this->program = program;
	this->args = args;

	silent = false;
	async = false;
	timeoutMillis = 3000;
}

CProgramActionStep::CProgramActionStep( const QString &program , const QString &arg ) : CProgramActionStep( program , QStringList( arg ) )
{
	// Nothing to do
}

CProgramActionStep::~CProgramActionStep()
{
	// Nothing to do
}

QStringList CProgramActionStep::getArgs( void ) const
{
	return args;
}

void CProgramActionStep::setArgs( const QStringList &args )
{
	this->args = args;
}

void CProgramActionStep::addArg( const QString &arg )
{
	args.append( arg );
}

bool CProgramActionStep::isSilent( void ) const
{
	return silent;
}

void CProgramActionStep::setSilent( bool silent )
{
	this->silent = silent;
}

bool CProgramActionStep::isAsync( void ) const
{
	return async;
}

void CProgramActionStep::setAsync( bool async )
{
	this->async = async;
}

int CProgramActionStep::getTimeoutMillis( void ) const
{
	return timeoutMillis;
}

void CProgramActionStep::setTimeoutMillis( int timeoutMillis )
{
	this->timeoutMillis = timeoutMillis;
}

int CProgramActionStep::execute( const QDir &workingDirectory )
{
	QProcess process;
	process.setWorkingDirectory( workingDirectory.absolutePath() );
	process.setProgram( program );
	process.setArguments( args );
#ifdef WIN32
	// https://docs.microsoft.com/en-us/windows/console/creation-of-a-console
	process.setCreateProcessArgumentsModifier( [=]( QProcess::CreateProcessArguments *args ) {
		args->flags |= async && !silent ? CREATE_NEW_CONSOLE : 0;
		args->startupInfo->dwFlags &=~ STARTF_USESTDHANDLES;
	});
#endif

	if( async )
	{
		process.startDetached();
		return 0;
	}

	process.start();
	if( process.waitForFinished( timeoutMillis ) )
		return silent ? 0 : process.exitCode();

#ifdef WIN32
	return WAIT_TIMEOUT;
#else
	return ETIME;
#endif
}
