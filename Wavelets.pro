TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    wavelettransformator.cpp \
    haartransformator.cpp

HEADERS += \
    wavelettransformator.hpp \
    haartransformator.hpp


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
