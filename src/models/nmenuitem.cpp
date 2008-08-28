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
 * MenuItem implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-08-15 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "nmenuitem.h"
#include "nmenuitem_p.h"

NMenuItem::NMenuItem(const QString &text)
: NListViewItem(text), d(new NMenuItemPrivate)
{
}

NMenuItem::NMenuItem(const QString &icon, const QString &text, const QString &navIcon,
                     const QColor &color, bool hline, bool isSubmenu, 
                     const QString &command, int helpId, Qt::ItemFlags flags)
: NListViewItem(icon, text, navIcon, color, hline, flags), d(new NMenuItemPrivate)
{
    d->isSubMenu = isSubmenu;
    d->command = command;
    d->helpId = helpId;
}

NMenuItem::NMenuItem(const NMenuItem &other)
: NListViewItem(other), d(new NMenuItemPrivate)
{
    d->isSubMenu = other.isSubmenu();
    d->command = other.command();
    d->helpId = other.helpId();
}

NMenuItem::~NMenuItem()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

QVariant NMenuItem::data(int role) const
{
    switch (role)
    {
    case IsSubMenuRole:
        return d->isSubMenu;
    case CommandRole:
        return d->command;
    case HelpId:
        return d->helpId;
    default:
        return NListViewItem::data(role);
    }
}

void NMenuItem::setData(int role, const QVariant &value)
{
    switch (role)
    {
    case IsSubMenuRole:
        d->isSubMenu = value.toBool();
        break;
    case CommandRole:
        d->command = value.toString();
        break;
    case HelpId:
        d->helpId = value.toInt();
        break;
    default:
        NListViewItem::setData(role, value);
        break;
    }
}




NMenuItemPrivate::NMenuItemPrivate()
: isSubMenu(false), command(""), helpId(0)
{
}

NMenuItemPrivate::~NMenuItemPrivate()
{
}
