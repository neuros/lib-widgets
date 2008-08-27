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
 * NListViewItem subroutines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-25 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "nlistviewitem.h"
#include "nlistviewitem_p.h"

NListViewItem::NListViewItem( )
: d(new NListViewItemPrivate)
{
}

NListViewItem :: NListViewItem(const QString &text)
: d(new NListViewItemPrivate)
{
    d->itemText = text;
}

NListViewItem::NListViewItem(const QString &icon, const QString &text, const QString &navIcon,
                             const QColor &color, bool hline, Qt::ItemFlags flags)
: d(new NListViewItemPrivate)
{
    d->itemIcon = icon;
    d->itemText = text;
    d->itemNavIcon = navIcon;
    d->itemTextColor = color;
    d->itemHLine = hline;
}

NListViewItem::NListViewItem(const NListViewItem &other)
: d(new NListViewItemPrivate)
{
    d->itemIcon = other.icon( );
    d->itemText = other.text( );
    d->itemNavIcon = other.navigationIcon( );
    d->itemTextColor = other.textColor( );
    d->itemHLine = other.hline( );
}

NListViewItem::~NListViewItem()
{
    if (NULL != d)
    {
        delete d;
        d = NULL;
    }
}

void NListViewItem::setData(int role, const QVariant &value)
{
    switch (role)
    {
    case DisplayRole:
        d->itemText = value.toString( );
        break;
    case IconRole:
        d->itemIcon = value.toString( );
        break;
    case NavigationIconRole:
        d->itemNavIcon = value.toString( );
        break;
    case TextColorRole:
        d->itemTextColor = qvariant_cast<QColor>(value);
        break;
    case HLineRole:
        d->itemHLine = value.toBool( );
        break;
    default:
        break;
    }
}

QVariant NListViewItem::data(int role) const
{
    switch (role)
    {
    case DisplayRole:
        return d->itemText;
    case IconRole:
        return d->itemIcon;
    case NavigationIconRole:
        return d->itemNavIcon;
    case TextColorRole:
        return d->itemTextColor;
    case HLineRole:
        return d->itemHLine;
    default:
        break;
    }

    return QVariant( );
}




NListViewItemPrivate::NListViewItemPrivate( )
: itemText(""), itemIcon(""), itemNavIcon(""), itemTextColor(QColor( )), itemHLine(false)
{
}

NListViewItemPrivate::~NListViewItemPrivate( )
{
}
