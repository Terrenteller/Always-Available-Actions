#ifndef CBUILTINACTIONFACTORY_H
#define CBUILTINACTIONFACTORY_H

#include <Qt>
#include <QtWidgets>

#include "CProgramSettings.h"
#include "Util.h"

class CBuiltinActionFactory : public QObject
{
	Q_OBJECT

private:
	CBuiltinActionFactory( void );

public:
	QAction* createRefreshAction( void );
	QAction* createConfigureAction( void );
	QAction* createExitAction( void );

protected slots:
	void refresh( void );
	void configure( void );
	void exit( void );

signals:
	void refreshed( void );

public:
	static CBuiltinActionFactory* instance( void )
	{
		static CBuiltinActionFactory* instance = new CBuiltinActionFactory();
		return instance;
	}
};

#endif // CBUILTINACTIONFACTORY_H
