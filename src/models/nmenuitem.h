#ifndef _NMENUITEM_H_
#define _NMENUITEM_H_
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
 * NMenuItem header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-08-15 WX
 *
 */

#include "nlistviewitem.h"

class NMenuItemPrivate;

class NMenuItem : public NListViewItem
{
    Q_ENUMS(NMenuItemDataRole)

    public:
    enum NListViewItemDataRole
    {
        IsSubMenuRole = NListViewItem::HLineRole + 1,
        CommandRole,
        HelpId
    };

    explicit NMenuItem(const QString &text);
    explicit NMenuItem(const QString &icon, const QString &text, const QString &navIcon,
                       const QColor &color = QColor(), bool hline = false,
                       bool isSubmenu = false, const QString &command = QString(),
                       int helpId = 0, Qt::ItemFlags flags = Qt::NoItemFlags);
    NMenuItem(const NMenuItem &other);
    virtual ~NMenuItem();

    inline bool isSubmenu() const
    { return(data(IsSubMenuRole).toBool()); }
    inline void setIsSubmenu(bool flag)
    { setData(IsSubMenuRole, flag); }

    inline QString command() const
    { return(data(CommandRole).toString()); }
    inline void setCommand(const QString &command )
    { setData(CommandRole, command); }

    inline int helpId() const
    { return(data(HelpId).toInt()); }
    inline void setHelpId(int id)
    { setData(HelpId, id); }

    virtual QVariant data(int role) const;
    virtual void setData(int role, const QVariant &value);

private:
    NMenuItemPrivate *d;

};

#endif // _NMENUITEM_H_
