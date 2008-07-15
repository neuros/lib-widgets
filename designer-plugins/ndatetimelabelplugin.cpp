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
 * NDateTimeLabelPlugin source
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-08 WX
 *
 */

#include "ndatetimelabel.h"
#include "ndatetimelabelplugin.h"
#include <QtPlugin>

NDateTimeLabelPlugin::NDateTimeLabelPlugin(QObject *parent)
: QObject(parent), initialized(false)
{
}

void NDateTimeLabelPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    Q_UNUSED(formEditor);
    if (initialized)
        return;

    initialized = true;
}

bool NDateTimeLabelPlugin::isInitialized( ) const
{
    return initialized;
}

QWidget *NDateTimeLabelPlugin::createWidget(QWidget *parent)
{
    return new NDateTimeLabel(parent);
}

QString NDateTimeLabelPlugin::name( ) const
{
    return "NDateTimeLabel";
}

QString NDateTimeLabelPlugin::group( ) const
{
    return "Neux";
}

QIcon NDateTimeLabelPlugin::icon( ) const
{
    return QIcon( );
}

QString NDateTimeLabelPlugin::toolTip( ) const
{
    return "";
}

QString NDateTimeLabelPlugin::whatsThis( ) const
{
    return "";
}

QString NDateTimeLabelPlugin::includeFile( ) const
{
    return "ndatetimelabel.h";
}

bool NDateTimeLabelPlugin::isContainer( ) const
{
    return false;
}

QString NDateTimeLabelPlugin::domXml( ) const
{
    return "<widget class=\"NDateTimeLabel\" name=\"datetimeLabel\">\n"
    " <property name=\"geometry\">\n"
    "  <rect>\n"
    "   <x>0</x>\n"
    "   <y>0</y>\n"
    "   <width>100</width>\n"
    "   <height>100</height>\n"
    "  </rect>\n"
    " </property>\n"
    " <property name=\"toolTip\" >\n"
    "  <string>Neuros Date and Time QLabel</string>\n"
    " </property>\n"
    " <property name=\"whatsThis\" >\n"
    "  <string>Inherited from QLabel, custom it for displaying the date and time.</string>\n"
    " </property>\n"
    "</widget>\n";
}

