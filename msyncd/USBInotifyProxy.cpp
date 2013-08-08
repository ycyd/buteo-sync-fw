#include "USBInotifyProxy.h"

#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

USBInotifyProxy::USBInotifyProxy (const QStringList pathsToWatch, QObject *parent) :
    QThread (parent), iPathsToWatch (pathsToWatch)
{
    FUNCTION_CALL_TRACE;
}

USBInotifyProxy::~USBInotifyProxy ()
{
    FUNCTION_CALL_TRACE;
}

void
USBInotifyProxy::addPath (const QString path)
{
    iPathsToWatch << path;
}

void
USBInotifyProxy::removePath (const QString path)
{
    iPathsToWatch.removeOne (path);
}

void
USBInotifyProxy::run ()
{
    startWatch ();

    exec ();

    // Cleanup

    stopWatch ();
}

void
USBInotifyProxy::startWatch ()
{
}

void
USBInotifyProxy::stopWatch ()
{
}
