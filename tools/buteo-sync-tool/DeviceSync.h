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
#ifndef DEVICESYNC_H
#define DEVICESYNC_H

#include <QObject>

#include "BTAdaptor.h"
#include <ProfileManager.h>
#include <SyncProfile.h>

using namespace Buteo;

class DeviceSync : public QObject
{
    Q_OBJECT
public:
    explicit DeviceSync(QObject *parent = 0);
 
    QString createProfile(const QString btAddress, const QString btName);

    bool startSync(const QString profileName);

    void profileTest();

signals:
    
public slots:
    
private:
    BTAdaptor               mBtAdaptor;

    QString                 mProfileName;
};

#endif // DEVICESYNC_H
