#include"monitor.h"

// Function to calculate the system processors' information
void cpuInfo::getCpuInfo()
{
    // Opening file "/proc/cpuinfo" which contains the information about CPU in LINUX
    QFile cpuinformation("/proc/cpuinfo");

    // checking if the file is opened for reading or not
    if( !cpuinformation.open(QIODevice::ReadOnly))
    {
         // assigning memory for QLabel* quantity in QVector
         processorInfo.push_back(new QLabel());

         // setting the information label will show
         processorInfo.at(0)->setText("Processor Information not available");
         return;
     }

     // Telling the program to read data from the file
     QTextStream read_file(&cpuinformation);
     // reading first line from the file
     QString line = read_file.readLine();
     // declaring a QStringList variabe to create a list to store QString data type
     // Here it is storing the data about the processor's model
     QStringList processorModelInfo;
     // variable to count the number of processors present in the CPU
     int processorCount=0;

     // setting a loop to read from file
     while(!line.isNull())
     {
           // checking if the line contains word "processor"
           if(line.contains("processor"))
           {
                  processorCount++;          // if yes then increment processorCount
            }

            // check for the information about the processor in the file
            // as the information is like "model name : information"
            if(line.contains("model name"))
            {
                   // if the string "model name" is present in the line
                   // split the Qstring into list of QStrings or say QStringList at occurrence of ":"
                   processorModelInfo.push_back(line.split(":").at(1));  // storing information of 2nd place string of QStringList data structure
             }
                    // read next line
                    line = read_file.readLine();
       }

       // Now when we have count of total number of processors
       for(int i=0;i<processorCount;++i)
       {
                // assign memory to QVector to store data for QLabel*
                processorInfo.push_back(new QLabel());
                // labeldata will contain the data to be shown by Qlabel
                QString labeldata = QString("processor ") + QString::number(i) + QString(" : ") + processorModelInfo.at(i);
                // tell Qlabel to show labeldata
                processorInfo.at(i)->setText(labeldata);
        }

        // closing the opened file
        cpuinformation.close();
}
