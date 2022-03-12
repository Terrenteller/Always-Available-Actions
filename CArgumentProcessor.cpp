#include "CArgumentProcessor.h"

CArgumentProcessor::CArgumentProcessor( void )
{
	// Nothing to do
}

void CArgumentProcessor::process( const QStringList &args )
{
	for( int index = 0 ; index < args.length() ; )
	{
		QString arg = args.at( index );
		if( arg.startsWith( "--" ) )
		{
			if( arg == "--show-message" )
			{
				if( index + 2 >= args.length() )
					return;

				emit showMessage( args.at( index + 1 ) , args.at( index + 2 ) );
				index += 2;
			}
			else if( arg == "--show-information" )
			{
				if( index + 2 >= args.length() )
					return;

				emit showInformation( args.at( index + 1 ) , args.at( index + 2 ) );
				index += 2;
			}
			else if( arg == "--show-warning" )
			{
				if( index + 2 >= args.length() )
					return;

				emit showWarning( args.at( index + 1 ) , args.at( index + 2 ) );
				index += 2;
			}
			else if( arg == "--show-critical" )
			{
				if( index + 2 < args.length() )
					return;

				emit showCritical( args.at( index + 1 ) , args.at( index + 2 ) );
				index += 2;
			}
			else
				index++;
		}
		else
			index++;
	}
}
