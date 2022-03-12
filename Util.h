#ifndef UTIL_H
#define UTIL_H

#include <QtCore>

namespace Util
{
	QList< QPair< QString , QString > > readSimpleKeyValueFile( const QString &absoluteFilePath );

	bool isStringTrue( const QString &value );
	bool isStringTrueOrEmpty( const QString &value );
	bool isStringFalse( const QString &value );
	bool isStringFalseOrEmpty( const QString &value );

	bool startDetached( const QString &program , const QStringList &args );
	bool startDetached( const QString &program , const QString &arg );
}

#endif // UTIL_H
