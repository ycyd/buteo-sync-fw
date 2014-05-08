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

#include <getopt.h>

void
usage(const char* binary_name)
{
    fprintf(stderr,
            "Usage:%s [-s] [-c profile_name] [-e profile_name] [-d profile_name] [-l] [-r profile_name]\n",
            binary_name);
    exit(1);
}

/**
  *! \brief Gets the uesr selection
  * @todo Improve this funtion further to return the profile name
  */
int
user_selection(int argc, char *argv[])
{
    int list_profiles = 0, sync_result = 0;
    int selection = -1;

    char *profile_name = 0;
    if (argc <= 1)
        usage(argv[0]);

    static struct option long_options[] =
    {
        { "devicesync",     no_argument,       0, 's' },
        { "createprofile",  required_argument, 0, 'c' },
        { "enableprpfile",  required_argument, 0, 'e' },
        { "disableprofile", required_argument, 0, 'd' },
        { "listprofiles",   required_argument, 0, 'l' },
        { "syncresult",     required_argument, 0, 'r' }
    };

    int c, option_index = 0;
    while ((c = getopt_long (argc, argv, "sc:e:d:lr:", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 's':
            selection = 1;
            break;
        case 'c':
            selection = 2;
            profile_name = optarg;
            break;
        case 'e':
            selection = 3;
            profile_name = optarg;
            break;
        case 'd':
            selection = 4;
            profile_name = optarg;
            break;
        case 'l':
            selection = 5;
            break;
        case 'r':
            selection = 6;
            profile_name = optarg;
            break;
        default:
            usage(argv[0]);
        }
 
        if (optind > argc)
            usage(argv[0]);
    }

    return selection;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
 
    /*
    int selection = user_selection (argc, argv);

    qDebug() << selection;

    switch (selection)
    {
    case 1:
    {
        BTAdaptor btAdapter;
        bool btDeviceStateValid = btAdapter.validateBtDevice ();
        if (!btDeviceStateValid)
        {
            qWarning() << "Something wrong with the host bluetooth device";
            exit(2);
        }
        btAdapter.searchBtDevices ();
        qDebug() << "Enter the bluetooth address of the target device to sync with";
    }
        break;
    case 2:
    {
        DeviceSync ds;
        ds.createProfile ("40:98:4E:5C:B5:3F", "Nokia N9");
    }
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        break;
    };

    // Start sync
    //ds.startSync (profileName);
    return a.exec();
    */
    DeviceSync ds;
    ds.profileTest ();
}
