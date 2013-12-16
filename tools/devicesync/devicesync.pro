#-------------------------------------------------
#
# Project created by QtCreator 2013-12-09T05:59:40
#
#-------------------------------------------------

QT       += core dbus

QT       -= gui

TARGET = devicesync-tool

CONFIG   += console
CONFIG   -= app_bundle

CONFIG += \
    link_pkgconfig

PKGCONFIG += buteosyncfw5

TEMPLATE = app


SOURCES += main.cpp \
    BTAdaptor.cpp \
    DeviceSync.cpp

HEADERS += \
    BTAdaptor.h \
    DeviceSync.h
