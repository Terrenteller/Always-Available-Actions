#ifndef CSQUEAKYACTION_H
#define CSQUEAKYACTION_H

#include <QtGui>
#include <QtWidgets>

class CSqueakyAction : public QAction
{
	Q_OBJECT

public:
	CSqueakyAction( const QString &iconText , QObject *parent = NULL );

public slots:
	virtual void activate( Qt::MouseButton mouseButton = Qt::NoButton , Qt::KeyboardModifiers keyboardModifiers = Qt::NoModifier );

signals:
	void triggeredAny( Qt::MouseButton mouseButton , Qt::KeyboardModifiers keyboardModifiers , bool checked );
	void triggeredLeft( Qt::KeyboardModifiers keyboardModifiers , bool checked );
	void triggeredMiddle( Qt::KeyboardModifiers keyboardModifiers , bool checked );
	void triggeredRight( Qt::KeyboardModifiers keyboardModifiers , bool checked );
};

#endif // CSQUEAKYACTION_H
