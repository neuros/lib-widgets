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
 * NStorageIconLabel implement routine.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2007-12-19 GL
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "nstorageiconlabel.h"

#define ICON_OSD (":/neux/osd.gif")
#define ICON_CF (":/neux/cf.gif")
#define ICON_MD (":/neux/md.gif")
#define ICON_MMC (":/neux/mmc.png")
#define ICON_MS (":/neux/ms.png")
#define ICON_SD (":/neux/sd.png")
#define ICON_USB (":/neux/usb.png")

NStorageIconLabel::NStorageIconLabel(QWidget *parent, Qt::WindowFlags f)
: QLabel(parent, f)
{
    setIcon(IconNone);
}

void NStorageIconLabel::setIcon(Icon icon)
{
	if(icon == storageIcon)
        return;

    storageIcon = icon;
    QString iconName;
    switch (storageIcon)
    {
    case IconOSD:
        iconName = ICON_OSD;
        break;
    case IconCF:
        iconName = ICON_CF;
        break;
    case IconMD:
        iconName = ICON_MD;
        break;
    case IconMMC:
        iconName = ICON_MMC;
        break;
    case IconMS:
        iconName = ICON_MS;
        break;
    case IconSD:
        iconName = ICON_SD;
        break;
    case IconUSB:
        iconName = ICON_USB;
        break;
    case IconNone:
    default:
        break;
    }

    //Note that QPixmaps are automatically added to the QPixmapCache when loaded from a file;
    //the key used is internal and can not be acquired.
    QPixmap iconPixmap(iconName);
    if (!iconPixmap.isNull( ))
        setPixmap(iconPixmap.scaled(size( )));
    else
        clear( );
}

