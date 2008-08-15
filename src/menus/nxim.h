#ifndef _NXIM_H_
#define _NXIM_H_
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
 * NXim Header.
 *
 * REVISION:
 *
 * 2) Import to OSD20 ----------------------------------- 2008-07-31 WX
 * 1) Initial creation. ----------------------------------- 2007-11-28 NW
 *
 */

#include <QMenu>
#include <QStyleOption>

class NXimPrivate;

class NXim : public QMenu
{
    Q_OBJECT

    public:
    NXim(QWidget *parent = NULL);
    NXim(const QString &title, QWidget *parent = NULL);
    virtual ~NXim( );
    virtual QSize sizeHint( ) const;

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    QList<QAction *> getVisibleActions( ) const;
    void drawBackground(QPainter *painter, const QStyleOption &option, const QRect &rect) const;
    void drawHeader(QPainter *painter, const QStyleOptionHeader &option, const QRect &rect) const;
    void drawCursor(QPainter *painter, const QStyleOptionMenuItem &option, const QRect &rect) const;

private:
    NXimPrivate *d;
};

#endif // _NXIM_H_
