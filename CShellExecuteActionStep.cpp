#include "CShellExecuteActionStep.h"

CShellExecuteActionStep::CShellExecuteActionStep( const QString &operation , const QString &file , const QString &parameters , const QString &directory , int showCommand /* = SW_SHOWNORMAL */ )
{
	this->operation = operation;
	this->file = file;
	this->parameters = parameters;
	this->directory = directory;
	this->showCommand = showCommand;
}

CShellExecuteActionStep::~CShellExecuteActionStep()
{
	// Nothing to do
}

int CShellExecuteActionStep::execute( const QDir &workingDirectory )
{
	Q_UNUSED( workingDirectory )

	std::wstring wideOperation = operation.toStdWString();
	std::wstring wideFile = file.toStdWString();
	std::wstring wideParameters = parameters.toStdWString();
	std::wstring wideDirectory = directory.toStdWString();
	ShellExecuteW( NULL , wideOperation.data() , wideFile.data() , wideParameters.data() , wideDirectory.data() , showCommand );

	return 0;
}
