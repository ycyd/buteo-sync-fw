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

#ifndef SYNCCLIENTINTERFACEPRIVATE_H
#define SYNCCLIENTINTERFACEPRIVATE_H

#include <QObject>
#include "SyncDaemonProxy.h"
#include <libsyncprofile/SyncProfile.h>

namespace Buteo {

class SyncProfile;
class SyncSchedule;
class SyncResults;
class SyncClientInterface;

//! Private implementation class for SyncClientInterface.
class SyncClientInterfacePrivate:public QObject
{
	Q_OBJECT
public:
	/*!\brief Constructor
	 *
	 *@param aParent - pointer to the parent object
	 */
	SyncClientInterfacePrivate(SyncClientInterface *aParent);

	/*! \brief Destructor
	 */
	~SyncClientInterfacePrivate();

	/*! \brief function to start the sync
	 *
	 * @param aProfileId - id of the profile to start the sync
	 */
	bool startSync(const QString &aProfileId) const;

	/*! \brief function to abort the sync
	 *
	 * @param aProfileId - id of the profile to abort the sync
	 */
	void abortSync(const QString &aProfileId) const;

	/*! \brief function to get Running sync list
	 *
	 * @return  - list of running sync profile ids
	 */
	QStringList getRunningSyncList();

	/*! \brief function to add a new profile
	 *
	 * @param aProfile profile to add
	 */
	bool addProfile(Buteo::SyncProfile &aProfile);

	/*! \brief function to remove a profile
	 *
	 * @param aProfileId id of the profule to remove to add
	 */
	bool removeProfile(QString &aProfileId);

	/*! \brief function to update an existing profile
	 *
	 * @param aProfile profile object to add
	 */
	bool updateProfile(Buteo::SyncProfile &aProfile);

	/*! \brief function to add a profile
	 *
	 * @return returns the backup restore state.
	 */
	bool getBackUpRestoreState();

	/*! \brief function to check if the interface is valid
	 *
	 * @return  status of the validity of the interface
	 */
    bool isValid();

	/*! \brief this function converts the SyncSchedule object to an xml
	 *  file of the below format
     * \code
     * <schedule interval="15" days="1,2,3,4,5,6,7" time="">
        <rush begin="08:00:00" enabled="true" interval="5" end="17:00:00" days="1,2,3,4,5"/>
      </schedule>
     * \endcode
     *
     * @param aProfileId - profile id
     * @param aSchedule - schedule object
     */
	bool setSyncSchedule(QString &aProfileId,SyncSchedule &aSchedule);

    /*! \brief this function converts the save the syncResults into
     * log.xml file corresponding to profileName.
     * \code
     * <syncresults scheduled="false" majorcode="1" minorcode = "501" time="2010-06-01T06:43:32">
     * \endcode
     */
    bool saveSyncResults(const QString &aProfileId,const Buteo::SyncResults &aSyncResults);

    /*! \brief Gets the Major code for the last.
     *  \param profileID
     *  \param major code as reference.
     *  \param minor code as reference
     *  \return void
     */
    void lastSyncResultCode(const QString &aProfileId, int &majorCode, int &minorCode);

    /*! \brief Gets the time of last completed sync session with this profile.
     *  \param profileID
     * \return Last sync time. Null object if this could not be determined.
     */
    QDateTime lastSyncTime(const QString &aProfileId);

    /*! \brief Checks if the results are from a scheduled sync.
     *  \param profileID
     * \return True if scheduled.
     */
    bool isLastSyncScheduled(const QString &aProfileId) const;

public slots:

	/*! \brief this is the slot where we will receive the xml data for profile from msyncd.
	 * The XML Data received will be of the following format
	 * \code <?xml version="1.0" encoding="UTF-8"?>
	 *	<profile type="sync" name="ovi.com-sr1">
	 *		<key value="1" name="accountid"/>
	 *		<key value="true" name="active"/>
	 *		<key value="true" name="enabled"/>
	 *		<key value="false" name="hidden"/>
	 *		<key value="true" name="scheduled"/>
	 *		<key value="true" name="use_accounts"/>
	 *		<profile type="service" name="ovi.com"/>
	 *		<profile type="storage" name="hcontacts">
	 *		<key value="true" name="enabled"/>
	 *		</profile>
	 *		<schedule interval="15" days="1,2,3,4,5,6,7" time="">
	 *		<rush begin="08:00:00" enabled="true" interval="5" end="17:00:00" days="1,2,3,4,5"/>
	 *		</schedule>
	 *	</profile>
	 *	\endcode
	 * @param 	aProfileId - id of the profile
	 * @param   aChangeType - change type whether addition , deletion or modification
	 * @param  aChangedProfileAsXml - changed profile arrives as xml
	 *
	 */
	void profileChanged(QString aProfileId , int aChangeType , QString aChangedProfileAsXml);

	/*! \brief this is the slot where we will receive the xml data for results from msyncd
	 * the xml looks like this
	 * \code <syncresults scheduled="false" majorcode="0" minorcode = "0" time="2010-06-01T06:43:32">
	 *	<target name="">
	 *	 <local modified="0" added="0" deleted="0"/>
	 *	<remote modified="0" added="4" deleted="0"/>
	 *	</target>
	 * </syncresults>
	 *\endcode
	 * @param aProfileId - id of the profile
	 * @param aLastSyncResultAsXml - last sync result as xml
	 */
	void resultsAvailable(QString aProfileId , QString aLastSyncResultAsXml);

signals:

	/*! \brief Signal that gets emitted on receiving profileChanged from msyncd
	 *
	 * @param 	aProfileId - id of the profile
	 * @param   aChangeType - change type whether addition , deletion or modification
	 * @param  aChangedProfile - changed sync profile object
	 */
	void profileChanged(QString aProfileId,int aChangeType,Buteo::SyncProfile aChangedProfile);

	/*! \brief Signal that gets emitted on receiving resultsAvailable from msyncd
	 *
	 * @param 	aProfileId - id of the profile
	 * @param   aLastResults - last results as SyncResults Object
	 */
	void resultsAvailable(QString aProfileId,Buteo::SyncResults aLastResults);

private:

	SyncDaemonProxy *iSyncDaemon;

	Buteo::SyncClientInterface *iParent;

};


};

#endif