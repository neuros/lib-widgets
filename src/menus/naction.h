#ifndef _NACTION_H_
#define _NACTION_H_
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
 * neuros action header.
 *
 * REVISION:
 *
 * 2) Import to OSD20. ----------------------------------- 2008-07-31 WX
 * 1) Initial creation. ----------------------------------- 2007-03-04 GL
 *
 */

#include <QAction>

class NActionPrivate;

class NAction : public QAction
{
    Q_OBJECT

    public:
    enum ActionType
    {
        ActionLocal = 0, ActionGlobal
    };

    NAction(QObject * parent, ActionType at = ActionLocal);
    NAction(const QString &text, QObject *parent, ActionType at = ActionLocal);
    NAction(const QIcon &icon, const QString &text, QObject *parent, ActionType at = ActionLocal);
    ~NAction( );

    ActionType type( ) const;
    void setType(ActionType at);

private:
    NActionPrivate *d;

};

#endif // _NACTION_H_
