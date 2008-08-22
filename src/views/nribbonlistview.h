#ifndef _NRIBBONLISTVIEW_H_
#define _NRIBBONLISTVIEW_H_

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
 * NRibbonListView implement header.
 *
 * REVISION:
 *
 * 3) Port to OSD20. ----------------------------------------------------------- 2008-08-12 WX
 * 2) Rename this widget and add fade effect to NRibbonListView. ------------ 2008-03-04 NW
 * 1) Initial creation. ----------------------------------- 2007-11-20 EY
 *
 */

#include "nlistview.h"

class NRibbonListViewPrivate;

#if defined(DESIGNER)
    #include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NRibbonListView : public NListView
#else
class NRibbonListView : public NListView
#endif
{
    Q_OBJECT
    Q_PROPERTY(bool showAllItemsIfFocusOut READ showAllItemsIfFocusOut WRITE setShowAllItemsIfFocusOut)

public:
    NRibbonListView(QWidget * parent = NULL);
    virtual ~NRibbonListView( );

    bool showAllItemsIfFocusOut( ) const;
    void setShowAllItemsIfFocusOut(bool show);

    virtual QRect visualRect(const QModelIndex &index) const;

protected:
    virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
    virtual void paintEvent(QPaintEvent *e);

private:
    void calculateToBeRendered( );

private:
    NRibbonListViewPrivate *d;
};


#endif // _NRIBBONLISTVIEW_H_
