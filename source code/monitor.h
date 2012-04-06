#ifndef __MONITOR__H
#define __MONITOR__H

#include"threadingHeader.h"

#include<QWidget>
#include<QLabel>
#include<QFile>
#include<QTextStream>
#include<QString>
#include<QVector>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QDebug>
#include<QDialog>
#include<QTabWidget>
#include<QStyle>
#include<iostream>
#include<QTableWidget>
#include<QFileDialog>
#include<QHeaderView>
#include<QMenu>
#include<QMenuBar>
#include<QApplication>
#include"unistd.h"
#include"pthread.h"
#include"sys/types.h"
#include<QTimer>

using namespace std;


// Class to design the Tab Widget
class settingTabs : public QWidget
{
    Q_OBJECT
    signals:
        void processKilledForcefully();
        void processKilledNormally();
        void processContinued();
        void processStopped();
    private slots:
        void stopProcess();
        void continueProcess();
        void endProcess();
        void killProcess();
        void changePriority();
    public slots:
        void unableMenuActions();

    public:
        settingTabs(QWidget*parent=0);
        QMenu       *menuMonitor,*menuEdit,*menuView,*menuHelp;
        QMenuBar    *menuBar;
        QAction     *stop,*cont,*end,*kill,*priority;
        // Adding a pointer to QTabWidget class object to add tabs in the main widget
        QTabWidget  *tablayout;
        QVBoxLayout *basicLayout;
};

// Class to desing the CPU information tab in the main widget and
// to show the CPU information
class cpuInfo : public QWidget
{
    Q_OBJECT

    public:
            cpuInfo(QWidget *parent=0);

    private slots:
            void getCpuInfo(void);
            void getRamInfo(void);
            void getOsInfo(void);

    private:
            // QVector class to store the QLabels number depending on the count of total processors present in the CPU
            QVector<QLabel*>processorInfo;
            // Layout for System Information
            QHBoxLayout *CpuInfoLayout;
            QVBoxLayout *innerSetting1;
            // Label
            QLabel *user;
            QLabel *operatingSys;
            QLabel *release;
            QLabel *kernelInfo;
            QLabel *CPUInfo;
            QLabel *ramInfo;
};

// Class to design the Processes information tab in the main widget
// it also fetch and display the different processes running on the system
class processInfo : public QWidget
{
    Q_OBJECT

    public:
            processInfo(QWidget*parent,QTabWidget*tabParent);
            processThread newProcessThread;

    signals:
            void sendCurrentIndex(int);
            void signalToUnableMenuActions();

    private slots:
            void enableEndButton();
            void getProcessInfo(void);
            void killProcess();
            void killProcessNormally();
            void continueProcess();
            void stopProcess();
            void selectingFromKeyBoard(int);

    private:
            QHBoxLayout  *horizontalLayout;
            QVBoxLayout  *processLayout;
            QTableWidget *processTable;
            QPushButton  *endProcess;
            QWidget      *cloneMainWidget;
            QTabWidget   *cloneTabWidget;
            QString      *PIDstr;
};

// Class to design the File System information tab in the main widget
// it also fetch and display the file system information present on the system
class fileSystemInfo : public QWidget
{
    Q_OBJECT

    public:
            fileSystemInfo(QTabWidget*parent);
            fileSysThread newFileSysThread;

    signals:
            void sendCurrentIndex(int);

    private slots:
            void getfileSystemInfo(void);
            void openDir(int row);

    private:
            QVBoxLayout  *fileLayout;
            QLabel       *label;
            QTableWidget *tableWidget;
            QTabWidget   *cloneWidget;
};

#endif
