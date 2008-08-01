#ifndef _NHORIZONTALCOMBOBOX_H_
#define _NHORIZONTALCOMBOBOX_H_
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
 * NHorizontalComboBox header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-22 WX
 *
 */

#include <QComboBox>
#include <QStringList>

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NHorizontalComboBox : public QComboBox
#else
class NHorizontalComboBox : public QComboBox
#endif
{
    Q_OBJECT
    Q_ENUMS(PlayRole)
    Q_PROPERTY(PlayRole role READ playRole WRITE setPlayRole)
    Q_PROPERTY(bool wrapping READ isWrapping WRITE setWrapping)

public:
    enum PlayRole { PlayAsComboBox = 0, PlayAsSpinBox };

	explicit NHorizontalComboBox(QWidget *parent = NULL);

    PlayRole playRole( ) const { return role; }
    void setPlayRole(PlayRole pr);

    bool isWrapping( ) const { return wrapping; }
    void setWrapping(bool w) { wrapping = w; }

    QSize sizeHint() const;

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    QStringList createNumericTexts(int from, int to) const;

private:
    PlayRole role;
    bool wrapping;

};

#endif // _NHORIZONTALCOMBOBOX_H_
