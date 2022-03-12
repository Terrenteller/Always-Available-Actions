#include "CAlwaysMenu.h"

CAlwaysMenu::CAlwaysMenu( const QString &title /* = QString() */ , QWidget *parent /* = NULL */ ) : CSqueakyMenu( title , parent )
{
	connect( this , &CSqueakyMenu::triggeredMiddle , this , &CAlwaysMenu::openDirectory );
}

QString CAlwaysMenu::getDirectoryPath( void )
{
	return dirPath;
}

void CAlwaysMenu::setDirectoryPath( const QString &dirPath )
{
	this->dirPath = dirPath;
}

void CAlwaysMenu::openDirectory( void )
{
	Util::startDetached( CProgramSettings::instance()->getFileBrowser() , getDirectoryPath() );
}
