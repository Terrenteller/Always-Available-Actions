#ifndef CPROGRAMSETTINGS_H
#define CPROGRAMSETTINGS_H

#include <QtCore>
#include <QtWidgets>

#include "Util.h"

class CProgramSettings : public QObject
{
	Q_OBJECT

private:
	CProgramSettings( void );

public:
	QString getFileBrowser( void ) const;
	QString getTextEditor( void ) const;

public slots:
	void refresh( void );

private:
	QString fileBrowser;
	QString textEditor;

public:
	static CProgramSettings* instance( void )
	{
		static CProgramSettings *instance = new CProgramSettings();
		return instance;
	}
};

#endif // CPROGRAMSETTINGS_H
