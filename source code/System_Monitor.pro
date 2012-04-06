# -------------------------------------------------
# Project created by QtCreator 2010-09-27T21:07:53
# -------------------------------------------------
TARGET = System_Monitor
TEMPLATE = app

# INCLUDEPATH += "/proc"
SOURCES += main.cpp \
    cpu_Info_Constructor.cpp \
    get_cpu_Information.cpp \
    settingTabs.cpp \
    process_Information.cpp \
    file_system_information.cpp \
    get_file_system_information.cpp \
    get_ram_information.cpp \
    getOSinformation.cpp \
    get_process_information.cpp \
    threading.cpp
HEADERS += monitor.h \
    "/usr/include/pthread.h" \
    "/usr/include/unistd.h" \
    "/usr/include/sys/types.h" \
    threadingHeader.h
FORMS += 
OTHER_FILES += 
RESOURCES += Icon_Resource.qrc
