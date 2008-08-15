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
 * neuros action routines.
 *
 * REVISION:
 *
 * 1) Initial creation. ----------------------------------- 2007-03-04 GL
 *
 */

#include "naction.h"
#include "naction_p.h"

#define LOCAL_FONT_SIZE 20
#define GLOBAL_FONT_SIZE 18

NAction::NAction(QObject * parent, ActionType at)
: QAction(parent), d(new NActionPrivate)
{
    setType(at);
}

NAction::NAction(const QString &text, QObject *parent, ActionType at)
: QAction(text, parent), d(new NActionPrivate)
{
    setType(at);
}

NAction::NAction(const QIcon &icon, const QString &text, QObject *parent, ActionType at)
: QAction(icon, text, parent), d(new NActionPrivate)
{
    setType(at);
}

NAction::~NAction( )
{
    if (NULL != d)
    {
        delete d;
        d = NULL;
    }
}

NAction::ActionType NAction::type( ) const
{
    return d->actionType;
}

void NAction::setType(ActionType at)
{
    d->actionType = at;
    QFont f(font( ));

    switch (d->actionType)
    {
    case ActionLocal:
        f.setPointSize(LOCAL_FONT_SIZE);
        f.setBold(true);
        break;
    case ActionGlobal:
        f.setPointSize(GLOBAL_FONT_SIZE);
        f.setBold(false);
        break;
    default:
        break;
    }

    setFont(f);
}



NActionPrivate::NActionPrivate( )
: actionType(NAction::ActionLocal)
{
}

NActionPrivate::~NActionPrivate( )
{
}
