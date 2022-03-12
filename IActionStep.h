#ifndef IACTIONSTEP_H
#define IACTIONSTEP_H

#include <QtCore>

class IActionStep
{
public:
	IActionStep( void );
	virtual ~IActionStep();

public:
	virtual int execute( const QDir &workingDirectory ) = 0;
};

#endif // IACTIONSTEP_H
