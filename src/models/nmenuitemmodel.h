#ifndef _NMENUITEMMODEL_H_
#define _NMENUITEMMODEL_H_
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
 * NMenuItemModel implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2007-11-27 SZ
 *
 */

#include <QAbstractListModel>
#include <QList>
#include "nmenuitem.h"

class NMenuItemModelPrivate;

class NMenuItemModel :  public QAbstractListModel
{
    Q_OBJECT

public:
    NMenuItemModel(QObject * parent = NULL);
    ~NMenuItemModel();

    void clear();
    bool appendRow(NMenuItem *item);
    bool appendRows(const QList<NMenuItem *> &items);
    bool insertRow(int row,  NMenuItem *item);
    bool insertRows(int row, const QList<NMenuItem *> &items);
    bool removeRow(int row);
    bool removeRows(int row, int count);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    NMenuItemModelPrivate *d;

};

#endif // _NMENUITEMMODEL_H_
