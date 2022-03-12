#ifndef CPROGRAMACTIONSTEP_H
#define CPROGRAMACTIONSTEP_H

#ifdef WIN32
#include <windows.h>
#else
#include <errno.h>
#endif

#include <QtCore>

#include "IActionStep.h"

class CProgramActionStep : public IActionStep
{
public:
	CProgramActionStep( const QString &program , const QStringList &args = QStringList() );
	CProgramActionStep( const QString &program , const QString &arg );
	~CProgramActionStep();

public:
	QStringList getArgs( void ) const;
	void setArgs( const QStringList &args );
	void addArg( const QString &arg );

	bool isSilent( void ) const;
	void setSilent( bool silent );

	bool isAsync( void ) const;
	void setAsync( bool async );

	int getTimeoutMillis( void ) const;
	void setTimeoutMillis( int timeoutMillis );

public: // IActionStep
	virtual int execute( const QDir &workingDirectory ) override;

protected:
	QString program;
	QStringList args;
	bool silent;
	bool async;
	int timeoutMillis;
};

#endif // CPROGRAMACTIONSTEP_H
