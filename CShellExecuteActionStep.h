#ifndef CSHELLEXECUTEACTIONSTEP_H
#define CSHELLEXECUTEACTIONSTEP_H

#include <string.h>
#include <windows.h>

#include <QtCore>

#include "IActionStep.h"

// https://docs.microsoft.com/en-us/windows/desktop/api/shellapi/nf-shellapi-shellexecutea
class CShellExecuteActionStep : public IActionStep
{
public:
	CShellExecuteActionStep( const QString &operation , const QString &file , const QString &parameters , const QString &directory , int showCommand = SW_SHOWNORMAL );
	~CShellExecuteActionStep() override;

public: // IActionStep
	virtual int execute( const QDir &workingDirectory ) override;

private:
	QString operation , file , parameters , directory;
	int showCommand;
};

#endif // CSHELLEXECUTEACTIONSTEP_H
