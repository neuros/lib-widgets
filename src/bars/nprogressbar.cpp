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
 * NProgressBar implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-21 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPalette>
#include <QPainter>
#include "nprogressbar.h"
#include "nprogressbar_p.h"

NProgressBar::NProgressBar(QWidget *parent)
: QProgressBar(parent), d(new NProgressBarPrivate)
{
    setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QPalette pal = palette();
    pal.setColor(QPalette::Normal, QPalette::Window, QColor(36, 36, 36));
    pal.setColor(QPalette::Normal, QPalette::Highlight, QColor(0, 170, 255));
    setPalette(pal);
}

NProgressBar::~NProgressBar()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

QString NProgressBar::text() const
{
    return QProgressBar::text();
}




NProgressBarPrivate::NProgressBarPrivate()
{

}

NProgressBarPrivate::~NProgressBarPrivate()
{
}

