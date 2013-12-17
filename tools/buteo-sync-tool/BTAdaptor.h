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
#ifndef BTADAPTOR_H
#define BTADAPTOR_H

#include <QObject>
#include <QPair>
#include <QDBusInterface>

class BTAdaptor : public QObject
{
    Q_OBJECT
public:
    
    /**
      *! \brief The structure that holds the properties of a bluetooth device
      */
    typedef struct {
        QString name;
        bool paired;
        QString btClass;
    }BtDeviceProps;

    explicit BTAdaptor(QObject *parent = 0);

    /**
     *! \brief Method to validate the bt device on the host
     * @return true if everything is okay, false otherwise
     */
    bool validateBtDevice();
 
    /**
     *! \brief Method to search for bluetooth devices in range
     * 
     */
    void searchBtDevices();
 
    /**
      *! \brief Method to pair the host bluetooth with the target
      * @param the address of the target bluetooth device
      */
    void pairDevices(const QString targetAddress);

    /**
      *! \brief Returns the bluetooth parameters given an address
      * @return The struct @see BtDeviceProps with the properties of bt device
      * @param the address of the target bt device
      */
    BtDeviceProps* device(const QString address);

protected slots:

    void deviceFound (QString address, QMap<QString,QVariant> devices);

    void deviceDisappeared (QString address);

private:

    QString                       mAdapterPath;

    QMap<QString, BtDeviceProps*>  mFoundDevices;

    QString adapterPath();
 
    bool areDevicesPaired(QString targetDevice);
 
    bool deviceHasSyncmlService(const QString& btAddress);
};

#endif // BTADAPTOR_H
