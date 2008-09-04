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
 * NRibbonListView implement routies.
 *
 * REVISION:
 *
 * 3) Port to OSD20. ----------------------------------------------------------- 2008-08-12 WX
 * 2) Rename this widget and add fade effect to NRibbonListView. ------------ 2008-03-04 NW
 * 1) Initial creation. ----------------------------------- 2007-11-20 EY
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include "nribbonlistview.h"
#include "nribbonlistview_p.h"
#include "nitemdelegate.h"

NRibbonListView::NRibbonListView(QWidget *parent)
: NListView(parent), d(new NRibbonListViewPrivate)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setItemWrapping(true);
}

NRibbonListView::~NRibbonListView( )
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

/*
 * return the property which holds whether all items are shown if focus out
 */
bool NRibbonListView::showAllItemsIfFocusOut( ) const
{
    return d->showAllItemsIfFocusOut;
}

/*
 * This property holds holds whether all items are shown if focus out.
 * If this property is true all items will show while focus out,
 * otherwise only the current item will show.
 * The default is true.
*/
void NRibbonListView::setShowAllItemsIfFocusOut(bool show)
{
    if (show == d->showAllItemsIfFocusOut)
        return;

    d->showAllItemsIfFocusOut = show;
    viewport( )->update( );
}


QRect NRibbonListView::visualRect(const QModelIndex &index) const
{
    int i = d->toBeRenderedIndexs.indexOf(index);
    if (i != -1)
        return d->toBeRenderedRects[i];
    else
        return NListView::visualRect(index);
}

QModelIndex NRibbonListView::moveCursor(CursorAction cursorAction,
                                        Qt::KeyboardModifiers modifiers)
{
    viewport( )->update( );
    return NListView::moveCursor(cursorAction, modifiers);
}

void NRibbonListView::paintEvent(QPaintEvent *e)
{
    /* calculate the items that need updating */
    calculateToBeRendered( );

    if ((model( ) == NULL) || (model( )->rowCount(rootIndex( )) <= 0) || state( ) == QAbstractItemView::AnimatingState)
        return NListView::paintEvent(e);

    /*
    * Below piece of code is copyed from QListView::paintEvent( )
    * But modify something for our custom NRibbonListView
    * 1. the alternating row Color feature is disabled.
    * 2. the mouse hover feature is disabled.
    * 3. the editorForIndex feature is disabled.
    * 4. paint the text of items that aways from center with gradient color one by one.
    * 5. calculateToBeRendered( ) for NRibbonListView
    */

    const NItemDelegate *delegate = qobject_cast<const NItemDelegate *>(itemDelegate( ));
    if (delegate == NULL)
        return NListView::paintEvent(e);

    QStyleOptionViewItem option = viewOptions( );
    QPainter painter(viewport( ));
    QRect area = e->rect( );

    const QColor currentColor = palette( ).color(QPalette::BrightText);
    const QModelIndex current = currentIndex( );
    const QAbstractItemModel *itemModel = model( );
    const QItemSelectionModel *selections = selectionModel( );
    const bool focus = (hasFocus( ) || viewport( )->hasFocus( )) && current.isValid( );
    const QStyle::State state = option.state;
    const QAbstractItemView::State viewState = this->state();
    const bool enabled = (state & QStyle::State_Enabled) != 0;

    int current_i = d->toBeRenderedIndexs.indexOf(current);
    QVector<QModelIndex>::const_iterator end = d->toBeRenderedIndexs.constEnd();
    for (QVector<QModelIndex>::const_iterator it = d->toBeRenderedIndexs.constBegin(); it != end; ++it)
    {
        Q_ASSERT((*it).isValid());
        option.rect = visualRect(*it);

        /* Do not draw the item if it doesn't proper contained by the view port */
        if (!area.contains(option.rect.adjusted(1, 1, -1, -1), true))
            continue;

        option.state = state;
        if (selections && selections->isSelected(*it))
            option.state |= QStyle::State_Selected;
        if (enabled)
        {
            QPalette::ColorGroup cg;
            if ((itemModel->flags(*it) & Qt::ItemIsEnabled) == 0)
            {
                option.state &= ~QStyle::State_Enabled;
                cg = QPalette::Disabled;
            }
            else
            {
                cg = QPalette::Normal;
            }
            option.palette.setCurrentColorGroup(cg);
        }
        if (focus && current == *it)
        {
            option.state |= QStyle::State_HasFocus;
            if (viewState == EditingState)
                option.state |= QStyle::State_Editing;
        }
        else
        {
            /* Custom the text color */
            int item_i = d->toBeRenderedIndexs.indexOf(*it);
            option.palette.setColor(QPalette::Text,
                                    currentColor.darker(100*(qAbs(item_i - current_i) + 1)));
        }

        delegate->paint(&painter, option, *it);
    }
}

void NRibbonListView::calculateToBeRendered( )
{
    d->toBeRenderedIndexs.clear( );
    d->toBeRenderedRects.clear( );

    if (model( ) == NULL)
    {
        if (flow( ) == QListView::TopToBottom)
        {
            d->toBeRenderedIndexs.append(rootIndex( ));
            const QRect vpRect = viewport( )->rect( );
            QRect centerRect;
            centerRect.setSize(itemDelegate( )->sizeHint(viewOptions( ), rootIndex( )));
            centerRect.moveTopLeft(QPoint(vpRect.left( ) + spacing( ), vpRect.center( ).y( ) - centerRect.height( )/2));
            d->toBeRenderedRects.append(centerRect);
        }
        return;
    }

    const QAbstractItemModel *itemModel = model( );
    const QModelIndex current = currentIndex( );
    const int itemCount = itemModel->rowCount(rootIndex( ));
    
    /* calculate visible indexs */
    QVector<QModelIndex> indexs;
    for (int i = 0; i < itemCount; i ++)
    {
        QModelIndex item = itemModel->index(i, 0);
        if (item.isValid( ) && (!isIndexHidden(item)))
            indexs.append(item);
    }

    /* 1-2-3-0-1-2-3 */
    QVector<QModelIndex> linkedIndexs;
    int currentIndex = indexs.indexOf(current);
    linkedIndexs += indexs.mid(currentIndex + 1);
    linkedIndexs += indexs;
    linkedIndexs += indexs.mid(0, currentIndex);
    currentIndex = linkedIndexs.indexOf(current);

    /* calculate the to be rendered index and rectangle */
    const QRect vpRect = viewport( )->rect( );
    const int space = spacing( );
    QRect centerRect = NListView::visualRect(current);

    if (flow( ) == QListView::TopToBottom)
    {
        centerRect.moveTop(vpRect.center( ).y( ) - centerRect.height( )/2);
        /* append the current index */
        d->toBeRenderedIndexs.append(current);
        d->toBeRenderedRects.append(centerRect);

        if (!d->showAllItemsIfFocusOut
            && ((!hasFocus( )) && (!viewport( )->hasFocus( ))))
            return;  //Just show the current item if focus out

        int upY = centerRect.y( );
        int downY = centerRect.bottom( );
        bool reachTop = false, reachBottom = false;
        for (int i = 1; i <= currentIndex; ++ i)
        {
            upY -= space;
            downY += space;
            QModelIndex upIndex = linkedIndexs[currentIndex - i];
            QModelIndex downIndex = linkedIndexs[currentIndex + i];
            if ((d->toBeRenderedIndexs.indexOf(upIndex) != -1)
                || (d->toBeRenderedIndexs.indexOf(downIndex) != -1))
                break;

            QRect upRect = visualRect(upIndex);
            QRect downRect = visualRect(downIndex);

            upY -= upRect.height( );
            upRect.moveTop(upY);
            downRect.moveTop(downY);
            downY += downRect.height( );

            if (upRect.top( ) < vpRect.top( ))
                reachTop = true;

            if (downRect.bottom( ) > vpRect.bottom( ))
                reachBottom = true;

            if (!reachTop)
            {
                d->toBeRenderedIndexs.prepend(upIndex);
                d->toBeRenderedRects.prepend(upRect);
            }

            if (!reachBottom)
            {
                d->toBeRenderedRects.append(downRect);
                d->toBeRenderedIndexs.append(downIndex);
            }
        }
    }
}



NRibbonListViewPrivate::NRibbonListViewPrivate( )
{
    showAllItemsIfFocusOut = true;
}

NRibbonListViewPrivate::~NRibbonListViewPrivate( )
{
}
