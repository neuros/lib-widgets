#ifndef _NPROGRESSBAR_H_
#define _NPROGRESSBAR_H_
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
 * NProgressBar implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-21 WX
 *
 */

#include <QProgressBar>

class NProgressBarPrivate;

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NProgressBar : public QProgressBar
#else
class NProgressBar : public QProgressBar
#endif
{
    Q_OBJECT

public:
    NProgressBar(QWidget *parent = NULL);
    virtual ~NProgressBar();

    virtual QString text() const;

private:
    NProgressBarPrivate *d;
};

#endif // _NPROGRESSBAR_H_
