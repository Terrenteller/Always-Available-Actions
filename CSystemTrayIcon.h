#ifndef CSYSTEMTRAYICON_H
#define CSYSTEMTRAYICON_H

#include <algorithm>

#include <QtWidgets>

#include "CAlwaysAction.h"
#include "CAlwaysMenu.h"
#include "CBuiltinActionFactory.h"
#include "CProgramSettings.h"
#if WIN32
#include "CShellExecuteActionStep.h"
#endif
#include "CSqueakyMenu.h"

class CSystemTrayIcon : public QSystemTrayIcon
{
	Q_OBJECT

public:
	CSystemTrayIcon( QObject *parent = NULL );
	~CSystemTrayIcon();

public slots:
	void refresh( void );

private slots:
	void buildMenu( const QString &absoluteDirPath , CSqueakyMenu *menu );
	void openApplicationDirectory( void );
	void systemTrayIconActivated( QSystemTrayIcon::ActivationReason reason );

private:
	CSqueakyMenu *trayMenu;
	QList< CAlwaysAction* > allActions;
};

#endif // CSYSTEMTRAYICON_H
