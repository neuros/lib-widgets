#ifndef _NGRADIENTLABEL_H_
#define _NGRADIENTLABEL_H_
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
 * NGradientLabel header
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-07 WX
 *
 */

#include <QLabel>
#include <QColor>

class NGradientLabelPrivate;

/*
 * 'QDESIGNER_WIDGET_EXPORT' macro is used when defining custom widgets 
 * to ensure that they are correctly exported from plugins for use with Qt Designer.
 */
#if defined(DESIGNER)
#include <QtDesigner/QDesignerExportWidget>
class QDESIGNER_WIDGET_EXPORT NGradientLabel : public QLabel
#else
class NGradientLabel : public QLabel
#endif
{
    /*
     * 'Q_OBJECT' macro must appear in the private section of a class definition
     * that declares its own signals and slots
     * or that uses other services provided by Qt's meta-object system.
     */
    Q_OBJECT

    /*
     * 'Q_ENUMS' macro registers one or several enum types to the meta-object system.
     */
    Q_ENUMS(GradientPolicy)

    /*
     * 'Q_PROPERTY' macro is used for declaring properties in classes that inherit QObject.
     * Properties behave like class data members, 
     * but they have additional features accessible through the Meta-Object System.
     */
    Q_PROPERTY(GradientPolicy gradient READ gradientPolicy WRITE setGradientPolicy)
    Q_PROPERTY(QColor linearStartColor READ linearColorStart WRITE setLinearColorStart)
    Q_PROPERTY(QColor linearStopColor READ linearColorStop WRITE setLinearColorStop)

public:
    enum GradientPolicy
    {
        NoGradientPolicy = 0,
        LinearGradientHorizontal,
        LinearGradientVertical
    };

    explicit NGradientLabel(QWidget *parent = NULL, Qt::WindowFlags f = 0);
    explicit NGradientLabel(const QString &text, QWidget *parent = NULL, Qt::WindowFlags f = 0);
    ~NGradientLabel();

    void setGradientPolicy(GradientPolicy policy);
    GradientPolicy gradientPolicy( ) const;

    void setLinearColorStart(const QColor &start);
    void setLinearColorStop(const QColor &stop);
    QColor linearColorStart( ) const;
    QColor linearColorStop( ) const;

Q_SIGNALS:
    void gradientChanged(GradientPolicy current, GradientPolicy previous);

protected:
    void paintEvent(QPaintEvent *event);

private:
    bool isLinearPolicy(GradientPolicy policy) const;
    QRect textRectangle( ) const;

private:
    NGradientLabelPrivate *d;
};

#endif // _NGRADIENTLABEL_H_
