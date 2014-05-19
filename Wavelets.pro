TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS +=


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
