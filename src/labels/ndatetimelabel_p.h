#ifndef _NDATETIMELABEL_P_H_
#define _NDATETIMELABEL_P_H_
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
 * NDateTimeLabelPrivate header
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-08-27 WX
 *
 */

#include <QColor>
#include <QTimer>
#include <QDateTime>
#include <QPainterPath>
#include "ndatetimelabel.h"

class NDateTimeLabelPrivate
{
public:
    NDateTimeLabelPrivate();
    ~NDateTimeLabelPrivate();

    QPainterPath roundRectPath(const QRect &rect) const;

    QTimer refreshTimer;
    Qt::DateFormat dateTimeFormat;
    NDateTimeLabel::DisplayRole role;
    int borderWidth;
    QColor borderColor;
    QColor topColor;
    QColor bottomColor;
    QPainterPath rectPath;

private:

};

#endif // _NDATETIMELABEL_P_H_
