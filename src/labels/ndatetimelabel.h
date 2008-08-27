#ifndef _NDATETIMELABEL_H_
#define _NDATETIMELABEL_H_
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
 * NDateTimeLabel header
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-08 WX
 *
 */

#include <QLabel>
#include <QColor>
#include <QTimer>
#include <QDateTime>

class NDateTimeLabelPrivate;

#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NDateTimeLabel : public QLabel
#else
class NDateTimeLabel : public QLabel
#endif
{
    Q_OBJECT

    Q_ENUMS(DisplayRole)
    Q_PROPERTY(DisplayRole role READ displayRole WRITE setDisplayRole)
    Q_PROPERTY(int refreshInterval READ refreshInterval WRITE setRefreshInterval)
    Q_PROPERTY(Qt::DateFormat dateTimeFormat READ format WRITE setFormat)

public:
    enum DisplayRole
    {
        DateAndTime = 0,
        TimeOnly,
        DateOnly
    };

    explicit NDateTimeLabel(QWidget *parent = NULL, Qt::WindowFlags f = 0);
    ~NDateTimeLabel();

    void refresh();

    void setRefreshInterval(int msec);
    int refreshInterval() const;

    void setFormat(Qt::DateFormat format);
    Qt::DateFormat format() const;

    void setDisplayRole(DisplayRole r);
    DisplayRole displayRole() const;

    Q_SIGNALS:
    void datetimeUpdated(const QDateTime &current);

public Q_SLOTS:
    void start();
    void stop();

private Q_SLOTS:
    void OnRefreshTimerOut();

protected:
    void paintEvent(QPaintEvent *event);

private:
    NDateTimeLabelPrivate *d;
};

#endif // _NDATETIMELABEL_H_
