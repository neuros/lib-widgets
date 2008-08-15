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
 * NXim routines.
 *
 * REVISION:
 *
 * 2) Import to OSD20 ----------------------------------- 2008-07-31 WX
 * 1) Initial creation. ----------------------------------- 2007-11-28 NW
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPainter>
#include <QShowEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QWidgetAction>
#include "nxim.h"
#include "nxim_p.h"

#define XIM_PAGE_ITEMS_MAX 7

#define XIM_WIDTH 320
#define XIM_HEIGTH_MIN 120
#define XIM_HEIGTH_MAX 315

#define XIM_ITEM_WIDTH 300
#define XIM_ITEM_HEIGHT 30

#define XIM_ITEM_ARROW_SPACING 10

#define XIM_ARROW_WIDTH 25
#define XIM_ARROW_HEIGHT 15

#define XIM_ICON_SPACING 8
#define XIM_ICON_WIDTH 18

NXim::NXim(QWidget *parent)
: QMenu(parent), d(new NXimPrivate)
{
    setTitle(tr("Options"));
    QPalette pal = palette( );
    pal.setBrush(QPalette::Highlight, QBrush( ));
    pal.setBrush(QPalette::Button, QBrush( ));
    setPalette(pal);
}

NXim::NXim(const QString &title, QWidget *parent)
: QMenu(title, parent), d(new NXimPrivate)
{
    setTitle(tr("Options"));
    QPalette pal = palette( );
    pal.setBrush(QPalette::Highlight, QBrush( ));
    pal.setBrush(QPalette::Button, QBrush( ));
    setPalette(pal);
}

NXim::~NXim( )
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

void NXim::showEvent(QShowEvent *event)
{
    QMenu::showEvent(event);
    int previousIndex = d->topItemIndex + d->currentItemIndex;
    int currentIndex = d->actionList.indexOf(activeAction( ));
    qDebug( ) << previousIndex << currentIndex;

    if ((currentIndex != -1) && (currentIndex != previousIndex)) //Has active action, and it isn't the previous index
    {
        d->currentItemIndex = currentIndex%d->pageItemMax;
        d->topItemIndex = currentIndex - d->currentItemIndex;
    }
    else if (previousIndex != -1)
    {
        setActiveAction(d->actionList.at(previousIndex));
    }
    else
    {
        d->currentItemIndex = 0;
        d->topItemIndex = 0;
        setActiveAction(d->actionList.at(0));
    }
}

void NXim::keyPressEvent(QKeyEvent *event)
{
    switch (event->key( ))
    {
    case Qt::Key_Up:
        if (d->topItemIndex + d->currentItemIndex == 0) // current is the first item
        {
            /* Go to the last item */
            d->currentItemIndex = d->pageItemMax - 1;
            d->topItemIndex = d->actionList.count( ) - 1 - d->currentItemIndex;
        }
        else if (d->currentItemIndex == 0) // current is the first item of current page
        {
            d->topItemIndex --;
        }
        else
        {
            d->currentItemIndex --;
        }

        setActiveAction(d->actionList.at(d->topItemIndex + d->currentItemIndex));
        update( );
        break;
    case Qt::Key_Down:
        if (d->topItemIndex + d->currentItemIndex == (d->actionList.count( ) - 1)) // current is the last item
        {
            /* Go to the first item */
            d->currentItemIndex = 0;
            d->topItemIndex = 0;
        }
        else if (d->currentItemIndex == (d->pageItemMax - 1)) // current is the last item of current page
        {
            d->topItemIndex ++;
        }
        else
        {
            d->currentItemIndex ++;
        }

        setActiveAction(d->actionList.at(d->topItemIndex + d->currentItemIndex));
        update( );
        break;
    default:
        return QMenu::keyPressEvent(event);
        break;
    }
}

QSize NXim::sizeHint( ) const
{
    d->actionList = getVisibleActions( );
    QSize size;
    size.setWidth(QMenu::sizeHint( ).width( ));
    size.setHeight(d->topHeight
                   + (d->needScroll ? 2*d->arrowSize.height( ) : 0)
                   + 2*XIM_ITEM_ARROW_SPACING
                   + (d->needScroll ? d->pageItemMax : d->actionList.count( ))*XIM_ITEM_HEIGHT
                   + d->bottomHeight);
    return size;
}

void NXim::resizeEvent(QResizeEvent *event)
{
    QMenu::resizeEvent(event);
    QPixmap bg(size( ));
    QPainter painter(&bg);
    QStyleOption option;
    option.initFrom(this);
    option.rect = QRect(QPoint(0, 0), bg.size( ));
    /* erase with background color */
    painter.eraseRect(option.rect);
    /* draw background image to the pixmap */
    drawBackground(&painter, option, rect( ).translated(option.rect.topLeft( )));
    /* set the background pixmap to background role */
    QPalette pal = palette( );
    pal.setBrush(backgroundRole( ), QBrush(bg));
    setPalette(pal);
}

void NXim::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    /* draw header, the xim icon and the title */
    QRect topRect = rect( );
    topRect.setHeight(d->topHeight);
    QStyleOptionHeader headerOption;
    headerOption.initFrom(this);
    headerOption.text = title( );
    headerOption.textAlignment = Qt::AlignCenter;
    headerOption.orientation = Qt::Horizontal;
    headerOption.icon = QIcon(*d->ximIconPixmap);
    headerOption.iconAlignment = Qt::AlignCenter;
    drawHeader(&painter, headerOption, topRect.translated(headerOption.rect.topLeft( )));

    /* draw the items that need updating */
    QStyleOption option;
    option.initFrom(this);
    const int hmargin = style( )->pixelMetric(QStyle::PM_MenuHMargin, &option, this);
    const int vmargin = style( )->pixelMetric(QStyle::PM_MenuVMargin, &option, this);
    QRect contentRect = rect( ).adjusted(hmargin,
                                         vmargin + d->topHeight + (d->needScroll ? d->arrowSize.height( ) : 0) + XIM_ITEM_ARROW_SPACING,
                                         -hmargin,
                                         -vmargin - d->bottomHeight - (d->needScroll ? d->arrowSize.height( ) : 0) - XIM_ITEM_ARROW_SPACING);

    int x = contentRect.x( );
    int y = contentRect.y( );
    QList<QAction *> pageActions = d->actionList.mid(d->topItemIndex, d->pageItemMax);
    Q_FOREACH(QAction *item, pageActions)
    {
        QRect itemRect = actionGeometry(item);
        itemRect.moveTopLeft(QPoint(x, y));

        if (!contentRect.contains(itemRect))
            continue;

        painter.setClipRegion(QRegion(itemRect));

        QStyleOptionMenuItem opt;
        initStyleOption(&opt, item);
        opt.rect = itemRect;
        if (opt.state & QStyle::State_Selected)
            drawCursor(&painter, opt, opt.rect);

        style( )->drawControl(QStyle::CE_MenuItem, &opt, &painter, this);
        y += itemRect.height( );
    }

    /* drawing the up/down arrows */
    const bool scrollUp = (d->topItemIndex > 0);
    const bool scrollDown = (d->topItemIndex + d->pageItemMax < d->actionList.count( ));
    if (scrollUp || scrollDown)
    {
        QStyleOptionMenuItem menuOpt;
        menuOpt.initFrom(this);
        menuOpt.palette = palette( );
        menuOpt.state = QStyle::State_None;
        menuOpt.checkType = QStyleOptionMenuItem::NotCheckable;
        menuOpt.menuRect = rect( );
        menuOpt.maxIconWidth = 0;
        menuOpt.tabWidth = 0;
        menuOpt.menuItemType = QStyleOptionMenuItem::Scroller;
        menuOpt.state |= QStyle::State_Enabled;

        /* draw up arrow if need */
        if (scrollUp)
        {
            menuOpt.rect.setRect(rect( ).center( ).x( ) - d->arrowSize.width( )/2,
                                 contentRect.y( ) - XIM_ITEM_ARROW_SPACING - d->arrowSize.height( ),
                                 d->arrowSize.width( ), d->arrowSize.height( ));
            painter.setClipRect(menuOpt.rect);
            style()->drawControl(QStyle::CE_MenuScroller, &menuOpt, &painter, this);
        }

        /* draw down arrow if need */
        if (scrollDown)
        {
            menuOpt.rect.setRect(rect( ).center( ).x( ) - d->arrowSize.width( )/2,
                                 contentRect.bottom( ) + XIM_ITEM_ARROW_SPACING,
                                 d->arrowSize.width( ), d->arrowSize.height( ));
            menuOpt.state |= QStyle::State_DownArrow;
            painter.setClipRect(menuOpt.rect);
            style()->drawControl(QStyle::CE_MenuScroller, &menuOpt, &painter, this);
        }
    }

    painter.end( );
}

void NXim::drawBackground(QPainter *painter, const QStyleOption &option, const QRect &rect) const
{
    /* draw top left*/
    painter->drawPixmap(QRect(rect.topLeft( ), d->bgTopLeftPixmap->size( )),
                        *d->bgTopLeftPixmap);
    /* draw top right */
    painter->drawPixmap(QRect(QPoint(rect.x( ) + rect.width( ) - d->bgTopRightPixmap->width( ),
                                     rect.y( )), d->bgTopRightPixmap->size( )), *d->bgTopRightPixmap);
    /* draw top middle*/
    painter->drawTiledPixmap(QRect(rect.x( ) + d->bgTopLeftPixmap->width( ),
                                   rect.y( ),
                                   rect.width( ) - d->bgTopLeftPixmap->width( ) - d->bgTopRightPixmap->width( ),
                                   d->bgTopMiddlePixmap->height( )),
                             *d->bgTopMiddlePixmap, QPoint(0, 0));
    /* draw bottom */
    painter->drawPixmap(QRect(rect.x( ), rect.y( ) + rect.height( ) - d->bgBottomPixmap->height( ),
                              rect.width( ), d->bgBottomPixmap->height( )), *d->bgBottomPixmap);
    /* draw middle left side */
    painter->drawPixmap(QRect(rect.x( ),
                              rect.y( ) + d->bgTopMiddlePixmap->height( ),
                              d->bgMiddleSidePixmap->width( ),
                              rect.height( ) - d->bgTopMiddlePixmap->height( ) - d->bgBottomPixmap->height( )),
                        *d->bgMiddleSidePixmap);
    /* draw middle right side */
    painter->drawPixmap(QRect(rect.x( ) + rect.width( ) - d->bgMiddleSidePixmap->width( ),
                              rect.y( ) + d->bgTopMiddlePixmap->height( ),
                              d->bgMiddleSidePixmap->width( ),
                              rect.height( ) - d->bgTopMiddlePixmap->height( ) - d->bgBottomPixmap->height( )),
                        *d->bgMiddleSidePixmap);
    /* draw middle center */
    painter->drawPixmap(QRect(rect.x( ) + d->bgMiddleSidePixmap->width( ),
                              rect.y( ) + d->bgTopMiddlePixmap->height( ),
                              rect.width( ) - 2*d->bgMiddleSidePixmap->width( ),
                              rect.height( ) - d->bgTopMiddlePixmap->height( ) - d->bgBottomPixmap->height( )),
                        *d->bgMiddleMiddlePixmap);
}

void NXim::drawHeader(QPainter *painter, const QStyleOptionHeader &option, const QRect &rect) const
{
    QRect boundingRect;
    painter->drawText(rect, option.textAlignment, option.text, &boundingRect);
    QRect iconRect = boundingRect;
    iconRect.setX(boundingRect.x( ) - boundingRect.height( )*3/4 - XIM_ICON_SPACING);
    iconRect.setWidth(boundingRect.height( )*3/4);
    painter->drawPixmap(iconRect, option.icon.pixmap(iconRect.size( )));
}

void NXim::drawCursor(QPainter *painter, const QStyleOptionMenuItem &option, const QRect &rect) const
{
    painter->drawPixmap(rect.x( ), rect.y( ),
                        d->bgCursorLeftPixmap->width( ), rect.height( ),
                        *d->bgCursorLeftPixmap);
    painter->drawPixmap(rect.right( ) - d->bgCursorRightPixmap->width( ), rect.y( ),
                        d->bgCursorRightPixmap->width( ), rect.height( ),
                        *d->bgCursorRightPixmap);
    painter->drawTiledPixmap(rect.x( ) + d->bgCursorLeftPixmap->width( ), rect.y( ),
                             rect.width( ) - d->bgCursorLeftPixmap->width( ) - d->bgCursorRightPixmap->width( ), rect.height( ),
                             *d->bgCursorMiddlePixmap);
}

QList<QAction *> NXim::getVisibleActions( ) const
{
    QList<QAction *> items;
    Q_FOREACH(QAction *item, actions( ))
    {
        if (QWidgetAction *wa = qobject_cast<QWidgetAction *>(item))
            if (wa->requestWidget(const_cast<NXim *>(this)))
                continue;

        if (item->isVisible( ))
            items << item;
    }

    if (items.count( ) > d->pageItemMax)
        d->needScroll = true;
    else
        d->needScroll = false;

    return items;
}



NXimPrivate::NXimPrivate( )
{
    loadPixmaps( );

    topHeight = qMax(bgTopLeftPixmap->height( ), bgTopRightPixmap->height( ));
    topHeight = qMax(topHeight, bgTopMiddlePixmap->height( ));
    bottomHeight = bgBottomPixmap->height( );
    arrowSize = QSize(XIM_ARROW_WIDTH, XIM_ARROW_HEIGHT);

    topItemIndex = 0;
    currentItemIndex = -1;
    pageItemMax = XIM_PAGE_ITEMS_MAX;
    needScroll = false;
}

NXimPrivate::~NXimPrivate( )
{
    unloadPixmaps( );
}

void NXimPrivate::loadPixmaps( )
{
    ximIconPixmap = new QPixmap(":/neux/xim.gif");
    upArrowPixmap = new QPixmap(":/neux/grey-arrow-up.gif");
    downArrowPixmap = new QPixmap(":/neux/grey-arrow-down.gif");
    bgTopLeftPixmap = new QPixmap(":/neux/xim-bg-top-left.png");
    bgTopMiddlePixmap = new QPixmap(":/neux/xim-bg-top-middle.png");
    bgTopRightPixmap = new QPixmap(":/neux/xim-bg-top-right.png");
    bgMiddleSidePixmap = new QPixmap(":/neux/xim-bg-middle-side.png");
    bgMiddleMiddlePixmap = new QPixmap(":/neux/xim-bg-middle-middle.png");
    bgBottomPixmap = new QPixmap(":/neux/xim-bg-bottom.png");
    bgCursorLeftPixmap = new QPixmap(":/neux/xim-cursor-left.png");
    bgCursorMiddlePixmap = new QPixmap(":/neux/xim-cursor-middle.png");
    bgCursorRightPixmap = new QPixmap(":/neux/xim-cursor-right.png");
}

void NXimPrivate::unloadPixmaps( )
{
    delete ximIconPixmap;
    delete upArrowPixmap;
    delete downArrowPixmap;
    delete bgTopLeftPixmap;
    delete bgTopMiddlePixmap;
    delete bgTopRightPixmap;
    delete bgMiddleSidePixmap;
    delete bgMiddleMiddlePixmap;
    delete bgBottomPixmap;
    delete bgCursorLeftPixmap;
    delete bgCursorMiddlePixmap;
    delete bgCursorRightPixmap;
}
