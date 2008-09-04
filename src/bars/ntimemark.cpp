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
 * NProgressBar implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-21 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "ntimemark.h"
#include "ntimemark_p.h"

NTimeMark::NTimeMark()
: d(new NTimeMarkPrivate) 
{
}

NTimeMark::~NTimeMark()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

bool NTimeMark::operator==(const NTimeMark &other)
{ 
    return d->type == other.type() && d->state == other.state()
    && d->start == other.start() && d->end == other.end();
}

NTimeMark::MarkType NTimeMark::type() const
{ 
    return d->type;
}

void NTimeMark::setType(MarkType type)
{ 
    d->type = type;
}

NTimeMark::MarkProp NTimeMark::state() const
{ 
    return d->state;
}

void NTimeMark::setState(MarkProp state)
{ 
    d->state = state;
}

int NTimeMark::start() const
{ 
    return d->start;
}

void NTimeMark::setStart(int start)
{ 
    d->start = start;
}

int NTimeMark::end() const
{ 
    return d->end;
}

void NTimeMark::setEnd(int end)
{ 
    d->end = end;
}





NTimeMarkPrivate::NTimeMarkPrivate()
: type(NTimeMark::MTBook), state(NTimeMark::MPStart), start(0), end(0)
{
}

NTimeMarkPrivate::~NTimeMarkPrivate()
{
}
