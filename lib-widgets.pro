#Configure
TEMPLATE = lib
CONFIG += warn_on
TARGET = neux 
DESTDIR = ./build

#Temporary Directory
MOC_DIR =	./tmp
UI_DIR =	./tmp
OBJECTS_DIR =	./tmp
RCC_DIR	=	./tmp

INCLUDEPATH +=	./tmp \
		./src/bars \
		./src/boxes \
		./src/buttons \
		./src/edits \
		./src/items \
		./src/labels \
		./src/menus \
		./src/models \
		./src/views

CONFIG(designer) {
DEFINES += DESIGNER
CONFIG += plugin

HEADERS +=	./designer-plugins/ncapacitybarplugin.h \
		./designer-plugins/nlineeditplugin.h \
		./designer-plugins/nlistviewplugin.h \
		./designer-plugins/ngradientlabelplugin.h \
		./designer-plugins/ndatetimelabelplugin.h \
		./designer-plugins/nhorizontalcomboboxplugin.h \
		./designer-plugins/npushbuttonplugin.h \
		./designer-plugins/nribbonlistviewplugin.h \
		./designer-plugins/nstorageiconlabelplugin.h \
		./designer-plugins/ntimeprogressbarplugin.h \
		./designer-plugins/neux.h

SOURCES +=	./designer-plugins/ncapacitybarplugin.cpp \
		./designer-plugins/nlineeditplugin.cpp \
		./designer-plugins/nlistviewplugin.cpp \
		./designer-plugins/ngradientlabelplugin.cpp \
		./designer-plugins/ndatetimelabelplugin.cpp \
		./designer-plugins/nhorizontalcomboboxplugin.cpp \
		./designer-plugins/npushbuttonplugin.cpp \
		./designer-plugins/nribbonlistviewplugin.cpp \
		./designer-plugins/nstorageiconlabelplugin.cpp \
		./designer-plugins/ntimeprogressbarplugin.cpp \
		./designer-plugins/neux.cpp
} else {
include (./config.pri)
}


#Library
LIBS+=

#Source Files
SOURCES +=	./src/bars/ncapacitybar.cpp \
		./src/bars/ntimeprogressbar.cpp \
		./src/boxes/nhorizontalcombobox.cpp \
		./src/buttons/npushbutton.cpp \
		./src/edits/nlineedit.cpp \
		./src/items/nitemdelegate.cpp \
		./src/labels/ngradientlabel.cpp \
		./src/labels/ndatetimelabel.cpp \
		./src/labels/nstorageiconlabel.cpp \
		./src/menus/naction.cpp \
		./src/menus/nxim.cpp \
		./src/models/nlistviewitem.cpp \
		./src/models/nlistviewmodel.cpp \
		./src/models/nmenuitem.cpp \
		./src/models/nmenuitemmodel.cpp \
		./src/views/nlistview.cpp \
		./src/views/nribbonlistview.cpp

#Header Files
HEADERS +=	./src/bars/ncapacitybar.h \
		./src/bars/ntimeprogressbar.h \
		./src/boxes/nhorizontalcombobox.h \
		./src/buttons/npushbutton.h \
		./src/edits/nlineedit.h \
		./src/items/nitemdelegate.h \
		./src/labels/ngradientlabel.h \
		./src/labels/ndatetimelabel.h \
		./src/labels/nstorageiconlabel.h \
		./src/menus/naction.h \
		./src/menus/nxim.h \
		./src/models/nlistviewitem.h \
		./src/models/nlistviewmodel.h \
		./src/models/nmenuitem.h \
		./src/models/nmenuitemmodel.h \
		./src/views/nlistview.h \
		./src/views/nribbonlistview.h

#Form Files
FORMS +=

#Translation Files
TRANSLATIONS +=

#Resource files
RESOURCES += ./resources/neux.qrc

#Install
CONFIG(designer) {
designer_plugin.path = $$[QT_INSTALL_PLUGINS]/designer
designer_plugin.files = ./build/*
designer_plugin.extra = cp -a ./build/* $$[QT_INSTALL_PLUGINS]/designer

designer_include.path = $$[QT_INSTALL_HEADERS]/neux
designer_include.files = $$HEADERS

INSTALLS += designer_plugin designer_include
} else {
rootfs.files = ./build/*.so.1.0.0
rootfs.extra = cp -a ./build/* /${ROOTFS}/fs/lib

toolchain_include.files =./src/bars/*.h \
			 ./src/boxes/*.h \
			 ./src/buttons/*.h \
			 ./src/edits/*.h \
			 ./src/items/*.h \
			 ./src/labels/*.h \
			 ./src/menus/*.h \
			 ./src/models/*.h \
			 ./src/views/*.h
				
toolchain_lib.files = ./build/*.so.1.0.0
toolchain_lib.extra = cp -a ./build/* /${TOOLCHAIN_USR_INSTALL}/lib

INSTALLS += rootfs toolchain_include toolchain_lib
}


QMAKE_CLEAN = ./build/* ./Makefile ./tmp/* ./*~

