#include "monitor.h"

processInfo::processInfo(QWidget *parent,QTabWidget*tabParent):QWidget(parent),cloneMainWidget(parent),cloneTabWidget(tabParent)
{
    /**
          calling the process Information to initially decorate the Tabs
    **/
        getProcessInfo();

    /**          end process button's initialization and defining its functionality         **/
    endProcess = new QPushButton(tr("End Process"));
    endProcess->setDisabled(true);
    connect(endProcess,SIGNAL(clicked()),this,SLOT(killProcess()));

    /**          setting the Layout         **/
    processLayout = new QVBoxLayout();

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->addStretch();
    horizontalLayout->addWidget(endProcess);

    processLayout->addWidget(processTable);
    processLayout->addLayout(horizontalLayout);
    setLayout(processLayout);

    /**     Making connections to define actions on QTableWidget showing Processes Information      **/
    connect(processTable,SIGNAL(cellClicked(int,int)),processTable,SLOT(selectRow(int)));
    connect(processTable,SIGNAL(cellClicked(int,int)),this,SLOT(enableEndButton()));

    /**     select the row if input is done from keyboard                                           **/
    connect(processTable,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(selectingFromKeyBoard(int)));
    connect(processTable,SIGNAL(currentCellChanged(int,int,int,int)),processTable,SLOT(selectRow(int)));
    // selection of any row will unable the MenuBar functionalities
    connect(this,SIGNAL(signalToUnableMenuActions()),cloneMainWidget,SLOT(unableMenuActions()));

    /**     Connecting the MenuBar functions with the other functionalities of the process          **/
    connect(cloneMainWidget,SIGNAL(processKilledForcefully()),this,SLOT(killProcess()));
    connect(cloneMainWidget,SIGNAL(processKilledNormally()),this,SLOT(killProcessNormally()));
    connect(cloneMainWidget,SIGNAL(processContinued()),this,SLOT(continueProcess()));
    connect(cloneMainWidget,SIGNAL(processStopped()),this,SLOT(stopProcess()));

            /** Starting new thread and defining its connection **/
    // the thread emits signal to update the process info
    connect(&newProcessThread,SIGNAL(processUpdate(void)),this,SLOT(getProcessInfo(void)),Qt::QueuedConnection);
    // the thread switches in between tabs so that the blank tab after updation do not appear
    connect(&newProcessThread,SIGNAL(refreshTab(int)),tabParent, SLOT(setCurrentIndex(int)),Qt::QueuedConnection);
    // sending signal to thread whether to switch tabs for process or not
    connect(this,SIGNAL(sendCurrentIndex(int)),&newProcessThread,SLOT(checkState(int)),Qt::QueuedConnection);
    newProcessThread.start();           /** initiate the thread **/
}

/**
     On selecting a row from keyboard
**/
void processInfo::selectingFromKeyBoard(int row)
{
    processTable->setCurrentCell(row,0);
    enableEndButton();
}

/**
     Enables "END PROCESS" button on selecting any process
 **/
void processInfo::enableEndButton()
{
    endProcess->setEnabled(true);
    // signal to unable MenuBar functionalities
    emit signalToUnableMenuActions();
}

/**
     Kills the selected process forcefully and hides that row from the user's visibility
**/
void processInfo::killProcess()
{
    int row = processTable->currentRow();
    QString PIDstr = processTable->item(row,10)->text();
    PIDstr = "kill " + PIDstr;
    system(PIDstr.toLatin1());
    processTable->hideRow(row);
    endProcess->setDisabled(true);
}

/**
     Kills the selected process normally and hides that row from the user's visibility
 **/
void processInfo::killProcessNormally()
{
    int row = processTable->currentRow();
    QString PIDstr = processTable->item(row,10)->text();
    PIDstr = "kill -1 " + PIDstr;
    system(PIDstr.toLatin1());
    processTable->hideRow(row);
    endProcess->setDisabled(true);
}

/**
     continues the selected stopped process
 **/
void processInfo::continueProcess()
{
    int row = processTable->currentRow();
    QString PIDstr = processTable->item(row,10)->text();
    PIDstr = "kill -CONT " + PIDstr;
    system(PIDstr.toLatin1());
}

/**
     stops the selected running process for the time being
 **/
void processInfo::stopProcess()
{
    int row = processTable->currentRow();
    QString PIDstr = processTable->item(row,10)->text();
    PIDstr = "kill -STOP " + PIDstr;
    system(PIDstr.toLatin1());
}
