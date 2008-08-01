#ifndef _NHORIZONTALCOMBOBOXPLUGIN_H_
#define _NHORIZONTALCOMBOBOXPLUGIN_H_
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
 * NHorizontalComboBoxPlugin header
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-21 WX
 *
 */

#include <QDesignerCustomWidgetInterface>

/*
 * Note: That the only part of the class definition 
 *          that is specific to this particular custom widget is the class name.
 */
class NHorizontalComboBoxPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    /*
     * The Q_OBJECT macro must appear in the private section of a class definition
     * that declares its own signals and slots or that uses other services
     * provided by Qt's meta-object system.
     */
    Q_OBJECT

    /*
     * since we are implementing an interface,
     * we must ensure that it's made known to the meta object system
     * using the Q_INTERFACES( ) macro. 
     * This enables Qt Designer to use the qobject_cast( ) function 
     * to query for supported interfaces using nothing but a QObject pointer.
     */
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    NHorizontalComboBoxPlugin(QObject *parent = NULL);

    bool isContainer( ) const;
    bool isInitialized( ) const;
    QIcon icon( ) const;
    QString domXml( ) const;
    QString group( ) const;
    QString includeFile( ) const;
    QString name( ) const;
    QString toolTip( ) const;
    QString whatsThis( ) const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *formEditor);

private:
    bool initialized;
};

#endif // _NHORIZONTALCOMBOBOXPLUGIN_H_

