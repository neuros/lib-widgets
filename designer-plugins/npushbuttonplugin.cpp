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
 * NPushButtonPlugin source
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-21 WX
 *
 */

#include "npushbutton.h"
#include "npushbuttonplugin.h"
#include <QtPlugin>

NPushButtonPlugin::NPushButtonPlugin(QObject *parent)
: QObject(parent), initialized(false)
{
}

/*
 * Initializes the widget for use with the specified formEditor interface.
 * Sets up extensions and other features for custom widgets.
 * Custom container extensions (see QDesignerContainerExtension)
 * and task menu extensions (see QDesignerTaskMenuExtension)
 * should be set up in this function.
 */
void NPushButtonPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    Q_UNUSED(formEditor);
    if (initialized)
        return;

    initialized = true;
}

/*
 * Returns true if the widget has been initialized, otherwise returns false.
 * Reimplementations usually check whether the initialize( ) function
 * has been called and return the result of this test.
 */
bool NPushButtonPlugin::isInitialized( ) const
{
    return initialized;
}

/*
 * Returns a new instance of the custom widget, with the given parent.
 */
QWidget *NPushButtonPlugin::createWidget(QWidget *parent)
{
    return new NPushButton(parent);
}

/*
 * Returns the class name of the custom widget supplied by the interface.
 * The name returned must be identical to the class name 
 * used for the custom widget.
 */
QString NPushButtonPlugin::name( ) const
{
    return "NPushButton";
}

/*
 * Returns the name of the group to which the custom widget belongs.
 */
QString NPushButtonPlugin::group( ) const
{
    return "Neux";
}

/*
 * Returns the icon used to represent the custom widget in Qt Designer's widget box.
 */
QIcon NPushButtonPlugin::icon( ) const
{
    return QIcon( );
}

/*
 * Returns a short description of the widget that can be used 
 * by Qt Designer in a tool tip.
 */
QString NPushButtonPlugin::toolTip( ) const
{
    return "";
}

/*
 * Returns a description of the widget that can be used
 * by Qt Designer in "What's This?" help for the widget.
 */
QString NPushButtonPlugin::whatsThis( ) const
{
    return "";
}

/*
 * Returns the path to the include file that uic uses when creating code for the custom widget.
 * The header file that must be included in applications that use this widget. 
 * This information is stored in .ui files and will be used by uic 
 * to create a suitable #includes statement in the code it generates
 * for the form containing the custom widget.
 */
QString NPushButtonPlugin::includeFile( ) const
{
    return "npushbutton.h";
}

/*
 * True if the widget will be used to hold child widgets; otherwise false.
 */
bool NPushButtonPlugin::isContainer( ) const
{
    return false;
}

/*
 * Returns the XML that is used to describe the custom widget's properties to Qt Designer.
 */
QString NPushButtonPlugin::domXml( ) const
{
    return "<widget class=\"NPushButton\" name=\"pushButton\"> </widget>\n";
}

