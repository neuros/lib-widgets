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
 * NItemDelegate routine.
 *
 * REVISION:
 * 
 * 2) Import to OSD20. ----------------------------------- 2008-07-30 WX
 * 1) Initial creation. ----------------------------------- 2007-12-14 SZ
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPainter>
#include <QPixmapCache>
#include "nitemdelegate.h"
#include "nlistviewitem.h"
#include "nlistview.h"

#define ARROW_ICON_LEFT  ":/neux/grey-arrow-left.gif"

NItemDelegate::NItemDelegate(QObject *parent)
: QItemDelegate(parent), d(new NItemDelegatePrivate)
{
}

NItemDelegate::~NItemDelegate( )
{
    if (NULL != d)
    {
        delete d;
        d = NULL;
    }
}


bool NItemDelegate::isLeftArrowEnable( ) const
{ 
    return d->leftArrowEnable;
}

void NItemDelegate::setLeftArrowEnable(bool enable)
{ 
    d->leftArrowEnable = enable;
}

QSize NItemDelegate::leftArrowSize( ) const
{ 
    return d->leftArrowSize;
}

void NItemDelegate::setLeftArrowSize(const QSize &size)
{ 
    d->leftArrowSize = size;
}

bool NItemDelegate::isIconEnable( ) const
{ 
    return d->iconEnable;
}

void NItemDelegate::setIconEnable(bool enable)
{ 
    d->iconEnable = enable;
}

QSize NItemDelegate::iconSize( ) const
{ 
    return d->iconSize;
}

void NItemDelegate::setIconSize(const QSize &size)
{ 
    d->iconSize = size;
}

bool NItemDelegate::isRightIconEnable( ) const
{ 
    return d->rightIconEnable;
}

void NItemDelegate::setRightIconEnable(bool enable)
{ 
    d->rightIconEnable = enable;
}

QSize NItemDelegate::rightIconSize( ) const
{ 
    return d->rightIconSize;
}

void NItemDelegate::setRightIconSize(const QSize &size)
{ 
    d->rightIconSize = size;
}

QWidget * NItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::createEditor(parent, option, index);
}

void NItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return QItemDelegate::setEditorData(editor, index);
}

void NItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    return QItemDelegate::setModelData(editor, model, index);
}

void NItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::updateEditorGeometry(editor, option, index);
}

void NItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect itemLeftArrowRect, itemIconRect, itemRightIconRect, itemTextRect, itemSelectionRect;
    d->doLayout(option.rect, &itemLeftArrowRect, &itemIconRect,
                &itemRightIconRect, &itemTextRect, &itemSelectionRect);

    bool hasFocus = false;
    if ((option.state & QStyle::State_HasFocus)
        || (!(option.state & QStyle::State_Active) && index == d->focusIndex))
    {
        hasFocus = true;
        //Save the focus item index, so that we can paint the same style as focus in while focus out
        d->focusIndex = index;
    }

    if (hasFocus)
    {
        /* draw item corsor bar */
        drawCursorBar(painter, option, index);

        /* draw item left arrow icon */
        if (d->leftArrowEnable)
        {
            QPixmap pixmap;
            if (!QPixmapCache::find(ARROW_ICON_LEFT, pixmap))
            {
                pixmap = QPixmap(ARROW_ICON_LEFT);
                QPixmapCache::insert (ARROW_ICON_LEFT, pixmap);
            }

            drawDecoration(painter, option, itemLeftArrowRect, pixmap.scaled(itemLeftArrowRect.size( )));
        }

        /* draw item right icon */
        if (d->rightIconEnable)
        {
            QString iconName = index.data(NListViewItem::NavigationIconRole).toString( );
            QPixmap pixmap;
            if (!QPixmapCache::find(iconName, pixmap))
            {
                pixmap = QPixmap(iconName);
                QPixmapCache::insert(iconName, pixmap);
            }

            if (!pixmap.isNull( ))
                drawDecoration(painter, option, itemRightIconRect, pixmap.scaled(itemRightIconRect.size( )));
        }
    }

    /* draw item text */
    bool hasSelected = false;
    QStyleOptionViewItem textOpt = option;
    if (option.state & QStyle::State_Selected)
    {
        hasSelected = true;
        textOpt.state &= ~QStyle::State_Selected; // disable Qt to paint the selected color
    }

    QColor textColor = qvariant_cast<QColor>(index.data(NListViewItem::TextColorRole));
    if (textColor.isValid( ))
        textOpt.palette.setColor(QPalette::Text, textColor);
    else if (hasSelected)
        textOpt.palette.setColor(QPalette::Text, option.palette.color(QPalette::HighlightedText));
    else
        textOpt.palette.setColor(QPalette::Text, hasFocus ? option.palette.color(QPalette::BrightText) : option.palette.color(QPalette::Text));

    drawDisplay(painter, textOpt, itemTextRect, index.data(Qt::DisplayRole).toString( ));

    /* draw item text highlight line */
    if (index.data(NListViewItem::HLineRole).toBool( ))
    {
        QPoint from(itemTextRect.left( ), itemTextRect.y( ) + itemTextRect.height( )/2);
        QPoint to(itemTextRect.right( ), itemTextRect.y( ) + itemTextRect.height( )/2);
        drawHLine(painter, option, QLine(from, to), option.palette.color(QPalette::Foreground));
    }

    /* draw item icon */
    if (d->iconEnable)
    {
        QString iconName = index.data(NListViewItem::IconRole).toString( );
        QPixmap pixmap;
        if (!QPixmapCache::find(iconName, pixmap))
        {
            pixmap = QPixmap(iconName);
            QPixmapCache::insert(iconName, pixmap);
        }

        if (!pixmap.isNull( ))
            drawDecoration(painter, option, itemIconRect, pixmap.scaled(itemIconRect.size( )));
    }

    /* draw item selection */
    if (option.state & QStyle::State_Selected)
        drawSelection(painter, option, itemSelectionRect, option.palette.color(QPalette::Highlight));
}

QSize NItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant value = index.data(Qt::SizeHintRole);
    if (value.isValid( ))
    {
        return value.toSize( );
    }
    else if (NListView *p = qobject_cast<NListView *>(parent( )))
    {
        QWidget *vp = p->viewport( );
        return QSize(vp->width( ), vp->height( )/(vp->height( )/(2*6 + vp->font( ).pointSize( )*5/3))); // 6: outline width
    }
    else
    {
        return QItemDelegate::sizeHint(option, index); 
    }
}

void NItemDelegate::drawCursorBar(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    Q_UNUSED(index)
    if (option.state & QStyle::State_Sunken)
    {
		painter->fillPath(getCursorBarPath(option.rect), QColor(0xe4, 0x5b, 0x00));
    }
    else
    {
        painter->fillRect(option.rect.adjusted(6, 6, -6, -option.rect.height( )/2), QColor(64, 64, 64));
        painter->fillRect(option.rect.adjusted(6, option.rect.height( )/2, -6, -6), QColor(8, 8, 8));
        painter->strokePath(getCursorBarPath(option.rect.adjusted(3, 3, -3, -3)), QPen(QColor(0xe4, 0x5b, 0x00).darker(125), 6)); // 6: the width of outline
    }
}

void NItemDelegate::drawSelection(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QRect &boundRect, const QColor &color) const
{
    Q_UNUSED(option)
    QPainterPath pp;
    pp.addEllipse(boundRect);
    painter->fillPath(pp, color);
}

void NItemDelegate::drawHLine(QPainter *painter, const QStyleOptionViewItem &option,
                              const QLine &line, const QColor &color) const
{
    Q_UNUSED(option)
    painter->setPen(color);
    painter->drawLine(line);
}

void NItemDelegate::drawDisplayExternal(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{ 
    QStyleOptionViewItem opt = option;
    opt.state &= ~QStyle::State_Selected; // disable Qt to paint the selected color

    if (option.state & QStyle::State_Selected)
        opt.palette.setColor(QPalette::Text, opt.palette.color(QPalette::HighlightedText));
    else
        opt.palette.setColor(QPalette::Text, option.state & QStyle::State_HasFocus ? opt.palette.color(QPalette::BrightText) : opt.palette.color(QPalette::Text));

    return drawDisplay(painter, opt, rect, text);
}


QPainterPath NItemDelegate::getCursorBarPath(const QRect &rect) const
{
    int radius = rect.height( )/5;
    int diam = 2*radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);

    QPainterPath path;
    path.moveTo(x2, y1 + radius);
    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
    path.lineTo(x1 + radius, y1);
    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
    path.lineTo(x1, y2 - radius);
    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
    path.lineTo(x1 + radius, y2);
    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
    path.closeSubpath( );

    return path;
}


NItemDelegatePrivate::NItemDelegatePrivate( )
: leftArrowEnable(true),
  iconEnable(true),
  rightIconEnable(true)
{
}

NItemDelegatePrivate::~NItemDelegatePrivate( )
{
}

void NItemDelegatePrivate::doLayout(const QRect &rect, QRect *leftArrowRect, QRect *iconRect,
                                    QRect *rightIconRect, QRect *textRect, QRect *selectionRect) const
{
    if (!rect.isValid( ))
        return;

    int x_offset = 0;
    int textWidth = rect.width( );
    /* calculate the position and size for left arrow icon */
    if (leftArrowEnable)
    {
        leftArrowRect->setX(rect.x( ) + x_offset + leftArrowSize.height( ));
        leftArrowRect->setY(rect.y( ) + (rect.height( ) - leftArrowSize.height( ))/2);
        leftArrowRect->setSize(leftArrowSize);
        x_offset += leftArrowSize.height( ) + leftArrowRect->width( );
    }

    /* calculate the position and size for decoration icon */
    if (iconEnable)
    {
        iconRect->setX(rect.x( ) + x_offset + iconSize.height( ));
        iconRect->setY(rect.y( ) + (rect.height( ) - iconSize.height( ))/2);
        iconRect->setSize(iconSize);
        x_offset +=  iconSize.height( ) + iconSize.width( );
    }
  
    /* calculate the position and size for right icon */
    if (rightIconEnable)
    {
        rightIconRect->setX(rect.x( ) + rect.width( ) - rightIconSize.width( ) - rightIconSize.height( ));
        rightIconRect->setY(rect.y( ) + (rect.height( ) - rightIconSize.height( ))/2);
        rightIconRect->setSize(rightIconSize);
        textWidth -= rect.x( ) + rect.width( ) - rightIconRect->x( );
    }
    
    if (0 == x_offset)
        x_offset = rect.height( );
    else
        x_offset += 30;

    textWidth -= x_offset;
    textWidth -= 30;
    
    /* calculate the position and size for display text rectangle */
    textRect->setX(rect.x( ) + x_offset); // 30: margin between text and icon
    textRect->setY(rect.y( ) + 6); // 6: the width of outline
    textRect->setSize(QSize(textWidth, rect.height( ) - 2*6));

    /* calculate the position and size for selection rectangle */
    selectionRect->setX(textRect->x( ) - (textRect->x( ) - x_offset + 30)/3);
    selectionRect->setY(rect.y( ) + rect.height( )/2 + rect.height( )/10);
    selectionRect->setSize(QSize(8, 8)); //Fixed selection rectangle.
}

