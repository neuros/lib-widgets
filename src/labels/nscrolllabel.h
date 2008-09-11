#ifndef _NSCROLLLABEL_H_
#define _NSCROLLLABEL_H_
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
 * NScrollLabel implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-09-04 WX
 *
 */

#include <QLabel>

class NScrollLabelPrivate;

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NScrollLabel : public QLabel
#else
class NScrollLabel : public QLabel
#endif
{
    Q_OBJECT
    Q_PROPERTY(bool enable READ isEnable WRITE setEnable)
    Q_PROPERTY(int interval READ interval WRITE setInterval)

public:
    NScrollLabel(QWidget *parent = NULL, Qt::WindowFlags f = 0);
    NScrollLabel(const QString & text, QWidget *parent = NULL, Qt::WindowFlags f = 0);
    ~NScrollLabel();

    bool isEnable() const;

    int interval() const;
    void setInterval(int msec); 

public Q_SLOTS:
    void setEnable(bool enable);
    void start();
    void stop();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private Q_SLOTS:
    void OnTimerOut();

private:
    bool checkAnimation(bool active);

private:
    NScrollLabelPrivate *d;
};

#endif // _NSCROLLLABEL_H_
