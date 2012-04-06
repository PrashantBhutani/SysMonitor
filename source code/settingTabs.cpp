#include "monitor.h"

const int MAX_SIZE = 700;           // Initial amount to define window's dimensions

settingTabs::settingTabs(QWidget *parent):QWidget(parent)
{
   resize(MAX_SIZE,MAX_SIZE-200);       // resizing the widget

   /**
         defining the "Monitor" menu and different actions it will perform
   **/
                 menuMonitor = new QMenu(tr("&Monitor"));
   menuMonitor->addAction(tr("&Quit          Alt+Q"),qApp,SLOT(quit()));    // Adding action to the menu

   /**
         defining the "Edit" menu and different actions it will perform
   **/
                menuEdit = new QMenu(tr("Edit"));
                stop = new QAction(tr("Stop Process"),this);
                menuEdit->addAction(stop);
                stop->setDisabled(true);
                connect(stop,SIGNAL(triggered()),this,SLOT(stopProcess()));
                cont = new QAction(tr("Continue Process"),this);
                menuEdit->addAction(cont);
                cont->setDisabled(true);
                connect(cont,SIGNAL(triggered()),this,SLOT(continueProcess()));
                menuEdit->addSeparator();
                end = new QAction(tr("End Process"),this);
                menuEdit->addAction(end);
                end->setDisabled(true);
                connect(end,SIGNAL(triggered()),this,SLOT(endProcess()));
                kill = new QAction(tr("Kill Process"),this);
                menuEdit->addAction(kill);
                kill->setDisabled(true);
                connect(kill,SIGNAL(triggered()),this,SLOT(killProcess()));
                menuEdit->addSeparator();
                priority = new QAction(tr("Change Priority"),this);
                menuEdit->addAction(priority);
                priority->setDisabled(true);
                connect(priority,SIGNAL(triggered()),this,SLOT(changePriority()));

   /**
         defining the "View" menu and different actions it will perform
   **/
                menuView  = new QMenu(tr("View"));

   /**
         defining the "Help" menu and different actions it will perform
   **/
                menuHelp = new QMenu(tr("Help"));

   /**
         initializing the QMenuBar which will contain the menus defined above
   **/
                menuBar = new QMenuBar();
                // adding the menus in the menubar
                menuBar->addMenu(menuMonitor);
                menuBar->addMenu(menuEdit);
               // menuBar->addMenu(menuView);
               // menuBar->addMenu(menuHelp);

   /**
         Alloting memory to the Tab Widget Object
   **/
        tablayout = new QTabWidget;

   /**
         defining different tabs it will contain
   **/
        tablayout->addTab(new cpuInfo(),tr("System"));
        tablayout->addTab(new processInfo(this,tablayout),tr("Processes"));
        tablayout->addTab(new fileSystemInfo(tablayout),tr("File Systems"));

   // setting the layout
   basicLayout = new QVBoxLayout();
   basicLayout->addWidget(menuBar);
   basicLayout->addWidget(tablayout);
   setLayout(basicLayout);

   /**          setting Window Title                **/
   setWindowTitle("System Monitor");
}

void settingTabs::stopProcess()
{
    emit processStopped();
}

void settingTabs::continueProcess()
{
    emit processContinued();
}

void settingTabs::endProcess()
{
    emit processKilledNormally();
}

void settingTabs::killProcess()
{
    emit processKilledForcefully();
}

void settingTabs::changePriority()
{
}

void settingTabs::unableMenuActions()
{
    stop->setDisabled(false);
    cont->setDisabled(false);
    end->setDisabled(false);
    kill->setDisabled(false);
    priority->setDisabled(false);
}
