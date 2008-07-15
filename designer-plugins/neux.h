#ifndef _NEUX_H_
#define _NEUX_H_
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
 * Neux header
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-15 WX
 *
 */

#include <QtDesigner/QtDesigner>
#include <QtCore/qplugin.h>

class Neux : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    Neux(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets( ) const;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};


#endif // _NEUXPLUGIN_H_
