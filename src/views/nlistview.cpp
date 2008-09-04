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
#include "nlistviewitem.h"

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
    setLeftArrowEnable(false);
    setRightIconEnable(false);

    QFontMetrics fm(font( ));
    setIconSize(QSize(fm.height( ), fm.height( )));

    QPalette pal = palette( );
    pal.setColor(QPalette::Text, QColor(0x64,0x64,0x64)); // default normal text color(darker than the text color of current item)
    pal.setColor(QPalette::BrightText, Qt::white); // default current item text color
    pal.setColor(QPalette::Highlight, Qt::red); // default flag color of selected item
    pal.setColor(QPalette::HighlightedText, Qt::white); // default text color for selected item text
    pal.setColor(QPalette::Foreground, Qt::white); // for hline color
    setPalette(pal);

    /* connect signals and slots */
    connect(&d->textAnimationTimeLine, SIGNAL(frameChanged(int)), this, SLOT(OnAnimationFrameChanged(int)));
    connect(&d->activeFlashTimer, SIGNAL(timeout( )), this, SLOT(OnActiveFlashTimerOut( )));
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
    checkAnimation(d->textAnimation == AlwaysOff ? false : true);
}

int NListView::textAnimationInterval( ) const
{ 
    return d->textAnimationTimeLine.updateInterval();
}

void NListView::setTextAnimationInterval(int interval)
{ 
    if (d->textAnimationTimeLine.updateInterval() == interval)
        return;

    d->textAnimationTimeLine.setUpdateInterval(interval);
    checkAnimation(d->textAnimation == AlwaysOff ? false : true);
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

QRect NListView::visualRect(const QModelIndex &index) const
{
    if (index == rootIndex( ))
        return QRect(viewport( )->rect( ).topLeft( ) += QPoint(spacing( ), spacing( )),
                     itemDelegate( )->sizeHint(viewOptions( ), rootIndex( )));
    else
        return QListView::visualRect(index);
}

void NListView::OnAnimationFrameChanged(int frame)
{
    setState(QAbstractItemView::AnimatingState);
    viewport( )->update(d->itemDelegate->currentTextRect());
}

void NListView::OnActiveFlashTimerOut( )
{
    d->currentItemActived = false;
    updateCurrent( );
}

void NListView::focusInEvent(QFocusEvent *event)
{
    QListView::focusInEvent(event);
    checkAnimation(true);
}

void NListView::focusOutEvent(QFocusEvent *event)
{
    checkAnimation(false);
    QListView::focusOutEvent(event);
}

void NListView::keyPressEvent(QKeyEvent *event)
{
    if ((event->key( ) == Qt::Key_Enter) || (event->key( ) == Qt::Key_Right))
    {
        d->currentItemActived = true;
        updateCurrent( );
        d->activeFlashTimer.start( );
    }

    return QListView::keyPressEvent(event);
}

QModelIndex NListView::moveCursor ( CursorAction cursorAction, 
                                    Qt::KeyboardModifiers modifiers )
{
    if (model() == NULL || !currentIndex().isValid())
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

        if (nextRow + 1 ==  (rowCnt - verticalScrollBar( )->maximum( ))/2 + verticalScrollBar( )->value( ))
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderSingleStepSub);

        break;
    case MoveDown:
        if (currentRow < rowCnt - 1)
            nextRow = currentRow + 1;
        else
            nextRow = (isItemWrapping( ) ? 0 : currentRow);

        if (nextRow > (rowCnt - verticalScrollBar( )->maximum( ))/2 + verticalScrollBar()->value( ))
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderSingleStepAdd);

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
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderPageStepAdd);
            nextRow = rowCnt - verticalScrollBar( )->maximum( ) + verticalScrollBar( )->value( ) - 1;
        }
        else if (verticalScrollBar( )->maximum( ) == verticalScrollBar( )->value( ))
        {
            verticalScrollBar( )->triggerAction(QAbstractSlider::SliderToMinimum);
            nextRow = 0;
        }
        break;
    case QListView::MoveLeft:
    case QListView::MoveRight:
        break;
    default:
        nextRow = QListView::moveCursor(cursorAction, modifiers).row( );
        break;
    }

    return model( )->index(nextRow, 0, rootIndex());
}

void NListView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    checkAnimation(false);
    QListView::currentChanged(current, previous);
    checkAnimation(true);
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
    checkAnimation(false);

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

    checkAnimation(true);
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
            option.rect = visualRect(rootIndex( ));
            delegate->paint(&painter, option, rootIndex( ));
            delegate->drawDisplayExternal(&painter, option, option.rect, tr("No items to list"));
        }

        return;
    }
    else if (state( ) == QAbstractItemView::AnimatingState)
    {
        setState(QAbstractItemView::NoState);
        NItemDelegate *delegate = qobject_cast<NItemDelegate *>(itemDelegate( ));
        if (NULL != delegate)
        {
            /* paint animation text */
            QPainter painter(viewport( ));
            QStyleOptionViewItem option = viewOptions( );
            option.state |= QStyle::State_HasFocus;
            QColor textColor = qvariant_cast<QColor>(currentIndex().data(NListViewItem::TextColorRole));
            if (textColor.isValid( ))
                option.palette.setColor(QPalette::BrightText, textColor);
            option.rect = event->rect();
            painter.fillRect(option.rect.adjusted(0, 0, 0, -option.rect.height( )/2), QColor(64, 64, 64));
            painter.fillRect(option.rect.adjusted(0, option.rect.height( )/2, 0, 0), QColor(8, 8, 8));
            delegate->drawDisplayExternal(&painter, option, option.rect, d->animationText.mid(d->textAnimationTimeLine.currentFrame()));
            if (currentIndex().data(NListViewItem::HLineRole).toBool( ))
                delegate->drawHLine(&painter, option,
                                    QLine(QPoint(option.rect.left( ), option.rect.y( ) + option.rect.height( )/2),
                                          QPoint(option.rect.right( ), option.rect.y( ) + option.rect.height( )/2)),
                                    option.palette.color(QPalette::Foreground));
        }

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

void NListView::checkAnimation(bool enable)
{
    switch (d->textAnimation)
    {
    case AsNeeded:
        if (enable)
        {
            if (d->textAnimationTimeLine.state() != QTimeLine::NotRunning)
            {
                d->textAnimationTimeLine.stop();
                d->textAnimationTimeLine.setCurrentTime(0);
                setState(QAbstractItemView::NoState);
            }

            int textWidth = d->itemDelegate->currentTextRect().width();
            d->animationText = currentIndex().data(NListViewItem::DisplayRole).toString();
            QFontMetrics fm(viewport()->font());
            if (fm.width(d->animationText) > textWidth)
            {
                int endFrame = d->animationText.size() - (textWidth*3/4)/fm.averageCharWidth();
                d->textAnimationTimeLine.setFrameRange(0, endFrame > 0? endFrame:d->animationText.size());
                d->textAnimationTimeLine.setDuration(d->textAnimationTimeLine.updateInterval() * (d->textAnimationTimeLine.endFrame() - d->textAnimationTimeLine.startFrame())/d->textAnimationStep);
                d->textAnimationTimeLine.setCurrentTime(0);
                d->textAnimationTimeLine.start();
            }

            break;
        }
    case AlwaysOff:
        d->textAnimationTimeLine.stop();
        d->textAnimationTimeLine.setCurrentTime(0);
        setState(QAbstractItemView::NoState);
    default:
        break;
    }
}




NListViewPrivate::NListViewPrivate( )
{
    textAlignment = Qt::AlignLeft|Qt::AlignVCenter;
    textAnimation = NListView::AlwaysOff;
    itemWrapping = true;

    itemDelegate = NULL;
    currentItemActived = false;
    activeFlashTimer.setInterval(150); //150ms

    textAnimationTimeLine.setDirection(QTimeLine::Forward);
    textAnimationTimeLine.setLoopCount (0); //loop forever
    textAnimationTimeLine.setUpdateInterval(1000); //ms
}

NListViewPrivate::~NListViewPrivate( )
{
    if (NULL != itemDelegate)
    {
        delete itemDelegate;
        itemDelegate = NULL;
    }
}
