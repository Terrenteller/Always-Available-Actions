#ifndef CALWAYSMENU_H
#define CALWAYSMENU_H

#include "CProgramSettings.h"
#include "CSqueakyMenu.h"
#include "Util.h"

class CAlwaysMenu : public CSqueakyMenu
{
public:
	CAlwaysMenu( const QString &title = QString() , QWidget *parent = NULL );

public:
	QString getDirectoryPath( void );
	void setDirectoryPath( const QString &dirPath );

private slots:
	void openDirectory( void );

protected:
	QString dirPath;
};

#endif // CALWAYSMENU_H
