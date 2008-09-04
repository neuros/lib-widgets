#ifndef _NTIMEPROGRESSBAR_P_H_
#define _NTIMEPROGRESSBAR_P_H_
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
 * NTimeProgressBarPrivate Header
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-09-04 WX
 *
 *
 */

class NTimeProgressBarPrivate
{
public:
    NTimeProgressBarPrivate();
    ~NTimeProgressBarPrivate();

    int value;
    int maximum;
    int minimum;

    bool totalTextVisible;
    bool currentTextVisible;
    QString textFormat;
    Qt::Alignment textAlignment;
    QList<NTimeMark> timeMarks;

    //paint depend
    QRect RetProg; //the area for active progress bar
    QRect RetGray; //the area for progress bar background
    QRect RetPost; //the area for the moving post
    QRect RetMark; //the area for the book mark
    QRect RetCurText; //the area for the total time text
    QRect RetTotText; //the area for the current time text

private:

};

#endif // _NTIMEPROGRESSBAR_P_H_

