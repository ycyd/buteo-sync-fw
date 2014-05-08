/*
 * This file is part of buteo-syncfw package
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Sateesh Kavuri <sateesh.kavuri@nokia.com>
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
#ifndef SYNCSCHEDULER_H
#define SYNCSCHEDULER_H

#include "SyncAlarmInventory.h"
#include "BackgroundSync.h"
#include <QObject>
#include <QMap>
#include <ctime>

class QDateTime;

namespace Buteo {
    
class SyncSession;
class SyncSchedulerTest;
class SyncProfile;
class BackgroundSync;

/*! \brief SyncScheduler Object to be used to set Schedule via the framework */
class SyncScheduler : public QObject
{
    Q_OBJECT

public:

    //! \brief Constructor.
    SyncScheduler(QObject *aParent = 0);
    
    /**
     * \brief Destructor
     */
    virtual ~SyncScheduler();

    /*! \brief Adds a profile to the scheduler.
     *
     * Verifies that the profile is enabled and it has schedule enabled
     * before adding. If the profile is already added, removes the old schedule
     * and then adds the profile again.
     * A syncNow signal is sent when sync should be started based on the
     * schedule settings of the profile. The signal is sent only once. Call
     * this function again after the sync has finished to continue scheduling
     * syncs for the profile.
     * \param aProfile Profile to add to scheduler.
     * \return Success indicator.
     */
    bool addProfile(const SyncProfile* aProfile);

    /* Schedule a retry for a failed sync if the profile has retries enabled
     *
     * @param aProfile sync profile
     * @param aNExtSyncTime retry after this duration
     */
    void addProfileForSyncRetry(const SyncProfile* aProfile, QDateTime aNextSyncTime);

    /*! \brief Removes the profile with the given name from the scheduler.
     *
     * No new syncNow signals will be sent for the profile. Note that an
     * already sent signal may still be waiting in the event queue of receiving
     * thread.
     * \param aProfileName Name of the profile to remove from the scheduler.
     */
    void removeProfile(const QString &aProfileName);

public slots:
    /**
     * \brief Performs needed actions when a scheduled sync is completed
     *
     * @param aProfileName Name of the profile for the completed sync
     */
    void syncDone(const QString &aProfileName);
    
private slots:
    /**
     * \brief Performs needed actions when scheduled alarm is triggered
     * 
     * @param aAlarmEventID an ID that identifies the triggered alarm event
     */

    void doAlarmActions(int aAlarmEventID);
    
    /**
     * \brief Performs needed actions when a BackgroundAction is triggered
     * 
     * @param aProfileName Name of the profile on which a BackgroundAction started
     */
    void doBackgroundActions(QString aProfileName);

signals:
    /*! \brief Signal emitted when a sync session should be launched based on
     *   the sync schedule settings of the profile.
     *
     * \param aProfileName Name of the profile.
     */
    void syncNow(QString aProfileName);

private: // functions
    
    /**
     * \brief Programs next alarm event to alarmd.
     * 
     * @param aProfile The profile for which the alarm is programmed
     * @param aNextSyncTime use if provided, otherwise fetch the info from the profile
     * @return Unique alarm event ID or 0 in failure case.
     */
    int setNextAlarm(const SyncProfile* aProfile, QDateTime aNextSyncTime = QDateTime());
    
    
    /**
     * \brief Creates a DBUS adaptor for the scheduler
     */
    void setupDBusAdaptor();
    
    /**
     * \brief Removes an alarm from alarmd queue
     * @param aAlarmEventID ID of the alarm to be removed
     */
    void removeAlarmEvent(int aAlarmEvent);
    
    /**
     * \brief A convenience method that removes all alarms from alarmd queue
     */
    void removeAllAlarms();
    
private: // data
    
    /// A list of sync schedule profiles
    QMap<QString, int> iSyncScheduleProfiles; 

    /// Alarm factory object
    SyncAlarmInventory      *iAlarmInventory;

    /// BackgroundSync management object
    BackgroundSync *iBackgroundActivity;

#ifdef SYNCFW_UNIT_TESTS
    friend class SyncSchedulerTest;
#endif

};

}

#endif // SYNCSCHEDULER_H
