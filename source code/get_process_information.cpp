#include "monitor.h"

void processInfo::getProcessInfo(void)
{
    static int count = 0;

    /**
       If this function is not being accessed for the first time,
       then remove all the rows in the QTableWidget and
       disable sorting so that it doesn't cause problem
       while assigning new data
    **/
    if(count)
    {
        int totalRows = processTable->rowCount();
        while(totalRows>=0)
        {
            processTable->removeRow(totalRows--);
        }
        processTable->setSortingEnabled(false);
        system("rm ./process_info.log");
    }

    /**     Telling compiler to write the data to "process_info.log" file
            instead of the standard output
    **/
    freopen("./process_info.log","w",stdout);

    /**
    * Unix terminal command which is run by C in sudo terminal
    * used to show processes running on the system with the following data:
    * A = all processes    ||  -o = shown in the given format
    * comm = short command of the process     || user = user of the process
    * stat = Status of the process
    * Different values of status are *//** O=Nonexistent , A=Active , I=Intermediate Z=Canceled , T=Stopped , K=Available kernel process  *//**
    * vsz = virtual memory being used in kilobytes
    * rss = The real-memory (resident memory) size of the process (in 1KB units)
    * pcpu = %CPU          ||   time = cpu time given to process since its starting
    * stime = time the process started in date  ||  etime = total time spent since starting
    * nice = Indicates the decimal value of the process nice value
    * pid = process' ID
    * cmd = actual command line to that process
    * wchan = waiting channel of the process
    ***/
    system("ps -A -o comm,user,stat,vsz,rss,pcpu,time,stime,etime,nice,pid,wchan,cmd");
    close();

    /**
      Opening the recently written file to fetch the data and update the QTableWidget
      with new process information
    **/
    QFile psInfoFile("process_info.log");
    if(!psInfoFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"cannot open";
        return;
    }

    QTextStream FileStream(&psInfoFile);
    QString line = FileStream.readLine();

    QStringList infoList = line.split(" ",QString::SkipEmptyParts);

    // calculating size of the list to form the tabular structure
    int size = infoList.size();

    /**         Setting the Horizontal Header of the TableWidget in the first turn only         **/
    if(count==0)
    {
          processTable   = new QTableWidget(0,size);
          processTable->setHorizontalHeaderLabels(infoList);
          processTable->setSortingEnabled(false);
    }

    // initializing the row variable to use in while loop
    int row=0;

    line = FileStream.readLine();               // read next line


    /**
         while loop to add new rows full of information to the
         QTableWidget until the readable file exhausted
    **/
    while(!line.isNull())                       // is the line null ?
    {
        infoList.clear();           // clearing the previous list

        infoList = line.split(" ",QString::SkipEmptyParts);

        /**
             check if the list size is greater than 13 ????
             if yes then merge extra lists after 12th node
        **/
        if(infoList.size()>13)
        {
            int extra = infoList.size();        // getting the original size of list
            QString replacement = " ";

            /**
                 the "extra" is pointing to the current position of infoList which
                 will be removed after taking its amount and saving it in "replacement"
            **/
            while(extra-- && extra!=12)
            {
                replacement = infoList.at(extra) + " " + replacement;
                // removing the extra node
                infoList.pop_back();
            }

            replacement = infoList.at(12) + " " + replacement;
            infoList.replace(12,replacement);
        }

        /**
             calculating number of rows present in the table to insert new row in the end
        **/
        row = processTable->rowCount();
        processTable->insertRow(row);

        // calculating the column size
        size = processTable->columnCount();

        int tempColumn= 0;
        int listSize = infoList.size();

        /**
            while loop to fill each row with the information contained in infoList
        **/
        while(size)
        {
            // the column number will be "list size" minus "the total number of column size"
            tempColumn = listSize - size;

            QTableWidgetItem *processTableItem = new QTableWidgetItem(infoList.at(tempColumn));
            processTable->setItem(row,tempColumn, processTableItem);
                /**  setting the item to be selectable ONLY **/
            processTableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            --size;
        }

        line = FileStream.readLine();               // reading next line
    }

    psInfoFile.close();                             // closing the file
    
    // setting some more parameters
    processTable->sortByColumn(0,Qt::AscendingOrder);   // table is sorted according to zeroth column
    processTable->setSortingEnabled(true);              // sorting is enabled for the table
    processTable->resizeColumnsToContents();           // resizing of column according to data is possible
    processTable->resizeRowsToContents();               // resizing of row according to data is possible
    processTable->verticalHeader()->hide();             // hiding the vertical header

    processTable->update();                             // updating the QTableWidget
    ++count;                                            // incrementing the count

    /**
        Emitting the signal to send the value of the tab being viewed by user
        and according to that switching the tabs to update them
    **/
    emit sendCurrentIndex(cloneTabWidget->currentIndex());
}

