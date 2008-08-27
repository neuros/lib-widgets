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
 * NDateTimeLabel source
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-08 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPainter>
#include "ndatetimelabel.h"
#include "ndatetimelabel_p.h"

NDateTimeLabel::NDateTimeLabel(QWidget *parent, Qt::WindowFlags f)
: QLabel(parent, f), d(new NDateTimeLabelPrivate)
{
    /* setup default value for NDateTimeLabel */
    setContentsMargins(15, 5, 15, 5);

    QPalette pal = palette();
    pal.setColor(QPalette::WindowText, Qt::white);
    setPalette(pal);

    setAlignment(Qt::AlignCenter);
    setDisplayRole(TimeOnly);
    setFormat(Qt::DefaultLocaleShortDate);

    /* connect signals and slots */
    connect(&d->refreshTimer, SIGNAL(timeout( )), this, SLOT(OnRefreshTimerOut( )));

    refresh();
    start();
}

NDateTimeLabel::~NDateTimeLabel()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

Qt::DateFormat NDateTimeLabel::format() const
{ 
    return d->dateTimeFormat;
}

void NDateTimeLabel::setFormat(Qt::DateFormat format)
{
    if (format == d->dateTimeFormat)
        return;

    d->dateTimeFormat = format;
    refresh();
}

NDateTimeLabel::DisplayRole NDateTimeLabel::displayRole() const
{ 
    return d->role;
}

void NDateTimeLabel::setDisplayRole(DisplayRole r)
{
    if (r == d->role)
        return;

    d->role = r;
    refresh();
}

void NDateTimeLabel::setRefreshInterval(int msec)
{ 
    d->refreshTimer.setInterval(msec);
}

int NDateTimeLabel::refreshInterval() const
{ 
    return d->refreshTimer.interval();
}

void NDateTimeLabel::start()
{ 
    d->refreshTimer.start();
}

void NDateTimeLabel::stop()
{ 
    d->refreshTimer.stop();
}

void NDateTimeLabel::refresh()
{ 
    OnRefreshTimerOut();
}

void NDateTimeLabel::OnRefreshTimerOut()
{
    QDateTime current(QDateTime::currentDateTime());
    QString currentText;
    switch (d->role)
    {
    case DateAndTime:
        currentText = current.toString(d->dateTimeFormat);
        break;
    case TimeOnly:
        currentText = current.time().toString(d->dateTimeFormat);
        break;
    case DateOnly:
        currentText = current.date().toString(d->dateTimeFormat);
        break;
    default:
        break;
    }

    setText(currentText);
    emit datetimeUpdated(current);
}

void NDateTimeLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    d->rectPath = d->roundRectPath(rect());
}

void NDateTimeLabel::paintEvent(QPaintEvent *event)
{
    QRect topRect(rect());
    QRect bottomRect(rect());
    topRect.setHeight(topRect.height()/2);
    bottomRect.setY(bottomRect.y() + bottomRect.height()/2);

    QPainterPath topPath, bottomPath;
    topPath.addRect(topRect);
    bottomPath.addRect(bottomRect);

    QPainter painter;
    painter.begin(this);
    painter.fillPath(d->rectPath.intersected(topPath), d->topColor);
    painter.fillPath(d->rectPath.intersected(bottomPath), d->bottomColor);

    QPen borderPen(painter.pen());
    borderPen.setColor(d->borderColor);
    borderPen.setWidth(d->borderWidth);
    painter.setPen(borderPen);
    painter.drawPath(d->rectPath);
    painter.end();

    QLabel::paintEvent(event);
}



NDateTimeLabelPrivate::NDateTimeLabelPrivate()
{
    dateTimeFormat = Qt::TextDate;
    role = NDateTimeLabel::DateAndTime;
    borderWidth = 5;
    borderColor = QColor(102, 102, 102);
    topColor = QColor(64, 64, 64);
    bottomColor = QColor(8 , 8, 8);
    refreshTimer.setInterval(1000); //1s
}

NDateTimeLabelPrivate::~NDateTimeLabelPrivate()
{
}

QPainterPath NDateTimeLabelPrivate::roundRectPath(const QRect &rect) const
{
    int radius = rect.height()/5;
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
    path.closeSubpath();
    return path;
}

