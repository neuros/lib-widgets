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
 * NListView implement routines.
 *
 * REVISION:
 * 
 * 2) Import to OSD20. ----------------------------------- 2008-07-25 WX
 * 1) Initial creation. ----------------------------------- 2007-11-08 EY
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QScrollBar>
#include <QPainter>
#include <QKeyEvent>
#include "nlistview.h"
#include "nlistview_p.h"

NListView::NListView(QWidget * parent)
: QListView(parent), d(new NListViewPrivate)
{
    setFrameStyle(QFrame::NoFrame);
    setAttribute(Qt::WA_InputMethodEnabled, false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(QAbstractItemView::NoSelection);
    setItemDelegate(d->itemDelegate = new NItemDelegate(this));
    setItemWrapping(true);
    setTextAnimationPolicy(AsNeeded);
    setLeftArrowEnable(true);
    setRightIconEnable(true);

    QFontMetrics fm(font( ));
    setIconSize(QSize(fm.height( ), fm.height( )));

    QPalette pal = palette( );
    pal.setColor(QPalette::Text, QColor(0x64,0x64,0x64)); // default normal text color(darker than the text color of current item)
    pal.setColor(QPalette::BrightText, Qt::white); // default current item text color
    pal.setColor(QPalette::Highlight, Qt::red); // default flag color of selected item
    pal.setColor(QPalette::HighlightedText, Qt::white); // default text color for selected item text
    pal.setColor(QPalette::Foreground, Qt::white); // for hline color
    setPalette(pal);
}

NListView::~NListView( )
{
    if (NULL != d)
    {
        delete d;
        d = NULL;
    }
}

NListView::TextAnimationPolicy NListView::textAnimationPolicy( ) const
{ 
    return d->textAnimation;
}

void NListView::setTextAnimationPolicy(TextAnimationPolicy policy)
{
    if (policy == d->textAnimation)
        return;

    d->textAnimation = policy;
}

int NListView::textAnimationInterval( ) const
{ 
    return d->textAnimationInterval;
}

void NListView::setTextAnimationInterval(int interval)
{ 
    d->textAnimationInterval = interval;
}

Qt::Alignment NListView::alignment( ) const
{
    return  d->textAlignment;
}

void NListView::setAlignment(Qt::Alignment alignment)
{
    if (alignment == d->textAlignment)
        return;

    d->textAlignment = alignment;
    viewport( )->update( );
}

bool NListView::isItemWrapping( ) const
{ 
    return d->itemWrapping;
}

void NListView::setItemWrapping(bool w)
{
    d->itemWrapping = w;
}

int NListView::currentRow( ) const
{ 
    return currentIndex( ).row( );
}

void NListView::setCurrentRow(int row)
{ 
    setCurrentIndex(model( )->index(row, 0,rootIndex( )));
}

bool NListView::isLeftArrowEnable( ) const 
{ 
    return d->itemDelegate->isLeftArrowEnable( );
}

void NListView::setLeftArrowEnable(bool enable)
{ 
    d->itemDelegate->setLeftArrowEnable(enable);
    updateCurrent( );  
}

QSize NListView::leftArrowSize( ) const 
{ 
    return d->itemDelegate->leftArrowSize( );
}

void NListView::setLeftArrowSize(const QSize &size) 
{ 
    d->itemDelegate->setLeftArrowSize(size);
    updateCurrent( );  
}

bool NListView::isRightIconEnable( ) const 
{ 
    return d->itemDelegate->isRightIconEnable( );
}

void NListView::setRightIconEnable(bool enable) 
{ 
    d->itemDelegate->setRightIconEnable(enable);
    updateCurrent( );  
}

QSize NListView::rightIconSize( ) const 
{ 
    return d->itemDelegate->rightIconSize( );
}

void NListView::setRightIconSize(const QSize &size) 
{ 
    d->itemDelegate->setRightIconSize(size);
    updateCurrent( );  
}

void NListView::onAnimationFrameChanged(int frame)
{
    qDebug( ) << "NListView::onAnimationFrameChanged" << frame;
    setState(QAbstractItemView::AnimatingState);
    viewport( )->update(visualRect(currentIndex( )));
}

void NListView::keyPressEvent(QKeyEvent *event)
{
    if ((event->key( ) == Qt::Key_Enter) || (event->key( ) == Qt::Key_Right))
    {
        d->currentItemActived = true;
        updateCurrent( );  
    }

    return QListView::keyPressEvent(event);
}

void NListView::keyReleaseEvent(QKeyEvent *event)
{
    if ((event->key( ) == Qt::Key_Enter) || (event->key( ) == Qt::Key_Right))
    {
        d->currentItemActived = false;
        updateCurrent( );  
    }

    return QListView::keyReleaseEvent(event);
}

QModelIndex NListView::moveCursor ( CursorAction cursorAction, 
                                    Qt::KeyboardModifiers modifiers )
{
    if (NULL == model( ))
        return QListView::moveCursor(cursorAction, modifiers);

    int rowCnt = model( )->rowCount(model( )->parent(currentIndex( )));
    int currentRow = currentIndex( ).row( );
    int nextRow = currentRow;

    switch (cursorAction)
    {
    case MoveUp:
        if (currentRow > 0)
            nextRow = currentRow - 1;
        else
            nextRow = (isItemWrapping( ) ? rowCnt - 1 : currentRow);

        if (nextRow + 1 ==  (rowCnt - verticalScrollBar( )->maximum( )) / 2 + verticalScrollBar( )->value( ))
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderSingleStepSub);

        break;
    case MoveDown:
        if (currentRow < rowCnt - 1)
            nextRow = currentRow + 1;
        else
            nextRow = (isItemWrapping( ) ? 0 : currentRow);

        if (nextRow > (rowCnt - verticalScrollBar( )->maximum( ))/2 + verticalScrollBar()->value( ))
            verticalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepAdd);

        break;
    case QListView::MovePageUp:
        if (currentRow > verticalScrollBar()->value( ))
        {
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderMove);
            nextRow = verticalScrollBar( )->value( );
        }
        else if (verticalScrollBar( )->value( ) > 0)
        {
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderPageStepSub);
            nextRow = verticalScrollBar()->value( );
        }
        else if (verticalScrollBar( )->value( ) == 0)
        {
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderToMaximum);
            nextRow = model( )->rowCount(model( )->parent(currentIndex( ))) - 1;
        }
        break;
    case QListView::MovePageDown:
        if (currentRow < (rowCnt - verticalScrollBar( )->maximum( ) + verticalScrollBar( )->value( ) - 1))
        {
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderMove);
            nextRow = rowCnt - verticalScrollBar( )->maximum( ) + verticalScrollBar( )->value( ) - 1;
        }
        else if (verticalScrollBar( )->maximum( ) > verticalScrollBar()->value( ))
        {
            verticalScrollBar()->triggerAction(QAbstractSlider::SliderPageStepAdd);
            nextRow = rowCnt - verticalScrollBar( )->maximum( ) + verticalScrollBar( )->value( ) - 1;
        }
        else if (verticalScrollBar( )->maximum( ) == verticalScrollBar( )->value( ))
        {
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderToMinimum);
            nextRow = 0;
        }
        break;
    default:
        nextRow = QListView::moveCursor(cursorAction, modifiers).row( );
        break;
    }

    return model( )->index(nextRow, 0, rootIndex());
}

void NListView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QListView::currentChanged(current, previous);
    emit currentRowChanged(current.row( ), previous.row( ));
}

QStyleOptionViewItem NListView::viewOptions( ) const
{
    QStyleOptionViewItem option = QListView::viewOptions( );

    option.displayAlignment = d->textAlignment;

    if (d->currentItemActived)
        option.state |= QStyle::State_Sunken;

    return option;
}

void NListView::resizeEvent(QResizeEvent *event)
{
    QListView::resizeEvent(event);

    NItemDelegate *delegate = qobject_cast<NItemDelegate *>(itemDelegate( ));
    if (NULL == delegate)
        return;

	QFontMetrics fm = QFontMetrics(font( ));
    int itemHe = height( )/(height( )/(fm.height( )*5/3));

    if (delegate->isLeftArrowEnable( ) && !delegate->leftArrowSize( ).isValid( ))
        delegate->setLeftArrowSize(QSize(fm.height( )/2, fm.height( )*2/3));
    if (delegate->isIconEnable( ) && !delegate->iconSize( ).isValid( ))
        delegate->setIconSize(iconSize( ));
    if (delegate->isRightIconEnable( ) && !delegate->rightIconSize( ).isValid( ))
        delegate->setRightIconSize(QSize(fm.height( ), fm.height( )));
}

void NListView::paintEvent(QPaintEvent *event)
{
    /* draw "No items to list" if no model */
    if ((NULL == model( )) || (model( )->rowCount( ) <= 0))
    {
        NItemDelegate *delegate = qobject_cast<NItemDelegate *>(itemDelegate( ));
        if (NULL != delegate)
        {
            QPainter painter(viewport( ));
            QStyleOptionViewItem option = viewOptions( );
            option.state |= QStyle::State_HasFocus;
            option.displayAlignment = Qt::AlignCenter;
            option.rect.setSize(delegate->sizeHint(option, QModelIndex( )));
            delegate->paint(&painter, option, QModelIndex( ));
            delegate->drawDisplayExternal(&painter, option, option.rect, tr("No items to list"));
        }

        return;
    }
    else if (state( ) == QAbstractItemView::AnimatingState)
    {
        qDebug( ) << "NListView::paintEvent::AnimatingState" << event->rect( );
        return;
    }
    else
    {
        return QListView::paintEvent(event);
    }
}

void NListView::updateCurrent( )
{
    currentIndex( ).isValid( ) ? update(currentIndex( )) : viewport( )->update( );  
}




NListViewPrivate::NListViewPrivate( )
{
    textAlignment = Qt::AlignLeft|Qt::AlignVCenter;
    textAnimation = NListView::AsNeeded;
    textAnimationTimeLine = NULL;
    textAnimationInterval = 1000;
    itemWrapping = true;

    itemDelegate = NULL;
    currentItemActived = false;
}

NListViewPrivate::~NListViewPrivate( )
{
    if (NULL != itemDelegate)
    {
        delete itemDelegate;
        itemDelegate = NULL;
    }
}
