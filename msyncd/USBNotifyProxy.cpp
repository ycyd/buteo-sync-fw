#include "USBNotifyProxy.h"

USBNotifyProxy::USBNotifyProxy (QStringList pathsToWatch, QObject *parent) :
    QObject(parent), iPrevState (false), iPathsToWatch (pathsToWatch)
{
    FUNCTION_CALL_TRACE;

    QObject::connect(&iWatcher, SIGNAL(directoryChanged(QString)),
                     this, SLOT(fileChanged (QString)));
    iWatcher.addPaths (iPathsToWatch);
}

USBNotifyProxy::~USBNotifyProxy ()
{
    FUNCTION_CALL_TRACE;
}

bool
USBNotifyProxy::usbNodeExists (const QString nodeName)
{
    FUNCTION_CALL_TRACE;

    QFile file (nodeName);
    if (file.exists ())
        return true;
    else
        return false;
}

void
USBNotifyProxy::fileChanged (QString path)
{
    if (usbNodeExists () && (iPrevState == false))
    {
        iPrevState = true;
        emit usbConnection (true);
    } else if (!usbNodeExists () && (iPrevState == true))
    {
        iPrevState = false;
        emit usbConnection (false);
    }
}

const QString
USBNotifyProxy::syncmlUsbNode ()
{
    return "/dev/ttyGS1";
}

const QString
USBNotifyProxy::linuxDevPath ()
{
    return "/dev/";
}
