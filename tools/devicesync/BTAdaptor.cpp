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
#include "BTAdaptor.h"

#include <QDBusReply>
#include <QDebug>

#define BLUEZ_DEST "org.bluez"
#define BLUEZ_MANAGER_INTERFACE "org.bluez.Manager"
#define BLUEZ_ADAPTER_INTERFACE "org.bluez.Adapter"
#define BLUEZ_SERIAL_INTERFACE "org.bluez.Serial"
#define REQUEST_SESSION "RequestSession"
#define RELEASE_SESSION "ReleaseSession"
#define GET_DEFAULT_ADAPTER "DefaultAdapter"
#define FIND_DEVICE "FindDevice"
#define CREATE_DEVICE "CreateDevice"
#define CREATE_PAIRED_DEVICE "CreatePairedDevice"
#define CONNECT "Connect"
#define DISCONNECT "Disconnect"

Q_DECLARE_METATYPE(QList<QDBusObjectPath>)

BTAdaptor::BTAdaptor(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<QList<QDBusObjectPath> >();
    
    mAdapterPath = adapterPath ();
}

QString
BTAdaptor::adapterPath ()
{
    // Get the Bluez manager dbus interface
    QDBusInterface mgrIface ("org.bluez", "/", "org.bluez.Manager", QDBusConnection::systemBus ());
    if (!mgrIface.isValid ())
    {
        qWarning() << "Unable to get bluez manager iface";
        return "";
    }

    // Fetch the default bluetooth adapter
    QDBusReply<QDBusObjectPath> reply = mgrIface.call (QLatin1String ("DefaultAdapter"));
    
    QString adapterPath = reply.value ().path ();
    qDebug() << "Bluetooth adapter path:" << adapterPath;
    
    return adapterPath;
}

bool
BTAdaptor::validateBtDevice ()
{
    qDebug() << "Validating bluetooth device";
    QDBusMessage msg = QDBusMessage::createMethodCall ("org.bluez",
                                                       mAdapterPath,
                                                       "org.bluez.Adapter",
                                                       "GetProperties");
    
    QDBusMessage reply = QDBusConnection::systemBus ().call (msg);
    if (reply.type () == QDBusMessage::ErrorMessage)
    {
        qWarning() << "Error in dbus call";
        return false;
    }

    QDBusArgument arg = reply.arguments ().at (0).value<QDBusArgument>();
    if (arg.currentType () == QDBusArgument::MapType)
    {
        QMap<QString,QVariant> props = qdbus_cast<QMap<QString,QVariant> > (arg);
        
        QMap<QString,QVariant>::iterator iter;
    	for (iter = props.begin (); iter != props.end (); ++iter)
    	{
        	// ! @todo Perform some validation on the returned properties
        	qDebug() << iter.key () << ":" << iter.value ();
    	}
    }
}

void
BTAdaptor::searchBtDevices ()
{
    // Connect to the signal DeviceFound to obtain the list of devices
    QDBusConnection bus = QDBusConnection::systemBus ();
    bool success = bus.connect ("org.bluez",
                                mAdapterPath,
                                "org.bluez.Adapter",
                                "DeviceFound",
                                this,
                                SLOT (deviceFound(QString,QMap<QString,QVariant>)));

    if (!success)
    {
        qDebug() << "Failure in connecting dbus signal";
        return;
    }
    
    QDBusMessage msg = QDBusMessage::createMethodCall ("org.bluez",
                                                       mAdapterPath,
                                                       "org.bluez.Adapter",
                                                       "StartDiscovery");

    QDBusMessage reply = bus.call (msg);
    if (reply.type () == QDBusMessage::ErrorMessage)
    {
        qWarning() << "Error in dbus call to search for devices";
        return ;
    }
}

void
BTAdaptor::deviceFound (QString address, QMap<QString, QVariant> devices)
{
    BtDeviceProps *prop = new BtDeviceProps();
    
    QMap<QString,QVariant>::iterator iter;

    for(iter = devices.begin (); iter != devices.end (); ++iter)
    {
        //qDebug() << iter.key () << ":" << iter.value ();
        if (iter.key () == "Name")
            prop->name = iter.value ().toString ();

        if (iter.key () == "Paired")
            prop->paired = iter.value ().toBool ();
        
        if (iter.key () == "Class")
            prop->btClass = iter.value ().toString ();
    }
    
    // Add the device to the list
    mFoundDevices.insert (address, prop);
    qDebug() << "Device:" << address << ","
             << "Name:" << prop->name << ","
             << "Paired:" << prop->paired << ","
             << "Bt class:" << prop->btClass;
}

void
BTAdaptor::deviceDisappeared (QString address)
{
    qDebug() << "Device with address " << address         <<
              " name:" << mFoundDevices.value (address) <<
              " disappeared";
    // Remove the device from the list
    mFoundDevices.remove (address);
}

bool
BTAdaptor::areDevicesPaired (QString targetDevice)
{
    return mFoundDevices.value (targetDevice)->paired;
}

bool
BTAdaptor::deviceHasSyncmlService (const QString &btAddress)
{
    //! @todo Check using SDP browse
}
