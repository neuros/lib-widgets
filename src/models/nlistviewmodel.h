#ifndef _NLISTVIEWMODEL_H_
#define _NLISTVIEWMODEL_H_
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
 * NListViewModel implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-25 WX
 *
 */

#include <QAbstractListModel>
#include <QList>
#include "nlistviewmodel_p.h"
#include "nlistviewitem.h"

class NListViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
	NListViewModel(QObject * parent = NULL);
	~NListViewModel( );

    void clear( );
    bool appendRow(NListViewItem *item);
    bool appendRows(const QList<NListViewItem *> &items);
    bool insertRow(int row,  NListViewItem *item);
    bool insertRows(int row, const QList<NListViewItem *> &items);
    bool removeRow(int row);
    bool removeRows(int row, int count);

	virtual int rowCount(const QModelIndex &parent = QModelIndex( )) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    NListViewModelPrivate *d;
};

#endif // _NLISTVIEWMODEL_H_
