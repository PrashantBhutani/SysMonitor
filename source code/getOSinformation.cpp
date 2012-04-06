#include "monitor.h"

void cpuInfo::getOsInfo(void)
{
    // setting host name aka user of the system
    QFile file("/etc/hostname");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream readFile(&file);
        QString userName = readFile.readLine();
        userName = "<u><b><h2>" + userName + "</h2></b></u>";
        user->setText(userName);
        file.close();
    }

    QFile file1("/etc/lsb-release");
    if(file1.open(QIODevice::ReadOnly))
    {
        // Setting Operating System Name
        QTextStream readFile(&file1);
        QString temp = readFile.readLine();
        QStringList list = temp.split("=");
        temp = list.at(1);
        temp = "<b><h2>"  + temp + "</b></h2>";
        operatingSys->setText(temp);

        // Setting release version
        temp = readFile.readLine();
        list.clear();
        list = temp.split("=");
        QString temp2;
        temp2 = "    Release " + list.at(1);

        temp = readFile.readLine();
        list.clear();
        list = temp.split("=");
        temp2 = temp2 + " (" + list.at(1) + ")";
        release->setText(temp2);
        file1.close();
    }

    // setting kernel version used
    QFile file2("/proc/version");
    if(file2.open(QIODevice::ReadOnly))
    {
        QTextStream readFile(&file2);
        QString temp = readFile.readLine();
        QStringList list = temp.split(" ");
        temp = "    Kernel " + list.at(0) + "  " + list.at(2);
        kernelInfo->setText(temp);
        file2.close();
    }

}
