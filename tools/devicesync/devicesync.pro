
QT       += core

QT       -= gui

TARGET = devicesync
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    BTAdaptor.cpp \
    DeviceSync.cpp

HEADERS += \
    BTAdaptor.h \
    DeviceSync.h
