#include"monitor.h"

/**
         Function to calculate the system Main Memory(RAM) information
**/
void cpuInfo::getRamInfo()
{
      /**       opening file to read available RAM information           **/
      QFile ram_info("/proc/meminfo");

      if(ram_info.open(QIODevice::ReadOnly))            // opening file for Read only purpose
      {
           QTextStream ramFile(&ram_info);              // Telling program to stream from opened file

           // reading first line as this contains the information of RAM(main memory) present in system
           QString str = ramFile.readLine();

           QStringList list = str.split(" ",QString::SkipEmptyParts);   // splitting the string

           long memInKb = (list.at(1)).toLong();    // data at 2nd position in list!! convert it to long!!
           int count = 0;

            // netMem will contain the main memory in nearest possible unit
            double netMem = static_cast<double>(memInKb);

            // when the amount of memory is unable to be divided by 1024 after continuous division
            while(memInKb>1024)
            {
                    // convert bytes to kilobytes to megabytes to gigabytes to terabytes and so on
                    netMem = static_cast<double>(memInKb)/1024;
                    memInKb = memInKb/1024;
                    // count to know at which unit the process stops
                    count++;
             }

               /**      assigning the unit according to the count       **/
               if(count==0)
                        str = "Memory :        " + QString::number(netMem) + "KB";
               else if(count==1)
                        str = "Memory :        " + QString::number(netMem) + "MB";
               else if(count==2)
                        str = "Memory :        " + QString::number(netMem) + "GiB";
               else if(count==3)
                        str = "Memory :        " + QString::number(netMem) + "TB";

               // setting label
               ramInfo->setText(str);

               // closing the file
               ram_info.close();
           }
  }
