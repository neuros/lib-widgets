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
 * NSpinBox implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-22 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QKeyEvent>
#include "nhorizontalcombobox.h"

NHorizontalComboBox::NHorizontalComboBox(QWidget *parent)
: QComboBox(parent)
{
    setWrapping(true);
    setPlayRole(PlayAsComboBox);
}

void NHorizontalComboBox::setPlayRole(PlayRole pr)
{
    if (pr == role)
        return;

    role = pr;
    switch (role)
    {
    case PlayAsComboBox:
        setEditable(false);
        break;
    case PlayAsSpinBox:
        setEditable(true);
        break;
    default:
        break;
    }
}

void NHorizontalComboBox::keyPressEvent(QKeyEvent *e)
{
    switch (e->key( ))
    {
    case Qt::Key_Clear:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        {
            // Convert Keys
            int convertedKey = e->key( );
            switch (e->key( ))
            {
            case Qt::Key_Clear:
                // Clear => Backspace
                convertedKey = Qt::Key_Backspace;
                break;
            case Qt::Key_Left:
                // if items wrapping and current is the first one, then Left => End, else Left => Up
                convertedKey = (isWrapping( ) && (currentIndex( ) == 0)) ? Qt::Key_End : Qt::Key_Up;
                break;
            case Qt::Key_Right:
                // if items wrapping and current is the last one, then Left => Home, else Left => Down
                convertedKey = (isWrapping( ) && (currentIndex( ) == count( ) - 1)) ? Qt::Key_Home : Qt::Key_Down;
                break;
            case Qt::Key_Up:
                // Up => Left
                convertedKey = Qt::Key_Left;
                break;
            case Qt::Key_Down:
                // Down => Right
                convertedKey = Qt::Key_Right;
                break;
            }

            QKeyEvent convertedKeyEvent(e->type( ), convertedKey, e->modifiers( ),
                                         e->text( ), e->isAutoRepeat( ), e->count( ));
            return QComboBox::keyPressEvent(&convertedKeyEvent);
        }
        break;
    default:
        break;
    }

    return QComboBox::keyPressEvent(e);
}

QSize NHorizontalComboBox::sizeHint( ) const
{
    return QComboBox::sizeHint( ) += QSize(QFontMetrics(font( )).height( )*2/5, 0);
}

QStringList NHorizontalComboBox::createNumericTexts(int from, int to) const
{
    QStringList numericTexts;

    if (from <= to)
    {
        for (int i = from; i <= to; ++ i)
            numericTexts.append(QString::number(i));
    }
    else
    {
        for (int i = from; i >= to; -- i)
            numericTexts.append(QString::number(i));
    }

    return numericTexts;
}
