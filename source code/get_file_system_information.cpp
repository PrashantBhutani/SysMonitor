#include "monitor.h"

void fileSystemInfo::getfileSystemInfo(void)
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
        int totalRows = tableWidget->rowCount();
        while(totalRows>=0)
            tableWidget->removeRow(totalRows--);
        tableWidget->setSortingEnabled(false);
        system("rm ./file_system_Info.log");
    }

    /**     Telling compiler to write the data to "./file_system_Info.log" file
            instead of the standard output
    **/
    freopen("./file_system_Info.log","w",stdout);
    system("df -a -hT");            // command to get the information about file system existing on system
    close();

    /**
      Opening the recently written file to fetch the data and update the QTableWidget
      with new process information
    **/
    QFile fileSysinfo("./file_system_Info.log");

    if(!fileSysinfo.open(QIODevice::ReadOnly))              // opening with read only mode
        return;

    QTextStream FileStream(&fileSysinfo);
    QString line = FileStream.readLine();

    /**
         list of strings read from file in the form
         QStringList["Device","Directory","Type","Total","Used","Available","Use %"];
    **/
    QStringList infoList;

    infoList = line.split(" ",QString::SkipEmptyParts);

    // calculating size of the list to form the tabular structure
    int size = infoList.size() - 1;

    // "mounted on" is one word but was counted as two, so removed "on" from list
    infoList.removeAt(infoList.size()-1);

    /**
         Replacing the data of infoLIst with desired ones
    **/
    if(count == 0)
    {
             infoList.replace(0,"Device");
             infoList.replace(1,"Directory");
             infoList.replace(2,"Type");
             infoList.replace(3,"Total");
             infoList.replace(4,"Used");
             infoList.replace(5,"Available");
             infoList.replace(6,"Use %");

             // QlistView to show the file system information in different columns
             tableWidget   = new QTableWidget(0,size);

             // setting the headers of the colums using the list
             tableWidget->setHorizontalHeaderLabels(infoList);
      }

    // initializing the row variable to use in while loop
    int row=0;

    line = FileStream.readLine();           // read next line

    /**
         while loop to add new rows full of information to the
         QTableWidget until the readable file exhausted
    **/
    while(!line.isNull())                   // is the line null ?
    {
        infoList.clear();                   // clearing the previous list

        // the log file is saving the data for these two drives in two lines causing error while running
        // so this if-condition is merging those two lines for these drives
        if(line.contains("binfmt_misc") || line.contains("gvfs-fuse-daemon"))
        {
            line += " " + FileStream.readLine();
        }

        infoList = line.split(" ",QString::SkipEmptyParts);

        /**
             calculating number of rows present in the table to insert new row in the end
        **/
        row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        // calculating the column size
        size = tableWidget->columnCount();

        int tempColumn= 0;
        int listSize = infoList.size();

        /**
            while loop to fill each row with the information contained in infoList
        **/
        while(size)
        {
            // the column number will be "list size" minus "the total number of column size"
            tempColumn = listSize - size;

            QTableWidgetItem *tableWidgetItem;

            // initializing the table cell compatible data type with the disc data
            if(tempColumn != 0)
            {
                    if(infoList.at(tempColumn) != "0" && infoList.at(tempColumn) != "-")
                    {
                            tableWidgetItem = new QTableWidgetItem(infoList.at(tempColumn));
                    }
                    else if(infoList.at(tempColumn) == "0")
                    {
                            tableWidgetItem = new QTableWidgetItem("0 bytes");
                    }
                    else
                    {
                            tableWidgetItem = new QTableWidgetItem("0%");
                    }
            }
            // For the device name attaching the icon with it
            else
            {
                tableWidgetItem = new QTableWidgetItem(QIcon(QPixmap(":/index.jpeg")),infoList.at(tempColumn));
            }

            // setting the item to be selectable ONLY
            tableWidgetItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            // assigning the data to each table cell corresponding to System Monitor
            switch(tempColumn)
            {
                    case 0:
                              tableWidget->setItem(row,tempColumn, tableWidgetItem);
                              break;
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                               tableWidget->setItem(row,tempColumn+1, tableWidgetItem);
                               break;
                    case 6:
                               tableWidget->setItem(row,1, tableWidgetItem);
            }

            --size;
        }

        line = FileStream.readLine();
    }

    // setting some more parameters
    tableWidget->sortByColumn(1,Qt::AscendingOrder);      // table is sorted according to first column
    tableWidget->setSortingEnabled(true);                 // sorting is enabled for the table
    tableWidget->resizeColumnsToContents();             // resizing of column according to data is possible
    tableWidget->resizeRowsToContents();                  // resizing of row according to data is possible
    tableWidget->verticalHeader()->hide();                // hiding the vertical header

    ++count;                                    // incrementing the count

    /**
        Emitting the signal to send the value of the tab being viewed by user
        and according to that switching the tabs to update them
    **/
    emit sendCurrentIndex(cloneWidget->currentIndex());
}
