#ifndef THREADINGHEADER_H
#define THREADINGHEADER_H

#include<QThread>

class processInfo;

class processThread : public QThread
{
    Q_OBJECT
    signals:
           void processUpdate(void);
           void refreshTab(int tabIndex);

    private slots:
           void checkState(int);

    public:
           processThread();
           void run();
};

class fileSysThread : public QThread
{
    Q_OBJECT
    signals:
            void fileSystemUpdate(void);
            void refreshTab(int tabIndex);

    private slots:
             void checkState(int);

    public:
           fileSysThread();
           void run();
};

#endif
