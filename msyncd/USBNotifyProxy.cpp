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

#include "USBNotifyProxy.h"

USBNotifyProxy::USBNotifyProxy(QStringList pathsToWatch, QObject *parent) :
    QObject(parent), iPrevState(false), iPathsToWatch(pathsToWatch)
{
    FUNCTION_CALL_TRACE;

    QObject::connect(&iWatcher, SIGNAL(directoryChanged(QString)),
                     this, SLOT(fileChanged(QString)));
    iWatcher.addPaths(iPathsToWatch);
}

USBNotifyProxy::~USBNotifyProxy()
{
    FUNCTION_CALL_TRACE;
}

bool
USBNotifyProxy::usbNodeExists(const QString nodeName)
{
    FUNCTION_CALL_TRACE;

    QFile file(nodeName);
    if (!file.open (QIODevice::ReadOnly))
    {
        LOG_DEBUG(nodeName << " does not exist");
        return false;
    }

    if (file.exists())
        return true;
    else
        return false;

    file.close();
}

void
USBNotifyProxy::fileChanged(QString path)
{
    FUNCTION_CALL_TRACE;

    bool syncmlNodeExists = usbNodeExists();
    if (syncmlNodeExists && (iPrevState == false))
    {
        iPrevState = true;
        emit usbStateChanged(true);
    } else if (!syncmlNodeExists && (iPrevState == true))
    {
        iPrevState = false;
        emit usbStateChanged(false);
    }
}

const QString
USBNotifyProxy::syncmlUsbNode()
{
    return "/dev/ttyGS1";
}

const QString
USBNotifyProxy::linuxDevPath()
{
    return "/dev/";
}
