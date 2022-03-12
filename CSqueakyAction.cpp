#include "CSqueakyAction.h"

CSqueakyAction::CSqueakyAction( const QString &iconText , QObject *parent /* = NULL */ ) : QAction( iconText , parent )
{
	// Nothing to do
}

void CSqueakyAction::activate( Qt::MouseButton mouseButton /* = Qt::NoButton */ , Qt::KeyboardModifiers keyboardModifiers /* = Qt::NoModifier */ )
{
	switch( mouseButton )
	{
		case Qt::LeftButton:
			emit triggeredLeft( keyboardModifiers , isChecked() );
			break;
		case Qt::MiddleButton:
			emit triggeredMiddle( keyboardModifiers , isChecked() );
			break;
		case Qt::RightButton:
			emit triggeredRight( keyboardModifiers , isChecked() );
			break;
		default: {}
	}

	emit triggeredAny( mouseButton , keyboardModifiers , isChecked() );
}
