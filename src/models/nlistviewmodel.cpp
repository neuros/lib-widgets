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
 * NListViewModel implement routines.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-25 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "nlistviewmodel.h"
#include "nlistviewmodel_p.h"

NListViewModel::NListViewModel(QObject *parent)
: QAbstractListModel(parent), d(new NListViewModelPrivate)
{
}

NListViewModel::~NListViewModel( )
{
    if (NULL != d)
    {
        delete d;
        d = NULL;
    }
}

void NListViewModel::clear( )
{
    d->clear( );
    reset( );
}

bool NListViewModel::appendRow(NListViewItem *item)
{
    return insertRows(rowCount( ), QList<NListViewItem *>( ) << item);
}

bool NListViewModel::appendRows(const QList<NListViewItem *> &items)
{
    return insertRows(rowCount( ), items);
}

bool NListViewModel::insertRow(int row,  NListViewItem *item)
{
    return insertRows(row, QList<NListViewItem *>( ) << item);
}

bool NListViewModel::insertRows(int row, const QList<NListViewItem *> &items)
{
    if (row < 0 || row > rowCount( ))
        return false;

    int count = items.count( );
    beginInsertRows(QModelIndex( ), row, row + count - 1);
    for (int i = 0; i < count; ++ i)
        d->modelDatas.insert(row ++, items.at(i));
    endInsertRows( );
    return true;
}

bool NListViewModel::removeRow(int row)
{
    return removeRows(row, 1);
}

bool NListViewModel::removeRows(int row, int count)
{
    if (count < 1 || row < 0 || row >= rowCount( ))
        return false;

    if (row + count > rowCount( ))
        count = rowCount( ) - row;

    beginRemoveRows(QModelIndex( ), row, row + count - 1);
    while ((count --) > 0) {
        delete d->modelDatas.takeAt(row);
    }
    endRemoveRows( );
    return true;
}

int NListViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid( ))
        return 0;

	return d->modelDatas.count( );
}

QVariant NListViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid( ) || index.row( ) >= d->modelDatas.count())
        return QVariant( );

    return d->modelDatas.at(index.row( ))->data(role);
}



NListViewModelPrivate::NListViewModelPrivate( )
{
}

NListViewModelPrivate::~NListViewModelPrivate( )
{
    clear( );
}

void NListViewModelPrivate::clear( )
{
    qDeleteAll(modelDatas);
    modelDatas.clear( );
}
