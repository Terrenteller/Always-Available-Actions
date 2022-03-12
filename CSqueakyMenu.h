#ifndef CSQUEAKYMENU_H
#define CSQUEAKYMENU_H

#include <QtWidgets>

#include "CSqueakyAction.h"

class CSqueakyMenu : public QMenu
{
	Q_OBJECT

public:
	CSqueakyMenu( const QString &title , QWidget *parent = NULL );

protected: // QMenu
	void mouseReleaseEvent( QMouseEvent *event ) override;

signals:
	void triggeredAny( QAction *action , Qt::MouseButton mouseButton , Qt::KeyboardModifiers keyboardModifiers );
	void triggeredLeft( QAction *action , Qt::KeyboardModifiers keyboardModifiers );
	void triggeredMiddle( QAction *action , Qt::KeyboardModifiers keyboardModifiers );
	void triggeredRight( QAction *action , Qt::KeyboardModifiers keyboardModifiers );
};

#endif // CSQUEAKYMENU_H
