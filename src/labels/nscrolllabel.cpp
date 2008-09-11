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
 * NClockLabel implement routine.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2007-02-01 GL
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPainter>
#include <QStyle>
#include <QFontMetrics>
#include "nscrolllabel.h"
#include "nscrolllabel_p.h"

NScrollLabel::NScrollLabel(QWidget *parent, Qt::WindowFlags f)
: QLabel(parent, f), d(new NScrollLabelPrivate)
{
    connect(&d->timer, SIGNAL(timeout()), this, SLOT(OnTimerOut()));
}

NScrollLabel::NScrollLabel(const QString & text, QWidget *parent, Qt::WindowFlags f)
: QLabel(text, parent, f), d(new NScrollLabelPrivate)
{
    connect(&d->timer, SIGNAL(timeout()), this, SLOT(OnTimerOut()));
}

NScrollLabel::~NScrollLabel()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

/*
 *  return true if the scroll animation is enable; otherwise false.
 */
bool NScrollLabel::isEnable() const
{
    return d->scrollEnable;
}

/*
 * enable the scroll animation if true, otherwise disable scroll animation
 */
void NScrollLabel::setEnable(bool enable)
{
    if (enable == d->scrollEnable)
        return;

    d->scrollEnable = enable;
    checkAnimation(d->scrollEnable);
    update();
}

/*
 * Starts or restarts the scroll timer with the timeout specified in interval.
 */
void NScrollLabel::start()
{
    checkAnimation(true);
}

/*
 * Stops the scroll timer.
 */
void NScrollLabel::stop()
{
    checkAnimation(false);
}

/*
 * return the scroll timeout interval in milliseconds.
 */
int NScrollLabel::interval() const
{
    return d->timer.interval();
}

/*
 * set the scroll interval in milliseconds
 */
void NScrollLabel::setInterval(int msec)
{
    d->timer.setInterval(msec);
}

void NScrollLabel::OnTimerOut()
{
    d->offset -= d->step;
    if (d->offset < -fontMetrics().width(text()))
        d->offset = d->avariableTextRect.width();

    update();
}

void NScrollLabel::showEvent(QShowEvent *event)
{
    QLabel::showEvent(event);
    checkAnimation(true);
}

void NScrollLabel::hideEvent(QHideEvent *event)
{
    checkAnimation(false);
    QLabel::hideEvent(event);
}

void NScrollLabel::resizeEvent(QResizeEvent *event)
{
    checkAnimation(false);
    QLabel::resizeEvent(event);
    int labelMargin = margin();
    d->avariableTextRect = contentsRect().adjusted(labelMargin, labelMargin, -labelMargin, -labelMargin);
    checkAnimation(true);
}

void NScrollLabel::paintEvent(QPaintEvent *event)
{
    QString txt = text();
    if (txt != d->originText)
    {
        checkAnimation(false);
        d->originText = txt;
        checkAnimation(true);
    }

    if (txt.isEmpty())
        return QLabel::paintEvent(event);

    QPainter painter(this);
    QFontMetrics fm = fontMetrics();
    drawFrame(&painter);
    int flags = QStyle::visualAlignment(layoutDirection(), QFlag(alignment()));
    if ((!d->scrollEnable) || (fm.width(txt) <= d->avariableTextRect.width()))
        style()->drawItemText(&painter,
                              style()->itemTextRect(fontMetrics(), d->avariableTextRect, flags, false, txt),
                              flags, palette(), isEnabled(), txt, foregroundRole());
    else
        style()->drawItemText(&painter,
                              d->avariableTextRect.adjusted(d->offset, 0, 0, 0),
                              flags & ~Qt::AlignHorizontal_Mask | Qt::AlignLeft,
                              palette(), isEnabled(), txt, foregroundRole());
}

bool NScrollLabel::checkAnimation(bool active)
{
    if (active)
    {
        if (d->scrollEnable && (fontMetrics().width(text()) > d->avariableTextRect.width()))
        {
            d->offset = 0;
            d->timer.start();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        d->timer.stop();
        d->offset = 0;
        return true;
    }
}




NScrollLabelPrivate::NScrollLabelPrivate()
{
    timer.setInterval(50); //msec
    offset = 0;
    step = 1;
    scrollEnable = true;
}

NScrollLabelPrivate::~NScrollLabelPrivate()
{
}

