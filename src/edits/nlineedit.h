#ifndef _NLINEEDIT_H_
#define _NLINEEDIT_H_
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
 *  NlineEdit editbox header.
 *
 * REVISION:
 * 
 * 2) Import to OSD20. ----------------------------------- 2008-07-24 WX
 * 1) Initial creation. ----------------------------------- 2007-11-21 SZ
 *
 */

#include <QLineEdit>
#include <QKeyEvent>

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NLineEdit : public QLineEdit
#else
class NLineEdit : public QLineEdit
#endif
{
    Q_OBJECT
    Q_ENUMS(AcceptKeyMode)
    Q_PROPERTY(int acceptKeys READ acceptKeyMode WRITE setAcceptKeyMode)

public:
    enum AcceptKeyMode
    {
        AcceptAllKey = 0x01,
        AcceptNumericKey = 0x02,
        AcceptCursorMoveKey = 0x04,
        AcceptMiscKey = 0x08
    };

    NLineEdit(QWidget *parent = NULL);
    NLineEdit(const QString &contents, QWidget *parent = NULL);

    void setAcceptKeyMode(int akm) { acceptKeys = akm;}
    int acceptKeyMode( ) const { return acceptKeys;}

    virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const;

protected:
    void keyPressEvent(QKeyEvent *);
    virtual void inputMethodEvent(QInputMethodEvent *);

private:
    int acceptKeys;
};

#endif // _NLINEEDIT_H_
