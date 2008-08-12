#ifndef _NLISTVIEWITEM_H_
#define _NLISTVIEWITEM_H_
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
 * NListViewItem implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-25 WX
 *
 */

#include <QString>
#include <QColor>
#include <QIcon>
#include <QVariant>

#include "nlistviewitem_p.h"

class NListViewItem
{
    Q_ENUMS(NListViewItemDataRole)
public:
    enum NListViewItemDataRole
    {
        DisplayRole = Qt::DisplayRole,
        IconRole = Qt::UserRole + 1,
        NavigationIconRole = Qt::UserRole + 2,
        TextColorRole = Qt::TextColorRole,
        HLineRole = Qt::UserRole + 3
    };

    NListViewItem( );
    explicit NListViewItem(const QString &text);
    explicit NListViewItem(const QString &icon, const QString &text, const QString &navIcon,
                           const QColor &color = QColor( ), bool hline = false, Qt::ItemFlags flags = Qt::NoItemFlags);
    NListViewItem(const NListViewItem &other);
    virtual ~NListViewItem( );

    virtual NListViewItem *clone( ) const { return new NListViewItem(*this); }

    inline QString text( ) const
    { return data(DisplayRole).toString(); }
    inline void setText(const QString &atext)
    { setData(DisplayRole, atext); }

    inline QString icon( ) const
    { return data(IconRole).toString( ); }
    inline void setIcon(const QString &aicon)
    { setData(IconRole, aicon); }

    inline QString navigationIcon( ) const
    { return data(NavigationIconRole).toString( ); }
    inline void setNavigationIcon(const QString &aicon)
    { setData(NavigationIconRole, aicon); }
    
    inline QColor textColor( ) const
    { return qvariant_cast<QColor>(data(TextColorRole)); }
    inline void setTextColor(const QColor &color)
    { setData(TextColorRole, color); }

    inline bool hline( ) const
    { return (data(HLineRole).toBool( )); }
    inline void setHLine(bool hl)
    { setData(HLineRole, hl); }

    virtual QVariant data(int role) const;
    virtual void setData(int role, const QVariant &value);

private:
    NListViewItemPrivate *d;
};


#endif // _NLISTVIEWITEM_H_
