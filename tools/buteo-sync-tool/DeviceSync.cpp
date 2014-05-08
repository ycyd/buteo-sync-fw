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
#include "DeviceSync.h"
#include <ProfileEngineDefs.h>
#include <QDebug>
#include <QDBusReply>

const QString BT_DEVICE_SYNC_TEMPLATE = "bt_device_sync_template";

DeviceSync::DeviceSync(QObject *parent) :
    QObject(parent)
{
}

QString
DeviceSync::createProfile (const QString btAddress, const QString btName)
{
    if (btAddress.isEmpty () || btName.isEmpty ())
    {
        qDebug() << "Bluetooth name of address cannot be empty. Address:"
                 << btAddress << ", Name:" << btName;
        return false;
    }

    Buteo::ProfileManager pm;
    Buteo::SyncProfile *sp = pm.syncProfile (BT_DEVICE_SYNC_TEMPLATE);
    if (sp)
    {
        sp->setKey (KEY_DISPLAY_NAME, btName);
        QStringList keys;
        keys << btAddress << sp->name ();
        sp->setName (keys);
        sp->setEnabled (true);
        sp->setBoolKey (KEY_HIDDEN, false);
        sp->setKey (KEY_BT_ADDRESS, btAddress);
        sp->setKey (KEY_BT_NAME, btName);
        mProfileName = pm.updateProfile (*sp);
    } else
    {
        qWarning() << "Template profile " << BT_DEVICE_SYNC_TEMPLATE << " does not exist";
    }
    
    return mProfileName;
}

bool
DeviceSync::startSync (const QString profileName)
{
    if (profileName.isEmpty ())
    {
        qDebug() << "Sync profile not created";
        return false;
    }

    // Start the sync using the dbus API of msyncd
    QDBusMessage callMsg = QDBusMessage::createMethodCall ("com.meego.msyncd",
                                                           "/synchronizer",
                                                           "com.meego.msyncd",
                                                           "startSync");
    QList<QVariant> args;
    args << profileName;
    callMsg.setArguments (args);

    QDBusMessage reply = QDBusConnection::sessionBus ().call (callMsg);
    if (reply.type () == QDBusMessage::ErrorMessage)
    {
        qWarning() << "Error in calling dbus startSync";
        return false;
    }
    return true;
}

void
DeviceSync::profileTest ()
{
    ProfileManager pm;
    Buteo::SyncProfile* sp = pm.syncProfile ("76317012");
    QList<Profile*> subProfiles = sp->allSubProfiles ();
    qDebug() << "Sub profiles count:" << subProfiles.count ();
    qDebug() << sp->allNonStorageKeys();
}
