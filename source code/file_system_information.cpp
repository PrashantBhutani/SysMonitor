#include "monitor.h"

fileSystemInfo::fileSystemInfo(QTabWidget *parent) : QWidget(parent) , cloneWidget(parent)
{
    // The main Layout of file system tab which contains the scrolling area
    // which will contain the Listed view of system files
    label = new QLabel(tr("<b>File Systems</b>"));
    fileLayout = new QVBoxLayout();

    /**
          calling the File System Information to initially decorate the Tabs
    **/
    getfileSystemInfo();

    // setting the layout
    fileLayout->addWidget(label);
    fileLayout->addWidget(tableWidget);
    setLayout(fileLayout);

    /**     Making connections to define actions on QTableWidget showing File System Information      **/
    connect(tableWidget,SIGNAL(cellClicked(int,int)),tableWidget,SLOT(selectRow(int)));
    connect(tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(openDir(int)));
    connect(tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),tableWidget,SLOT(selectRow(int)));


            /** Starting new thread and defining its connection **/
    // the thread emits signal to update the file system info
    connect(&newFileSysThread,SIGNAL(fileSystemUpdate()),this,SLOT(getfileSystemInfo()),Qt::QueuedConnection);
    // the thread switches in between tabs so that the blank tab after updation do not appear
    connect(&newFileSysThread,SIGNAL(refreshTab(int)),parent, SLOT(setCurrentIndex(int)),Qt::QueuedConnection);
    // sending signal to thread whether to switch tabs for process or not
    connect(this,SIGNAL(sendCurrentIndex(int)),&newFileSysThread,SLOT(checkState(int)),Qt::QueuedConnection);
    newFileSysThread.start();           /** initiate the thread **/
}

/**
     Opens the selected directory on clicking it
 **/
void fileSystemInfo::openDir(int row)
{
    QString str = QFileDialog::getOpenFileName(this,"open directory",tableWidget->item(row,1)->text());
}
