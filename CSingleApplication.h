// Credits: https://stackoverflow.com/a/28172162

#ifndef CSINGLEAPPLICATION_H
#define CSINGLEAPPLICATION_H

#include <iostream>

#include <QtCore>
#include <QtNetwork>

class CSingleApplication : public QObject
{
	Q_OBJECT

public:
	CSingleApplication( const QString& applicationKey );
	Q_DISABLE_COPY( CSingleApplication )
	~CSingleApplication();

public:
	bool isRunning( void );
	bool isPrimary( void );
	bool claimPrimary( void );
	void release( void );
	bool sendArgsToPrimary( int argc , char *argv[] );

protected:
	bool sendArgsToPrimary( const QStringList &args );

private slots:
	QByteArray serializeArgs( const QStringList &args );
	QStringList unserializeArgs( QByteArray &data );
	void onNewConnection( void );

signals:
	void argsReceived( QStringList &args );

private:
	const QString applicationKey;
	const QString memLockKey;
	const QString sharedMemKey;

	QSharedMemory sharedMem;
	QSystemSemaphore memLock;

	bool primary;
	unsigned short port;
	QTcpServer server;
};


#endif // CSINGLEAPPLICATION_H
