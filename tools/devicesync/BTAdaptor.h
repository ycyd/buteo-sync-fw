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

class BTAdaptor : public QObject
{
    Q_OBJECT
public:
    explicit BTAdaptor(QObject *parent = 0);
    
signals:
    
public slots:
    
private:
    QPair<QString, QString> mTargetBtDevice;
    
    bool validateBtState();
    
    void searchBtDevices();
    
    bool areDevicesPaired(QPair<QString,QString> targetDevice);
    
};

#endif // BTADAPTOR_H
