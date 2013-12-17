/*
 * This file is part of buteo-syncfw package
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
 *
 */
#include <QCoreApplication>
#include <QDebug>
#include "BTAdaptor.h"
#include "DeviceSync.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QString targetBtAddr = QString(argv[1]);
    BTAdaptor btAdapter;
    qDebug() << "Validating device";
    btAdapter.validateBtDevice ();

    qDebug() << "Searching for devices nearby";
    btAdapter.searchBtDevices ();

    BTAdaptor::BtDeviceProps *targetBtDevice = btAdapter.device (targetBtAddr);
    if (!targetBtDevice)
    {
        qWarning() << "Target device with address " << targetBtAddr << " not available";
        return 3;
    }

    if (targetBtDevice->paired == false)
    {
        qDebug() << "Device " << targetBtDevice->name << " is not paired. Pair first";
        return 1;
    }

    qDebug() << "Creating profile with name Nokia N9";
    DeviceSync ds;
    QString profileName = ds.createProfile (targetBtAddr, targetBtDevice->name);
    if (profileName.isEmpty ())
    {
        qWarning() << "Failure in creating profile";
        return 2;
    }

    // Start sync
    ds.startSync (profileName);
    return a.exec();
}
