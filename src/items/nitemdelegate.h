#ifndef _NITEMDELEGATE_H_
#define _NITEMDELEGATE_H_
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
 * NItemDelegate header.
 *
 * REVISION:
 * 
 * 2) Import to OSD20. ----------------------------------- 2008-07-30 WX
 * 1) Initial creation. ----------------------------------- 2007-12-14 SZ
 *
 */

#include <QItemDelegate>

class NItemDelegatePrivate;

class NItemDelegate : public QItemDelegate
{
     Q_OBJECT
public:
    NItemDelegate(QObject *parent = NULL);
    ~NItemDelegate( );

    //FIXME: port below api after the input method widget done
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool isLeftArrowEnable( ) const;
    void setLeftArrowEnable(bool enable);
    QSize leftArrowSize( ) const;
    void setLeftArrowSize(const QSize &size);

    bool isIconEnable( ) const;
    void setIconEnable(bool enable);
    QSize iconSize( ) const;
    void setIconSize(const QSize &size);

    bool isRightIconEnable( ) const;
    void setRightIconEnable(bool enable);
    QSize rightIconSize( ) const;
    void setRightIconSize(const QSize &size);

    QRect currentTextRect() const;

    void drawCursorBar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void drawSelection(QPainter *painter, const QStyleOptionViewItem &option, const QRect &boundRect, const QColor &color) const;
    void drawHLine(QPainter *painter, const QStyleOptionViewItem &option, const QLine &line, const QColor &color) const;

    /* special api for NListView to draw custom text */
    void drawDisplayExternal(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

private:
    QPainterPath getCursorBarPath(const QRect &rect) const;

private:
    NItemDelegatePrivate *d;
};

#endif // _NITEMDELEGATE_H_
