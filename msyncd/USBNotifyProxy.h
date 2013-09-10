/*
* This file is part of buteo-sync-plugins package
*
* Copyright (C) 2013 Jolla Ltd. and/or its subsidiary(-ies).
*
* Author: Sateesh Kavuri <sateesh.kavuri@gmail.com>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* This library is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA
*/

#ifndef USBNOTIFYPROXY_H
#define USBNOTIFYPROXY_H

#include <QThread>
#include <LogMacros.h>
#include <QStringList>
#include <QFileSystemWatcher>

/**
  *! \brief This class is used to monitor the creation/deletion of the USB created
  * nodes such as /dev/ttyGS1. This class is generic in nature that it can monitor
  * any file on the file system
  * A USB device driver creates the nodes at /dev and once this device is created,
  * the sync plugins can start binding to these devices and carry on the respective
  * sync actions
  */
class USBNotifyProxy : public QObject
{
    Q_OBJECT
public:
    explicit USBNotifyProxy(QStringList pathsToWatch = QStringList(USBNotifyProxy::linuxDevPath()), QObject *parent = 0);

    virtual ~USBNotifyProxy();

    bool usbNodeExists(const QString nodeName=USBNotifyProxy::syncmlUsbNode());

signals:

    void usbStateChanged(bool connected);

protected slots:

    void fileChanged(QString path);

private:

    static const QString syncmlUsbNode();

    static const QString linuxDevPath();

    bool                iPrevState;

    QStringList         iPathsToWatch;

    QFileSystemWatcher  iWatcher;
};

#endif // USBNOTIFYPROXY_H
