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
		./src/labels

CONFIG(designer) {
DEFINES += DESIGNER
CONFIG += plugin

HEADERS +=	./designer-plugins/ncapacitybarplugin.h \
		./designer-plugins/ngradientlabelplugin.h \
		./designer-plugins/ndatetimelabelplugin.h \
		./designer-plugins/neux.h

SOURCES +=	./designer-plugins/ncapacitybarplugin.cpp \
		./designer-plugins/ngradientlabelplugin.cpp \
		./designer-plugins/ndatetimelabelplugin.cpp \
		./designer-plugins/neux.cpp
} else {
include (./config.pri)
}


#Library
LIBS+=

#Source Files
SOURCES +=	./src/bars/ncapacitybar.cpp \
		./src/labels/ngradientlabel.cpp \
		./src/labels/ndatetimelabel.cpp

#Header Files
HEADERS +=	./src/bars/ncapacitybar.h \
		./src/labels/ngradientlabel.h \
		./src/labels/ndatetimelabel.h

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

INSTALLS += designer_plugin
} else {
rootfs.files = ./build/*.so.1.0.0
rootfs.extra = cp -a ./build/* /${ROOTFS}/fs/lib
toolchain_include.files = 	./src/bars/*.h
				./src/labels/*.h
toolchain_lib.files = ./build/*.so.1.0.0
toolchain_lib.extra = cp -a ./build/* /${TOOLCHAIN_USR_INSTALL}/lib

INSTALLS += rootfs toolchain_include toolchain_lib
}


QMAKE_CLEAN = ./build/* ./Makefile ./tmp/* ./*~

