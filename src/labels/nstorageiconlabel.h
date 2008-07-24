#ifndef _NSTORAGEICONLABEL_H_
#define _NSTORAGEICONLABEL_H_
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
 * NStorageIconLabel implement header.
 *
 * REVISION:
 * 
 * 2) Import to OSD20. ----------------------------------- 2008-07-22 WX
 * 1) Initial creation. ----------------------------------- 2007-12-19 GL
 *
 */

#include <QLabel>
#include <QResizeEvent>
#include <QPixmap>

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NStorageIconLabel : public QLabel
#else
class NStorageIconLabel : public QLabel
#endif
{
    Q_OBJECT
    Q_ENUMS(Icon)
    Q_PROPERTY(Icon storageIcon READ icon WRITE setIcon)

public:
    enum Icon { IconNone = 0, IconOSD, IconCF, IconMD, IconMMC, IconMS, IconSD, IconUSB };

    NStorageIconLabel(QWidget *parent = NULL, Qt::WindowFlags f = 0);

    void setIcon (Icon icon);
    Icon icon( ) const { return storageIcon; }

private:
    Icon storageIcon;
};

#endif // _NSTORAGEICONLABEL_H_
