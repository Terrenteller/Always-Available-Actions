#include "CSingleApplication.h"

#include <QCryptographicHash>

namespace
{

QString generateKeyHash( const QString& key, const QString& salt )
{
	QByteArray data;

	data.append( key.toUtf8() );
	data.append( salt.toUtf8() );
	return QCryptographicHash::hash( data, QCryptographicHash::Sha1 ).toHex();
}

} // ::

CSingleApplication::CSingleApplication( const QString& key )
	: applicationKey( key )
	, memLockKey( generateKeyHash( key, "_memLockKey" ) )
	, sharedMemKey( generateKeyHash( key, "_sharedmemKey" ) )
	, sharedMem( sharedMemKey )
	, memLock( memLockKey, 1 )
{
	primary = false;
	port = 0;

	memLock.acquire();
	{
		// Fix for *nix: http://habrahabr.ru/post/173281/
		QSharedMemory fix( sharedMemKey );
		fix.attach();
	}
	memLock.release();
}

CSingleApplication::~CSingleApplication()
{
	release();
}

bool CSingleApplication::isRunning( void )
{
	memLock.acquire();
	const bool isRunning = sharedMem.isAttached() || sharedMem.attach();
	if( isRunning )
	{
		port = *(unsigned short*)sharedMem.data();
		sharedMem.detach();
	}
	memLock.release();

	return isRunning;
}

bool CSingleApplication::isPrimary( void )
{
	return primary;
}

bool CSingleApplication::claimPrimary( void )
{
	if( isRunning() )
		return primary;

	memLock.acquire();
	primary = sharedMem.create( sizeof( unsigned short ) );
	*(unsigned short*)sharedMem.data() = 0;
	if( primary && server.listen( QHostAddress::LocalHost ) )
	{
		*(unsigned short*)sharedMem.data() = server.serverPort();
		connect( &server , &QTcpServer::newConnection , this , &CSingleApplication::onNewConnection );
	}
	memLock.release();
	if( !primary )
		release();

	return primary;
}

void CSingleApplication::release( void )
{
	memLock.acquire();
	if( sharedMem.isAttached() )
		sharedMem.detach();
	primary = false;
	server.close();
	memLock.release();
}

bool CSingleApplication::sendArgsToPrimary( int argc , char *argv[] )
{
	QStringList args;
	// First argument is the program name
	for( int index = 1 ; index < argc ; index++ )
		args << QString( argv[ index ] );

	return sendArgsToPrimary( args );
}

bool CSingleApplication::sendArgsToPrimary( const QStringList &args )
{
	if( !port )
		return false;

	QTcpSocket socket( NULL );
	socket.connectToHost( QHostAddress::LocalHost , port );

	if( !socket.waitForConnected( 5000 ) )
		return false;

	QByteArray data = serializeArgs( args );
	bool ok = socket.write( data ) == data.length();
	socket.flush();
	socket.close();

	return ok;
}

QByteArray CSingleApplication::serializeArgs( const QStringList &args )
{
	QByteArray data;
	QBuffer buffer( &data );
	buffer.open( QIODevice::WriteOnly );
	QDataStream stream;
	stream.setDevice( &buffer );
	stream << args;

	return data;
}

QStringList CSingleApplication::unserializeArgs( QByteArray &data )
{
	QBuffer buffer( &data );
	buffer.open( QIODevice::ReadOnly );
	QDataStream stream;
	stream.setDevice( &buffer );
	QStringList args;
	stream >> args;

	return args;
}

void CSingleApplication::onNewConnection( void )
{
	while( server.hasPendingConnections() )
	{
		QTcpSocket *client = server.nextPendingConnection();
		connect(
			client,
			&QIODevice::readyRead,
			[=]( void )
			{
				QByteArray data = client->readAll();
				QStringList args = unserializeArgs( data );
				emit argsReceived( args );
			} );
		connect( client , &QAbstractSocket::disconnected , client , &QObject::deleteLater );
	}
}
