#ifndef USBINOTIFYPROXY_H
#define USBINOTIFYPROXY_H

#include <QThread>
#include <LogMacros.h>
#include <QStringList>

class USBInotifyProxy : public QThread
{
    Q_OBJECT
public:
    explicit USBInotifyProxy(const QStringList pathsToWatch, QObject *parent = 0);

    virtual ~USBInotifyProxy ();

    void addPath (const QString path);

    void removePath (const QString path);

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
