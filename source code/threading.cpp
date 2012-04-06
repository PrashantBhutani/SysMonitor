#include "monitor.h"
#include "threadingHeader.h"

/**
  constructor to process updating thread
**/
processThread::processThread()
{

}

/**
  main routine responsible for thread working
**/
void processThread::run()
{
    forever{
    sleep(20);
    emit processUpdate();
    }
}

/**
     Slot which is conducted on receiving the "currentIndex" result of QTabWidget
     to update the processes result in QTableWidget
**/
void processThread::checkState(int tabIndex)
{
    if(tabIndex==1)
    {
       emit refreshTab(0);
       emit refreshTab(1);
    }
}



/**
  File System updating thread's constructor
**/
fileSysThread::fileSysThread()
{

}


/**
   Main routine to run the thread
**/
void fileSysThread::run()
{
    forever{
    sleep(20);
    emit fileSystemUpdate();
    }
}

/**
     Slot which is conducted on receiving the "currentIndex" result of QTabWidget
     to update the processes result in QTableWidget
**/
void fileSysThread::checkState(int tabIndex)
{
    if(tabIndex==2)
    {
        emit refreshTab(0);
        emit refreshTab(2);
    }
}
