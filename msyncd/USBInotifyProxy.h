#ifndef USBINOTIFYPROXY_H
#define USBINOTIFYPROXY_H

#include <QThread>
#include <LogMacros.h>
#include <QStringList>

/**
  *! \brief This class is used to monitor the creation/deletion of the USB created
  * nodes such as /dev/ttyGS1. This class is generic in nature that it can monitor
  * any file on the file system
  * A USB device driver creates the nodes at /dev and once this device is created,
  * the sync plugins can start binding to these devices and carry on the respective
  * sync actions
  */
class USBInotifyProxy : public QThread
{
    Q_OBJECT
public:
    explicit USBInotifyProxy(QStringList pathsToWatch = QStringList ("/dev/ttyGS1"), QObject *parent = 0);

    virtual ~USBInotifyProxy ();

    void addPath (const QString path);

    void removePath (const QString path);

    bool usbNodeExists (const QString nodeName="/dev/ttyGS1");

signals:

    void fileCreated (const QString filename);

    void fileRemoved (const QString filename);

public slots:

protected:

    virtual void run ();

private:

    void startWatch ();

    void stopWatch ();

    int                 iFd;

    int                 iWatchFd;

    QStringList         iPathsToWatch;

};

#endif // USBINOTIFYPROXY_H
