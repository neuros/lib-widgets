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
 * NTimeProgressBar implement routies.
 *
 * REVISION:
 * 
 *
 * 2) Import to OSD20. ----------------------------------- 2008-07-29 WX
 * 1) Initial creation. ----------------------------------- 2007-11-30 GL
 *
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "ntimeprogressbar.h"
#include "ntimeprogressbar_p.h"

#include <QPainter>
#include <QTime>
#include <QFontMetrics>
#include <cstdio>

#define SPACE 2
#define DEF_WIDTH 300
#define MIN_WIDTH 100
#define MARK_MIN_LENGTH     6
#define DEFAULTSTR  "00:00:00"

/*
 * Constructs a NTimeProgressBar bar with the given parent.
*/
NTimeProgressBar::NTimeProgressBar(QWidget *parent)
: QWidget(parent), d(new NTimeProgressBarPrivate)
{
    setRange(0, 0);
    setValue(0);
    setCurrentTextVisible(true);
    setTotalTextVisible(true);
    setFormat("hh:mm:ss");
    QPalette p(palette( ));
    p.setColor(QPalette::Window, Qt::lightGray);
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::BrightText, Qt::white);
    setPalette(p);
}

NTimeProgressBar::~NTimeProgressBar( )
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

void NTimeProgressBar::drawGradientRect(QPainter *painter, const QRect &rect, const QColor &from, const QColor &to, int direction)
{
    QLinearGradient gradient(rect.topLeft( ), 0 == direction ? rect.bottomLeft( ) : rect.topRight( ));
    gradient.setColorAt(0.0, from);
    gradient.setColorAt(1.0, to);
    painter->setBrush(gradient);
    painter->drawRect(rect);
}

void NTimeProgressBar::drawGradientBar(QPainter *painter, const QRect &rect, const QColor &from, const QColor &to)
{
    return drawGradientRect(painter, rect, from, to, 0);
}

void NTimeProgressBar::drawPost(QPainter *painter, const QRect &rect, const QColor &from, const QColor &to)
{
    return drawGradientRect(painter, rect, from, to, 0);
}

void NTimeProgressBar::drawProgressBar(QPainter *painter, const QRect &rect, const QColor &from, const QColor &to)
{
    return drawGradientRect(painter, rect, from, to, 0);
}

void NTimeProgressBar::drawPaintTimeMark(QPainter &painter)
{
    if (d->timeMarks.isEmpty( ))
        return;

    int MarkLength = MARK_MIN_LENGTH;
    int MarkNormalLength = d->RetCurText.height();
    QBrush brush;
    QColor color;
    brush.setStyle(Qt::SolidPattern);
    int i = 0;
    Q_FOREACH(NTimeMark item, d->timeMarks)
    {
        i ++;
        if (item.type( ) == NTimeMark::MTClip)
        {
            color = Qt::yellow;
            if (item.state( ) != NTimeMark::MPStart)
            {
                int length = item.end( )-item.start( );
                MarkLength = d->RetMark.width()*length/maximum( );
            }
        }
        else if (item.type( ) == NTimeMark::MTBook)
        {
            color = Qt::green;
        }

        int posx = d->RetMark.width( )*item.start( )/maximum( );

        QRect ret = d->RetProg;
        ret.setWidth(MarkLength);
        ret.translate(posx,0);

        QLinearGradient gradient(0,ret.y(),0,ret.y()+ret.height());
        color.setAlpha(0);
        gradient.setColorAt(0.0,color);
        color.setAlpha(255);
        gradient.setColorAt(1.0,color);
        painter.setBrush(gradient);
        painter.drawRect(ret);  

        brush.setColor(color);
        ret.setY(d->RetMark.y());
        ret.setHeight(d->RetMark.height());
        painter.fillRect(ret,brush);

        if (MarkLength < MarkNormalLength)
        {
            ret.setWidth(MarkNormalLength);
            painter.fillRect(ret,brush);
        }

        //draw number
        QString str;
        str.setNum(i);
        painter.setPen(QColor(30,30,30));
        painter.drawText(ret,Qt::AlignHCenter|Qt::AlignVCenter,str);
        painter.setPen(Qt::NoPen);
    }
}

void NTimeProgressBar::computePos(void)
{
    int range, pos; 
    QFontMetrics fm(font());
    int textsize =  fm.height();
    int textlength = fm.width(DEFAULTSTR);

    d->RetGray  = QRect(textlength/2,
                        height()/2-textsize/6,
                        width()-textlength*3/2-SPACE*4,
                        textsize/3);

    range = maximum( ) - minimum( );
    if (range <= 0)
        pos = 0;
    else
        pos = d->RetGray.width( )*(value( ) - minimum( ))/range;

    d->RetPost = QRect(d->RetGray.x(),
                       height()/2-d->RetGray.height(),
                       d->RetGray.height()/2,
                       d->RetGray.height()*2);
    d->RetPost.translate(pos,0);
    d->RetProg = d->RetGray;
    d->RetProg.setWidth(pos);

    d->RetCurText = QRect(pos,0,textlength,
                          textsize);
    d->RetTotText = QRect(width()-textlength-SPACE*2,
                          height()/2-textsize/2,
                          textlength,
                          textsize);

    d->RetMark = d->RetGray;
    d->RetMark.setHeight(height() - d->RetGray.y() - d->RetGray.height());
    d->RetMark.translate(0, d->RetGray.height());
}

void NTimeProgressBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(font( ));

    computePos( );

    QColor color;

    color = palette( ).color(QPalette::Window);
    drawGradientBar(&painter, d->RetGray, color, QColor(30,30,30));

    color = palette( ).color(QPalette::Highlight);
    drawProgressBar(&painter, d->RetProg, color, QColor(1,1,1));

    drawPaintTimeMark(painter);

    color = palette( ).color(QPalette::HighlightedText);
    drawPost(&painter, d->RetPost, color, QColor(1,1,1));

    if (isTotalTextVisible( ))
    {
        painter.setPen(palette( ).color(QPalette::WindowText));
        painter.drawText(d->RetTotText, Qt::AlignHCenter, QTime( ).addSecs(maximum( )).toString(format( )));
    }

    if (isCurrentTextVisible( ))
    {
        painter.setPen(palette( ).color(QPalette::BrightText));
        painter.drawText(d->RetCurText, Qt::AlignHCenter, QTime( ).addSecs(value( )).toString(format( )));
    }
}

QSize NTimeProgressBar::sizeHint( ) const
{
    QFontMetrics fm(font());
    int textsize =  fm.height();

    return QSize(DEF_WIDTH, textsize*3+2*SPACE);
}

QSize NTimeProgressBar::minimumSizeHint () const
{
    return sizeHint( );
}

void NTimeProgressBar::setFlag(const QList<NTimeMark> &flags)
{
    if (flags == d->timeMarks)
        return;

    d->timeMarks = flags;
    update( );
}

/*
 * Reset the progress bar. The progress bar "rewinds" and shows no progress.
 */
void NTimeProgressBar::reset( )
{
    setValue(d->minimum);
}

int NTimeProgressBar::value( ) const
{ 
    return d->value;
}

void NTimeProgressBar::setValue(int v)
{
    if ((v < 0)
        || (v == d->value)
        || ((v > d->maximum || v < d->minimum) && (d->maximum != 0 || d->minimum != 0)))
        return;

    d->value = v;
    emit valueChanged(d->value);
    update( );
}

int NTimeProgressBar::maximum( ) const
{ 
    return d->maximum;
}

void NTimeProgressBar::setMaximum(int max)
{
    if ((max < 0) || (max == d->maximum))
        return;

    setRange(qMin(d->minimum, max), max);
}

int NTimeProgressBar::minimum( ) const
{ 
    return d->minimum;
}

void NTimeProgressBar::setMinimum(int min)
{
    if ((min < 0) || (min == d->minimum))
        return;

    setRange(min, qMax(d->maximum, min));
}

/*
 * Sets the progress bar's minimum and maximum values to minimum and maximum respectively.
 * If maximum is smaller than minimum, minimum becomes the only legal value.
 * If the current value falls outside the new range, the progress bar is reset with reset().
 */
void NTimeProgressBar::setRange(int min, int max)
{
    if ((d->minimum == min) && (d->maximum == max))
        return;

    min = qMax(min, 0);
    max = qMax(max, 0);

    d->minimum = min;
    d->maximum = qMax(min, max);
    setValue(qBound(d->minimum, d->value, d->maximum));
    update( );
}

QString NTimeProgressBar::format( ) const
{ 
    return d->textFormat;
}

void NTimeProgressBar::setFormat(const QString &format)
{
    if (d->textFormat == format)
        return;

    d->textFormat = format;
    update( );
}

bool NTimeProgressBar::isCurrentTextVisible( ) const
{ 
    return d->currentTextVisible;
}

void NTimeProgressBar::setCurrentTextVisible(bool enable)
{
    if (d->currentTextVisible == enable)
        return;

    d->currentTextVisible = enable;
    update( );
}

bool NTimeProgressBar::isTotalTextVisible( ) const
{ 
    return d->totalTextVisible;
}

void NTimeProgressBar::setTotalTextVisible(bool enable)
{
    if (d->totalTextVisible == enable)
        return;

    d->totalTextVisible = enable;
    update( );
}



NTimeProgressBarPrivate::NTimeProgressBarPrivate()
{
}

NTimeProgressBarPrivate::~NTimeProgressBarPrivate()
{
}



