#Configure
TEMPLATE = lib
CONFIG += warn_on
TARGET = neux 
DESTDIR = ./build

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QT -= xml sql svg

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

HEADERS +=	./designer-plugins/nprogressbarplugin.h \
		./designer-plugins/nlineeditplugin.h \
		./designer-plugins/nlistviewplugin.h \
		./designer-plugins/ngradientlabelplugin.h \
		./designer-plugins/ndatetimelabelplugin.h \
		./designer-plugins/nhorizontalcomboboxplugin.h \
		./designer-plugins/npushbuttonplugin.h \
		./designer-plugins/nribbonlistviewplugin.h \
		./designer-plugins/nscrolllabelplugin.h \
		./designer-plugins/nstorageiconlabelplugin.h \
		./designer-plugins/ntimeprogressbarplugin.h \
		./designer-plugins/neux.h

SOURCES +=	./designer-plugins/nprogressbarplugin.cpp \
		./designer-plugins/nlineeditplugin.cpp \
		./designer-plugins/nlistviewplugin.cpp \
		./designer-plugins/ngradientlabelplugin.cpp \
		./designer-plugins/ndatetimelabelplugin.cpp \
		./designer-plugins/nhorizontalcomboboxplugin.cpp \
		./designer-plugins/npushbuttonplugin.cpp \
		./designer-plugins/nribbonlistviewplugin.cpp \
		./designer-plugins/nscrolllabelplugin.cpp \
		./designer-plugins/nstorageiconlabelplugin.cpp \
		./designer-plugins/ntimeprogressbarplugin.cpp \
		./designer-plugins/neux.cpp
} else {
INCLUDEPATH +=  ${TOOLCHAIN}/Qt/include/*
LIBS += -L${TOOLCHAIN}/Qt/lib
}


#Library
LIBS+=

#Source Files
SOURCES +=	./src/bars/nprogressbar.cpp \
		./src/bars/ntimemark.cpp \
		./src/bars/ntimeprogressbar.cpp \
		./src/boxes/nhorizontalcombobox.cpp \
		./src/buttons/npushbutton.cpp \
		./src/edits/nlineedit.cpp \
		./src/items/nitemdelegate.cpp \
		./src/labels/ngradientlabel.cpp \
		./src/labels/ndatetimelabel.cpp \
		./src/labels/nscrolllabel.cpp \
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
HEADERS +=	./src/bars/nprogressbar.h \
		./src/bars/ntimemark.h \
		./src/bars/ntimeprogressbar.h \
		./src/boxes/nhorizontalcombobox.h \
		./src/buttons/npushbutton.h \
		./src/edits/nlineedit.h \
		./src/items/nitemdelegate.h \
		./src/labels/ngradientlabel.h \
		./src/labels/ndatetimelabel.h \
		./src/labels/nscrolllabel.h \
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
rootfs.path = /${ROOTFS}/fs/lib
rootfs.files = ./build/*.so.1.0.0
rootfs.extra = cp -a ./build/* /${ROOTFS}/fs/lib

toolchain_include.path = /${TOOLCHAIN_USR_INSTALL}/include/neux
toolchain_include.files = $$HEADERS
				
toolchain_lib.path = /${TOOLCHAIN_USR_INSTALL}/lib
toolchain_lib.files = ./build/*.so.1.0.0
toolchain_lib.extra = cp -a ./build/* /${TOOLCHAIN_USR_INSTALL}/lib

INSTALLS += rootfs toolchain_include toolchain_lib
}


QMAKE_CLEAN = ./build/* ./Makefile ./tmp/* ./*~

