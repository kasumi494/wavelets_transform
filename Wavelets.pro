TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_RELEASE += -flto

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Ofast

SOURCES += main.cpp \
    wavelettransformator.cpp \
    haartransformator.cpp \
    daubechiestransformator.cpp

HEADERS += \
    wavelettransformator.hpp \
    haartransformator.hpp \
    daubechiestransformator.hpp


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
