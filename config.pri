DEPENDPATH += 
INCLUDEPATH +=	${TOOLCHAIN}/Qt/include/*
LIBS += -L${TOOLCHAIN}/Qt/lib

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QT -= xml sql svg

rootfs.path = /${ROOTFS}/fs/lib
toolchain_include.path = /${TOOLCHAIN_USR_INSTALL}/include/neux
toolchain_lib.path = /${TOOLCHAIN_USR_INSTALL}/lib
