#ifndef _NTIMEPROGRESSBAR_H_
#define _NTIMEPROGRESSBAR_H_
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
 * NTimeProgressBar Header
 *
 * REVISION:
 * 
 *
 * 2) Import to OSD20. ----------------------------------- 2008-07-29 WX
 * 1) Initial creation. ----------------------------------- 2007-11-30 TOM
 *
 *
 */

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
#endif
#include <QWidget>
#include <QList>

class NTimeMark
{
public:
    enum MarkType { MTBook = 0, MTClip }; 
    enum MarkProp { MPStart = 0, MPBoth };

    NTimeMark( )
    : markType(MTBook), markState(MPStart), markStart(0), markEnd(0) {}
    ~NTimeMark( ) {}

    inline bool operator==(const NTimeMark &other)
    { return markType == other.type( ) && markState == other.state( )
        && markStart == other.start( ) && markEnd == other.end( ); }
    
    inline MarkType type( ) const { return markType;}
    inline void setType(MarkType type) { markType = type;}
    inline MarkProp state( ) const { return markState;}
    inline void setState(MarkProp state) { markState = state;}
    inline int start( ) const { return markStart;}
    inline void setStart(int start) { markStart = start;}
    inline int end( ) const { return markEnd;}
    inline void setEnd(int end) { markEnd = end;}

private:
    MarkType markType;
    MarkProp markState;
    int markStart;
    int markEnd;
};

#if defined(DESIGNER)
class QDESIGNER_WIDGET_EXPORT NTimeProgressBar : public QWidget
#else
class NTimeProgressBar : public QWidget
#endif
{
    Q_OBJECT

    Q_PROPERTY(int minimumValue READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximumValue READ maximum WRITE setMaximum)
    Q_PROPERTY(int currentValue READ value WRITE setValue)
    Q_PROPERTY(bool currentTextVisible READ isCurrentTextVisible WRITE setCurrentTextVisible)
    Q_PROPERTY(bool totalTextVisible READ isTotalTextVisible WRITE setTotalTextVisible)
    Q_PROPERTY(QString textFormat READ format WRITE setFormat)

public:
    NTimeProgressBar(QWidget *parent = NULL);

    int maximum( ) const { return maximumValue; }
    int minimum( ) const { return minimumValue; }
    int value( ) const { return currentValue; }

    bool isCurrentTextVisible( ) const { return currentTextVisible; }
    void setCurrentTextVisible(bool enable);
    bool isTotalTextVisible( ) { return totalTextVisible; }
    void setTotalTextVisible(bool enable);

    QString format( ) const { return textFormat; }
    void setFormat(const QString &format);

    virtual QSize sizeHint( ) const;
    virtual QSize minimumSizeHint ( ) const;

public Q_SLOTS:
    void reset( );
    void setMaximum(int max);
    void setMinimum(int min);
    void setRange(int min, int max);
    void setValue(int v);
    void setFlag(const QList<NTimeMark> &flags); 

Q_SIGNALS:
    /* 
     * This signal is emitted when the value shown in the progress bar changes.
     * value is the new value shown by the progress bar.
     */
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawGradientRect(QPainter *painter, const QRect &rect, const QColor &from, const QColor &to, int direction);
    void drawGradientBar(QPainter *painter, const QRect &rect, const QColor &from, const QColor &to);
    void drawPost(QPainter *painter, const QRect &rect, const QColor &from, const QColor &to);
    void drawProgressBar(QPainter *painter, const QRect &rect, const QColor &from, const QColor &to);
    void drawPaintTimeMark(QPainter &painter);
    void computePos(void); //calculate position

private:
    int currentValue;
    int maximumValue;
    int minimumValue;

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
};

#endif // _NTIMEPROGRESSBAR_H_

