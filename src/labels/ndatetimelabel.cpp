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

NDateTimeLabel::NDateTimeLabel(QWidget *parent, Qt::WindowFlags f)
: QLabel(parent, f)
{
    setAlignment(Qt::AlignCenter);
    setDisplayRole(TimeOnly);
    setFormat(Qt::DefaultLocaleShortDate);
    setContentsMargins(15, 5, 15, 5);
    QPalette pal = palette();
    pal.setColor(QPalette::WindowText, Qt::white);
    setPalette(pal);

    dateTimeFormat = Qt::TextDate;
    role = DateAndTime;
    borderWidth = 5;
    borderColor = QColor(102, 102, 102);
    topColor = QColor(64, 64, 64);
    bottomColor = QColor(8 , 8, 8);
    refreshTimer.setInterval(1000); //1s
    connect(&refreshTimer, SIGNAL(timeout( )), this, SLOT(OnRefreshTimerOut( )));
    refresh( );
    start( );
}

void NDateTimeLabel::setFormat(Qt::DateFormat format)
{
    if (format != dateTimeFormat)
    {
        dateTimeFormat = format;
        refresh( );
    }
}

void NDateTimeLabel::setDisplayRole(DisplayRole r)
{
    if (r != role)
    {
        role = r;
        refresh( );
    }
}

void NDateTimeLabel::OnRefreshTimerOut( )
{
    QDateTime current(QDateTime::currentDateTime( ));
    QString currentText;
    switch (role)
    {
    case DateAndTime:
        currentText = current.toString(dateTimeFormat);
        break;
    case TimeOnly:
        currentText = current.time( ).toString(dateTimeFormat);
        break;
    case DateOnly:
        currentText = current.date( ).toString(dateTimeFormat);
        break;
    default:
        break;
    }

    setText(currentText);
    emit datetimeUpdated(current);
}

void NDateTimeLabel::paintEvent(QPaintEvent *event)
{
    QRect topRect(rect( ));
    QRect bottomRect(rect( ));
    topRect.setHeight(topRect.height( )/2);
    bottomRect.setY(bottomRect.y( ) + bottomRect.height( )/2);
    QPainter painter;
    painter.begin(this);
    painter.fillRect(topRect, QBrush(topColor));
    painter.fillRect(bottomRect, QBrush(bottomColor));

    QPen borderPen(painter.pen( ));
    borderPen.setColor(borderColor);
    borderPen.setWidth(borderWidth);
    painter.setPen(borderPen);
    painter.drawRoundRect(rect( ), 15, 60);
    painter.end( );

    QLabel::paintEvent(event);
}

