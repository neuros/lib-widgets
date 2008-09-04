/*
 *  Copyright(C) 2007 Neuros Technology International LLC. 
 *               <www.neurostechnology.com>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 of the License.
 *  
 *
 *  This program is distributed in the hope that, in addition to its 
 *  original purpose to support Neuros hardware, it will be useful 
 *  otherwise, but WITHOUT ANY WARRANTY; without even the implied 
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 ****************************************************************************
 *
 * NlineEdit editbox routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2007-11-21 SZ
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QApplication>
#include "nlineedit.h"
#include "nlineedit_p.h"

NLineEdit::NLineEdit(QWidget *parent)
: QLineEdit(parent), d(new NLineEditPrivate)
{
    setAcceptKeyMode(AcceptAllKey);
}

NLineEdit::NLineEdit(const QString &contents, QWidget *parent)
: QLineEdit(contents, parent), d(new NLineEditPrivate)
{
    setAcceptKeyMode(AcceptAllKey);
}

NLineEdit::~NLineEdit()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

void NLineEdit::setAcceptKeyMode(int akm)
{ 
    d->acceptKeys = akm;
}

int NLineEdit::acceptKeyMode( ) const
{ 
    return d->acceptKeys;
}

void NLineEdit::keyPressEvent(QKeyEvent *e)
{
    if (d->acceptKeys & NLineEdit::AcceptAllKey)
    {
#ifndef DESIGNER
        // FIXME: This piece of code is unnecessary, 
        // should be removed after OSDIrKeyboardHandler class fixed the unicode map issue.
        if ((e->key( ) >= Qt::Key_0) && (e->key( ) <= Qt::Key_9))
            insert(QString('0' + e->key( ) - Qt::Key_0));
#endif
        return QLineEdit::keyPressEvent(e);
    }

    if (d->acceptKeys & NLineEdit::AcceptNumericKey)
    {
        // Key_0, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,
        if ((e->key( ) >= Qt::Key_0) && (e->key( ) <= Qt::Key_9))
        {
#ifndef DESIGNER
            // FIXME: This piece of code is unnecessary, 
            // should be removed after OSDIrKeyboardHandler class fixed the unicode map issue.
            insert(QString('0' + e->key( ) - Qt::Key_0));
#endif
            return QLineEdit::keyPressEvent(e);
        }
    }

    if (d->acceptKeys & NLineEdit::AcceptCursorMoveKey)
    {
        // Key_Home, Key_End, Key_Left, Key_Up, Key_Right, Key_Down,
        // Key_PageUp, Key_PageDown,
        if ((e->key( ) >= Qt::Key_Home) && (e->key( ) <= Qt::Key_PageDown))
            return QLineEdit::keyPressEvent(e);
    }

    if (d->acceptKeys & NLineEdit::AcceptMiscKey)
    {
        // Key_Escape, Key_Tab, Key_Backtab, Key_Backspace, Key_Return,
        // Key_Enter, Key_Insert, Key_Delete, Key_Pause, 
        // Key_Print, Key_SysReq, Key_Clear
        if ((e->key( ) >= Qt::Key_Escape) && (e->key( ) <= Qt::Key_Clear))
        {
            if (e->key( ) == Qt::Key_Clear)
            {
                //For Neuros OSD IR remote controller, Convert the clear key (#) to Key_Backspace
                QKeyEvent bsKeyEvent(e->type( ), Qt::Key_Backspace, e->modifiers( ), 
                                     e->text( ), e->isAutoRepeat( ), e->count( ));
                return QLineEdit::keyPressEvent(&bsKeyEvent);
            }
            else
            {
                return QLineEdit::keyPressEvent(e);
            }
        }
    }
}

/*
 *This method is only relevant for input widgets.
 * It is used by the input method to query a set of properties of the widget
 * to be able to support complex input method operations 
 * as support for surrounding text and reconversions.
 */
QVariant NLineEdit::inputMethodQuery(Qt::InputMethodQuery query) const
{
    if (Qt::ImCurrentSelection == query) //FIXME: Is there a better way to go?
        return QStringList( ) << selectedText( ) << toolTip( );
    else
        return QLineEdit::inputMethodQuery(query);
}

/*
 * Reimplemented to receive Input Method composition events.
 * This handler is called when the state of the input method changes.
 * Note that when creating custom text editing widgets, 
 * the Qt::WA_InputMethodEnabled window attribute must be set explicitly in order to receive input method events.
 */
void NLineEdit::inputMethodEvent(QInputMethodEvent *ime)
{
    QLineEdit::inputMethodEvent(ime);

    //FIXME: why send application a ENTER key event?
    QKeyEvent keyEvent = QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
    QApplication::sendEvent(this, &keyEvent);
}




NLineEditPrivate::NLineEditPrivate()
{
}

NLineEditPrivate::~NLineEditPrivate()
{
}
