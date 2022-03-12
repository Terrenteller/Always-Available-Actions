#include "Util.h"

namespace Util
{

QList< QPair< QString , QString > > readSimpleKeyValueFile( const QString &absoluteFilePath )
{
	QList< QPair< QString , QString > > keyValues;
	if( !QDir::isAbsolutePath( absoluteFilePath ) )
		return keyValues;

	QFile file;
	file.setFileName( absoluteFilePath );
	if( !file.open( QIODevice::ReadOnly ) )
		return keyValues;

	QTextStream textStream( &file );
	while( !textStream.atEnd() )
	{
		QString key , value , line = textStream.readLine();
		int splitPos = line.indexOf( ' ' );
		if( splitPos != -1 )
		{
			key = line.left( splitPos );
			value = line.mid( splitPos + 1 );
		}
		else
			key = line;

		keyValues.append( QPair< QString , QString >( key , value ) );
	}

	file.close();
	return keyValues;
}

bool isStringTrue( const QString &value )
{
	return value == "1"
		|| QString::compare( value , "y" , Qt::CaseInsensitive ) == 0
		|| QString::compare( value , "yes" , Qt::CaseInsensitive ) == 0
		|| QString::compare( value , "true" , Qt::CaseInsensitive ) == 0
		|| QString::compare( value , "on" , Qt::CaseInsensitive ) == 0;
}

bool isStringTrueOrEmpty( const QString &value )
{
	return value.isEmpty() || isStringTrue( value );
}

bool isStringFalse( const QString &value )
{
	return !isStringTrue( value );
}

bool isStringFalseOrEmpty( const QString &value )
{
	return value.isEmpty() || isStringFalse( value );
}

bool startDetached( const QString &program , const QStringList &args )
{
	if( program.isEmpty() )
		return false;

	QProcess process;
	process.setProgram( program );
	process.setArguments( args );
	return process.startDetached();
}

bool startDetached( const QString &program , const QString &arg )
{
	return startDetached( program , QStringList( arg ) );
}

} // Util::
