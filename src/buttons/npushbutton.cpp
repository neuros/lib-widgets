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
 * NPushButton implementation
 *
 * REVISION:
 * 
 * 2) Import to OSD20.--------------------------------2008-07-21WX 
 * 1) Initial creation. ----------------------------------- 2008-15-16 nerochiaro
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "npushbutton.h"
#include "npushbutton_p.h"

NPushButton::NPushButton(QWidget *parent)
: QPushButton(parent), d(new NPushButtonPrivate)
{
}

NPushButton::NPushButton(const QString &text, QWidget *parent)
: QPushButton(text, parent), d(new NPushButtonPrivate)
{
}

NPushButton::NPushButton(const QIcon &icon, const QString &text, QWidget *parent)
: QPushButton(icon, text, parent), d(new NPushButtonPrivate)
{
}

NPushButton::~NPushButton()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

void NPushButton::keyPressEvent(QKeyEvent *event)
{
    if (event->key( ) == Qt::Key_Enter)
        animateClick(d->AnimateClickDelay);

    return QAbstractButton::keyPressEvent(event);
}



NPushButtonPrivate::NPushButtonPrivate()
{
}

NPushButtonPrivate::~NPushButtonPrivate()
{
}
