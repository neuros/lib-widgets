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
 * NCapacityBar implement routines.
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
#include "ncapacitybar.h"

NCapacityBar::NCapacityBar(QWidget *parent)
: QProgressBar(parent)
{
    setCapacity(CapacityNone);
}

NCapacityBar::~NCapacityBar( )
{
}

void NCapacityBar::setCapacity(CapacityType type)
{
    if (type == capacityType)
        return;

    capacityType = type;
    update( );
}

QString NCapacityBar::text( ) const
{
    switch (capacityType)
    {
    case CapacityNone:
    case CapacityDiskSize:
        //FIXME: Custom the text for disk capacity("1.8G free of 2G")
    default:
        return QProgressBar::text( );
    }
}

/* Copy from Neuros-Cooler/core */
const char *
NCapacityBar::CoolCreateReadableSizeString(unsigned long long size,
                                           unsigned long block_size, unsigned long display_unit) const
{
    #define KILOBYTE 1024
    /* The code will adjust for additional (appended) units. */
    static const char zero_and_units[] = { '0', 0, 'K', 'M', 'G', 'T'};
    static const char fmt[] = "%Lu";
    static const char fmt_tenths[] = "%Lu.%d %c";
    static char str[21];        /* Sufficient for 64 bit unsigned integers. */

    unsigned long long val;
    int frac;
    const char *u;
    const char *f;

    u = zero_and_units;
    f = fmt;
    frac = 0;

    val = size * block_size;
    if (val == 0)
        return u;

    if (display_unit)
    {
        val += display_unit/2;  /* Deal with rounding. */
        val /= display_unit;    /* Don't combine with the line above!!! */
    }
    else
    {
        ++u;
        while ((val >= KILOBYTE)
               && (u < zero_and_units + sizeof(zero_and_units) - 1))
        {
            f = fmt_tenths;
            ++u;
            frac = ((((int)(val % KILOBYTE)) * 10) + (KILOBYTE/2)) / KILOBYTE;
            val /= KILOBYTE;
        }
        if (frac >= 10)
        {
            ++val;
            frac = 0;
        }
    }

    snprintf(str, sizeof(str), f, val, frac, *u);
    return str;
}

