#ifndef USBNOTIFYPROXY_H
#define USBNOTIFYPROXY_H

#include <QThread>
#include <LogMacros.h>
#include <QStringList>
#include <QFileSystemWatcher>

/**
  *! \brief This class is used to monitor the creation/deletion of the USB created
  * nodes such as /dev/ttyGS1. This class is generic in nature that it can monitor
  * any file on the file system
  * A USB device driver creates the nodes at /dev and once this device is created,
  * the sync plugins can start binding to these devices and carry on the respective
  * sync actions
  */
class USBNotifyProxy : public QObject
{
    Q_OBJECT
public:
    explicit USBNotifyProxy(QStringList pathsToWatch = QStringList (USBNotifyProxy::linuxDevPath ()), QObject *parent = 0);

    virtual ~USBNotifyProxy ();

    bool usbNodeExists (const QString nodeName=USBNotifyProxy::syncmlUsbNode ());

signals:

    void usbConnection (bool connected);

protected slots:

    void fileChanged (QString path);

private:

    static const QString syncmlUsbNode();

    static const QString linuxDevPath ();

    bool                iPrevState;

    QStringList         iPathsToWatch;

    QFileSystemWatcher  iWatcher;
};

#endif // USBNOTIFYPROXY_H
