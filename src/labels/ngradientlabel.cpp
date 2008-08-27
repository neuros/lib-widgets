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
 * NGradientLabel source
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-07 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QLinearGradient>
#include <QPainter>
#include "ngradientlabel.h"
#include "ngradientlabel_p.h"

#define DEFAULT_GRADIENT_POLICY (NGradientLabel::LinearGradientVertical)
#define DEFAULT_LINEAR_COLOR_START (QColor(0xFF,0xFF,0xFF))
#define DEFAULT_LINEAR_COLOR_STOP (QColor(0x4,0x4,0x4))

NGradientLabel::NGradientLabel(QWidget *parent, Qt::WindowFlags f)
: QLabel(parent, f), d(new NGradientLabelPrivate)
{
    /* setup default gradient policy */
    setGradientPolicy(DEFAULT_GRADIENT_POLICY);
    setLinearColorStart(DEFAULT_LINEAR_COLOR_START);
    setLinearColorStop(DEFAULT_LINEAR_COLOR_STOP);
}

NGradientLabel::NGradientLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
: QLabel(text, parent, f), d(new NGradientLabelPrivate)
{
    /* setup default gradient policy */
    setGradientPolicy(DEFAULT_GRADIENT_POLICY);
    setLinearColorStart(DEFAULT_LINEAR_COLOR_START);
    setLinearColorStop(DEFAULT_LINEAR_COLOR_STOP);
}

NGradientLabel::~NGradientLabel()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

NGradientLabel::GradientPolicy NGradientLabel::gradientPolicy( ) const
{ 
    return d->gradient;
}

void NGradientLabel::setGradientPolicy(GradientPolicy policy)
{
    if (policy == d->gradient)
        return;

    switch (policy)
    {
    case LinearGradientHorizontal:
    case LinearGradientVertical:
        if (!isLinearPolicy(d->gradient))
        {
            d->gradientStops.clear( );
            d->gradientStops.resize(2); //one for start, one for stop
        }
        break;
    case NoGradientPolicy:
        d->gradientStops.clear( );
    default:
        break;
    }

    d->gradient = policy;
    update( );
}

void NGradientLabel::setLinearColorStart(const QColor &start)
{
    if (isLinearPolicy(d->gradient) && (start != d->gradientStops.first( ).second))
    {
        d->gradientStops.first( ) = QGradientStop(0, start);
        update( );
    }
}

void NGradientLabel::setLinearColorStop(const QColor &stop)
{
    if (isLinearPolicy(d->gradient) && (stop != d->gradientStops.last( ).second))
    {
        d->gradientStops.last( ) = QGradientStop(1, stop);
        update( );
    }
}

QColor NGradientLabel::linearColorStart( ) const
{
    if (isLinearPolicy(d->gradient))
        return d->gradientStops.first( ).second;
    else
        return QColor( );
}

QColor NGradientLabel::linearColorStop( ) const
{
    if (isLinearPolicy(d->gradient))
        return d->gradientStops.last( ).second;
    else
        return QColor( );
}

void NGradientLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    if (NoGradientPolicy == d->gradient)
        return;

    //FIXME: style paint ?
    //FIXME: support full gradient policy
    //FIXME: word wrap, Qt hasn't yet supported QPainter to draw gradient text on Qt-embedded-4.4.0, 
    //             use QPainterPath to draw the gradient text, but, QPainterPath is unable to word wrap.

    if (isLinearPolicy(d->gradient))
    {
        QLinearGradient gradient(contentsRect( ).topLeft( ),
                                 LinearGradientHorizontal == d->gradient ? contentsRect( ).topRight( ) : contentsRect( ).bottomLeft( ));
        gradient.setStops(d->gradientStops);

        QPainterPath pp;
        pp.addText(textRectangle( ).topLeft( ), font( ), text( ));

        QPainter painter(this);
        painter.eraseRect(contentsRect( ));
        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);
        painter.drawPath(pp);
    }
}

QRect NGradientLabel::textRectangle( ) const
{
    QFontMetrics fm=QFontMetrics(font( ));
    QRect rect=fm.boundingRect(text( ));

    if (alignment( ) & Qt::AlignLeft)
        rect.moveLeft(contentsRect( ).left( ));
    else if (alignment( ) & Qt::AlignRight)
        rect.moveLeft(contentsRect( ).left( ) + contentsRect( ).width( ) - rect.width( ));
    else
        rect.moveLeft(contentsRect( ).left( ) + (contentsRect( ).width( ) - rect.width( )) / 2);

    if (alignment( ) & Qt::AlignTop)
        rect.moveTop(contentsRect( ).top( ));
    else if (alignment( ) & Qt::AlignBottom)
        rect.moveTop(contentsRect( ).top( ) + contentsRect( ).height( ) - rect.height( ));
    else
        rect.moveTop(contentsRect( ).top( ) + (contentsRect( ).height( ) - rect.height( )) / 2);

    rect.moveTop(rect.top( )+ fm.ascent( ));

    return rect;
}

bool NGradientLabel::isLinearPolicy(GradientPolicy policy) const
{
    return((LinearGradientHorizontal == policy) || (LinearGradientVertical == policy));
}




NGradientLabelPrivate::NGradientLabelPrivate()
: gradient(NGradientLabel::NoGradientPolicy), gradientStops(0)
{
}

NGradientLabelPrivate::~NGradientLabelPrivate()
{
}



