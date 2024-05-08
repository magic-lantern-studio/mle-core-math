QT -= gui

TEMPLATE = lib
DEFINES += MLMATH_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += MLE_NOT_DLL

INCLUDEPATH += $$PWD/../../common/include /opt/MagicLantern/include

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/../../common/src/asine.cxx \
    $$PWD/../../common/src/atan.cxx \
    $$PWD/../../common/src/fixed.cxx \
    $$PWD/../../common/src/recip.cxx \
    $$PWD/../../common/src/rotation.cxx \
    $$PWD/../../common/src/scalar.cxx \
    $$PWD/../../common/src/sine.cxx \
    $$PWD/../../common/src/sqrt.cxx \
    $$PWD/../../common/src/transfrm.cxx \
    $$PWD/../../common/src/vector.cxx

HEADERS += \
    $$PWD/../../common/include/math/3dmath.h \
    $$PWD/../../common/include/math/anglebr.h \
    $$PWD/../../common/include/math/angle.h \
    $$PWD/../../common/include/math/asine.h \
    $$PWD/../../common/include/math/atan.h \
    $$PWD/../../common/include/math/mlmath.h \
    $$PWD/../../common/include/math/recip.h \
    $$PWD/../../common/include/math/rotation.h \
    $$PWD/../../common/include/math/scalar.h \
    $$PWD/../../common/include/math/sine.h \
    $$PWD/../../common/include/math/sqrt.h \
    $$PWD/../../common/include/math/transfrm.h \
    $$PWD/../../common/include/math/trig.h \
    $$PWD/../../common/include/math/vector.h

# Default rules for deployment.
unix {
    target.path = /opt/MagicLantern/lib
    headers.path = /opt/MagicLantern/include/math
    headers.files = $$HEADERS
    INSTALLS += target headers
}
#!isEmpty(target.path): INSTALLS += target
