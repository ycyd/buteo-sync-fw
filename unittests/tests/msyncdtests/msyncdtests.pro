SOURCEPATH += . \
    ../../../msyncd
    
INCLUDEPATH += /usr/include/iphbd/ \
/usr/include/signon-qt
DEFINES +=  UNIT_TEST
QT += xml \
    dbus
CONFIG += qdbus \
    link_pkgconfig \
    silent
PKGCONFIG += dbus-1
LIBS += -lcontextsubscriber -liphb -lqttracker -lsignon-qt

SOURCES += ServerThread.cpp \
    ServerThreadTest.cpp \
    StorageBookerTest.cpp \
    StorageBooker.cpp \
    SyncQueueTest.cpp \
    SyncQueue.cpp \
    AccountsHelperTest.cpp \
    AccountsHelper.cpp \
    SyncSchedulerTest.cpp \
    SyncScheduler.cpp \
    SyncSession.cpp \
    SyncSessionTest.cpp \
    PluginRunner.cpp \
    ClientThread.cpp \
    ClientThreadTest.cpp\
    USBModedProxy.cpp \
    TransportTracker.cpp \
    TransportTrackerTest.cpp \
    PluginRunnerTest.cpp \
    ClientPluginRunner.cpp \
    ServerActivator.cpp \
    ServerActivatorTest.cpp \
    ClientPluginRunnerTest.cpp \
    synchronizer.cpp \
    SyncDBusAdaptor.cpp \
    SyncBackupAdaptor.cpp \
    SyncBackup.cpp \
    SyncBackupTest.cpp \
    ServerPluginRunner.cpp \
    ServerPluginRunnerTest.cpp \
    SynchronizerTest.cpp \
    SyncAlarmInventory.cpp \
    IPHeartBeat.cpp \
    IPHeartBeatTest.cpp

HEADERS += ServerThread.h \
    ServerThreadTest.h \
    StorageBookerTest.h \
    SyncQueueTest.h \
    AccountsHelperTest.h \
    AccountsHelper.h \
    SyncSchedulerTest.h \
    SyncScheduler.h \
    SyncSession.h \
    SyncSessionTest.h \
    PluginRunner.h \
    ClientThread.h \
    ClientThreadTest.h\
    USBModedProxy.h \
    TransportTracker.h \
    TransportTrackerTest.h \
    PluginRunnerTest.h \
    ClientPluginRunner.h \
    ServerActivator.h \
    ServerActivatorTest.h \
    ClientPluginRunnerTest.h \
    synchronizer.h \
    SyncDBusAdaptor.h \
    SyncDBusInterface.h \
    SyncBackupProxy.h \
    SyncBackupAdaptor.h \
    SyncBackup.h \
    SyncBackupTest.h \
    ServerPluginRunner.h \
    ServerPluginRunnerTest.h \
    SyncAlarmInventory.h \
    SynchronizerTest.h \
    IPHeartBeat.h \
    IPHeartBeatTest.h

OTHER_FILES += 

