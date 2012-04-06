#include"monitor.h"

cpuInfo::cpuInfo(QWidget *parent) : QWidget(parent)
{
    // assigning memory to Label for ahowing processors Information
    CPUInfo = new QLabel(tr("<b>Hardware</b>"));
    ramInfo = new QLabel();
    user    = new QLabel();
    operatingSys = new QLabel();
    release  = new QLabel();
    kernelInfo = new QLabel();

    // Calling program to calculate system information
    getCpuInfo();
    getRamInfo();
    getOsInfo();

    // defining the layout structure
    // structure is a horizontal box containing one vertical box with a stretch in front
    // so that the information is not sticked to left wall
    CpuInfoLayout = new QHBoxLayout();           // horizontal box layout
    innerSetting1 = new QVBoxLayout();              // vertical box 2 whixh contains the data
    innerSetting1->addSpacing(4);
    innerSetting1->addWidget(user);
    innerSetting1->addSpacing(4);
    innerSetting1->addWidget(operatingSys);
    innerSetting1->addWidget(release);
    innerSetting1->addWidget(kernelInfo);
    innerSetting1->addSpacing(20);
    innerSetting1->addWidget(CPUInfo);       // Adding label to the layout
    innerSetting1->addWidget(ramInfo);

    // adding QLabel to the layout depending on the number of processors present in system
    for(int i=0; i<processorInfo.size(); ++i)
    {
         innerSetting1->addWidget(processorInfo.at(i));
         innerSetting1->addSpacing(0);
     }
    innerSetting1->addStretch();

    // adding layouts to tha main layout
    CpuInfoLayout->addStretch();
    CpuInfoLayout->addLayout(innerSetting1);
    CpuInfoLayout->addStretch();

    // setting the layout of the parent widget
    setLayout(CpuInfoLayout);
}
