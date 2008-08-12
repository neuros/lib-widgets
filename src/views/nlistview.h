#ifndef _NLISTVIEW_H_
#define _NLISTVIEW_H_
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
 * NListView implement header.
 *
 * REVISION:
 * 
 * 2) Import to OSD20. ----------------------------------- 2008-07-25 WX
 * 1) Initial creation. ----------------------------------- 2007-11-08 EY
 *
 */

#include <QWidget>
#include <QListView>
#include <QTimeLine>
#include "nitemdelegate.h"

class NListViewPrivate;

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NListView : public QListView
#else
class NListView : public QListView
#endif
{
    Q_OBJECT
    Q_ENUMS(TextAnimationPolicy)
    Q_PROPERTY(TextAnimationPolicy textAnimation READ textAnimationPolicy WRITE setTextAnimationPolicy)
    Q_PROPERTY(int textAnimationInterval READ textAnimationInterval WRITE setTextAnimationInterval)
    Q_PROPERTY(Qt::Alignment textAlignment READ alignment WRITE setAlignment)
    Q_PROPERTY(bool itemWrapping READ isItemWrapping WRITE setItemWrapping)
    Q_PROPERTY(bool leftArrowEnable READ isLeftArrowEnable WRITE setLeftArrowEnable)
    Q_PROPERTY(QSize leftArrowSize READ leftArrowSize WRITE setLeftArrowSize)
    Q_PROPERTY(bool rightIconEnable READ isRightIconEnable WRITE setRightIconEnable)
    Q_PROPERTY(QSize rightIconSize READ rightIconSize WRITE setRightIconSize)

public:
    enum TextAnimationPolicy { AlwaysOff = 0, AsNeeded };

    NListView(QWidget * parent = NULL);
    ~NListView( );

    TextAnimationPolicy textAnimationPolicy( ) const;
    void setTextAnimationPolicy(TextAnimationPolicy policy);

    int textAnimationInterval( ) const;
    void setTextAnimationInterval(int interval);

    Qt::Alignment alignment( ) const;
    void setAlignment(Qt::Alignment alignment);

    bool isItemWrapping( ) const;
    void setItemWrapping(bool w);

    int currentRow( ) const;
    void setCurrentRow(int row);

    bool isLeftArrowEnable( ) const;
    void setLeftArrowEnable(bool enable);
    QSize leftArrowSize( ) const;
    void setLeftArrowSize(const QSize &size);

    bool isRightIconEnable( ) const;
    void setRightIconEnable(bool enable);
    QSize rightIconSize( ) const;
    void setRightIconSize(const QSize &size);

Q_SIGNALS:
    void currentRowChanged(int current, int previous);

protected:
    virtual QStyleOptionViewItem viewOptions( ) const;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent(QPaintEvent *event);

protected Q_SLOTS:
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void onAnimationFrameChanged(int frame);

private:
    void updateCurrent( );

private:
    NListViewPrivate *d;

};

#endif // _NLISTVIEW_H_

