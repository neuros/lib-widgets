#ifndef _NPROGRESSBAR_H_
#define _NPROGRESSBAR_H_
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
 * NTimeMark implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-21 WX
 *
 */

class NTimeMarkPrivate;

class NTimeMark
{
    Q_ENUMS(MarkType)
    Q_ENUMS(MarkProp)
    Q_PROPERTY(MarkType type READ type WRITE setType)
    Q_PROPERTY(MarkProp state READ state WRITE setState)
    Q_PROPERTY(int start READ start WRITE setStart)
    Q_PROPERTY(int end READ end WRITE setEnd)

public:
    enum MarkType { MTBook = 0, MTClip }; 
    enum MarkProp { MPStart = 0, MPBoth };

    NTimeMark();
    virtual ~NTimeMark();

    bool operator==(const NTimeMark &other);

    MarkType type() const;
    void setType(MarkType type);
    MarkProp state() const;
    void setState(MarkProp state);
    int start() const;
    void setStart(int start);
    int end() const;
    void setEnd(int end);

private:
    NTimeMarkPrivate *d;
};

#endif // _NPROGRESSBAR_H_
