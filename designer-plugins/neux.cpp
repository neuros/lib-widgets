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
 * Neux source
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-07-15 WX
 *
 */

#include "neux.h"
#include "ngradientlabelplugin.h"
#include "ndatetimelabelplugin.h"
#include "ncapacitybarplugin.h"
#include "nlineeditplugin.h"
#include "npushbuttonplugin.h"
#include "nstorageiconlabelplugin.h"
#include "ntimeprogressbarplugin.h"

Neux::Neux(QObject *parent)
: QObject(parent)
{
    widgets.append(new NCapacityBarPlugin(this));
    widgets.append(new NGradientLabelPlugin(this));
    widgets.append(new NDateTimeLabelPlugin(this));
    widgets.append(new NLineEditPlugin(this));
    widgets.append(new NPushButtonPlugin(this));
    widgets.append(new NStorageIconLabelPlugin(this));
    widgets.append(new NTimeProgressBarPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> Neux::customWidgets( ) const
{
    return widgets;
}

/*
 * Export custom widget plugin to Qt Designer
 * Q_EXPORT_PLUGIN2(PluginName, ClassName)
 * This macro exports the plugin class ClassName for the plugin specified 
 * by PluginName. 
 * The value of PluginName should correspond 
 * to the TARGET specified in the plugin's project file.
 */
Q_EXPORT_PLUGIN2(neux, Neux)
