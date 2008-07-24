#ifndef _NCAPACITYBAR_H_
#define _NCAPACITYBAR_H_
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
 * NCapacityBar implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-21 WX
 *
 */

#include <QProgressBar>
#include <QMetaType>
#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NCapacityBar : public QProgressBar
#else
class NCapacityBar : public QProgressBar
#endif
{
    Q_OBJECT
    Q_ENUMS(CapacityType);
    Q_PROPERTY(CapacityType capacityType READ capacity WRITE setCapacity)

public:
    enum CapacityType { CapacityNone = 0, CapacityDiskSize };

    NCapacityBar(QWidget *parent = NULL);
    virtual ~NCapacityBar( );

    void setCapacity(CapacityType type);
    CapacityType capacity( ) const { return capacityType; }

    virtual QString text( ) const;

private:
    const char * CoolCreateReadableSizeString(unsigned long long size, unsigned long block_size,
                                              unsigned long display_unit) const;

private:
    CapacityType capacityType;
};

#endif // _NCAPACITYBAR_H_
