#ifndef CALWAYSACTION_H
#define CALWAYSACTION_H

#include <iostream>

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "CArgumentProcessor.h"
#include "CProgramActionStep.h"
#include "CProgramSettings.h"
#include "CSqueakyAction.h"
#include "Util.h"

class CAlwaysAction : public QObject
{
	Q_OBJECT

public:
	CAlwaysAction( const QString &absoluteFilePath );
	~CAlwaysAction();

public:
	bool isValid( void ) const;

	QString getSourcePath( void ) const;
	void setSourcePath( const QString &absoluteSourcePath );

	bool isEditable( void ) const;
	void setEditable( bool editable );

	QString getDisplayName( void ) const;
	void setDisplayName( const QString &name );

	QStringList getPlatforms( void ) const;
	void setPlatforms( const QStringList &platforms );

	void appendStep( IActionStep *step );

	CSqueakyAction* createAction( void );

private slots:
	void executeSteps( void );
	void openSourcePath( void );

private:
	QString sourcePath;
	bool editable;
	QString displayName;
	// TODO: QIcon from executable if Windows?
	QStringList platforms;
	QList< IActionStep* > actionSteps;
};

#endif // CALWAYSACTION_H
