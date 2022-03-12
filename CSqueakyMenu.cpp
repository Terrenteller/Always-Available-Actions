#include "CSqueakyMenu.h"

CSqueakyMenu::CSqueakyMenu( const QString &title , QWidget *parent /* = NULL */ ) : QMenu( title , parent )
{
	// Nothing to do
}

void CSqueakyMenu::mouseReleaseEvent( QMouseEvent *event )
{
	QAction *action = actionAt( event->pos() );
	CSqueakyAction *squeakyAction = qobject_cast< CSqueakyAction* >( action );
	if( squeakyAction )
	{
		squeakyAction->activate( event->button() , event->modifiers() );

#ifdef WIN32
		// Don't call the base implementation after accepting
		// otherwise it will activate the action normally (and for a second time)
		event->accept();
#else
		if( !event->isAccepted() )
			event->accept();

		// The menus close automatically on Windows but not in LXDE (at least).
		// This may still emit QAction::triggered() but we don't listen to it.
		// We've accepted the event, so what gives?
		QMenu::mouseReleaseEvent( event );
#endif

		// Don't emit other signals when we activate the action directly
		return;
	}

	QMenu::mouseReleaseEvent( event );

	switch( event->button() )
	{
		case Qt::LeftButton:
			emit triggered( action );
			emit triggeredLeft( action , event->modifiers() );
			break;
		case Qt::MiddleButton:
			emit triggeredMiddle( action , event->modifiers() );
			break;
		case Qt::RightButton:
			emit triggeredRight( action , event->modifiers() );
			break;
		default: {}
	}

	emit triggeredAny( action , event->button() , event->modifiers() );
}
