#ifndef CARGUMENTPROCESSOR_H
#define CARGUMENTPROCESSOR_H

#include <QtCore>

class CArgumentProcessor : public QObject
{
	Q_OBJECT

private:
	CArgumentProcessor( void );

public:
	void process( const QStringList &args );

signals:
	void showMessage( const QString &title , const QString &message );
	void showInformation( const QString &title , const QString &message );
	void showWarning( const QString &title , const QString &message );
	void showCritical( const QString &title , const QString &message );

public:
	static CArgumentProcessor* instance( void )
	{
		static CArgumentProcessor *instance = new CArgumentProcessor();
		return instance;
	}
};

#endif // CARGUMENTPROCESSOR_H
