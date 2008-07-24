#ifndef _NPUSHBUTTON_H_
#define _NPUSHBUTTON_H_

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
 * NPushButton header.
 *
 * REVISION:
 * 
 * 2) Import to OSD20.--------------------------------2008-07-21 WX 
 * 1) Initial creation. ----------------------------------- 2008-05-16 nerochiaro
 *
 */

#include <QPushButton>
#include <QEvent>
#include <QKeyEvent>

/*
 * This class is needed to make Push buttons able to respond to ENTER key in the same 
 * way they respond to SPACE key. The problem is that in QT the ENTER key does not generate a full click
 * but we need it to generate one instead.
 *
 * PLEASE do not add to this class anything else. This class exist only for the purpose of doing 
 * what is described above and should not especially be used to implement button styles.
 *
 * @author   nerochiaro
 */

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NPushButton : public QPushButton
#else
class NPushButton : public QPushButton
#endif
{
    Q_OBJECT

public:
    NPushButton(QWidget *parent = NULL);
    NPushButton(const QString &text, QWidget *parent = NULL);
    NPushButton(const QIcon &icon, const QString &text, QWidget *parent = NULL);

protected:
    virtual void keyPressEvent(QKeyEvent *);

private:
    static const int AnimateClickDelay = 200;
};

#endif // _NPUSHBUTTON_H_
