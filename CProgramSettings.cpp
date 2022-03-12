#include "CProgramSettings.h"

CProgramSettings::CProgramSettings( void )
{
#ifdef WIN32
	// Assume reasonable defaults
	fileBrowser = "explorer.exe";
	textEditor = "notepad.exe";
#endif

	refresh();
}

QString CProgramSettings::getFileBrowser( void ) const
{
	return fileBrowser;
}

QString CProgramSettings::getTextEditor( void ) const
{
	return textEditor;
}

void CProgramSettings::refresh( void )
{
#if WIN32
	QString settingsFilePath = QCoreApplication::applicationDirPath() + "/windows.cfg";
#else
	QString settingsFilePath = QCoreApplication::applicationDirPath() + "/linux.cfg";
#endif

	QList< QPair< QString , QString > > keyValues = Util::readSimpleKeyValueFile( settingsFilePath );
	for( const QPair< QString , QString > &keyValue : qAsConst( keyValues ) )
	{
		QString key = keyValue.first;
		QString value = keyValue.second;
		if( !key.isEmpty() && !value.isEmpty() )
		{
			if( key == "fileBrowser" )
				fileBrowser = value;
			else if( key == "textEditor" )
				textEditor = value;
		}
	}
}
