#-------------------------------------------------
# RobotSim Qt project file.
#-------------------------------------------------

QT       += core network

QMAKE_CXXFLAGS +=

*-g++* {
    QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Wpedantic
}

TARGET = RobotSim
TEMPLATE = app


SOURCES  += \
    Data.cpp \
    DataVec.cpp \
    Main.cpp \
    RobotSim.cpp \
    Sleep.cpp

HEADERS  += \
    Data.h \
    DataCommon.h \
    DataVec.h \
    RobotSim.h \
    Sleep.h

FORMS    +=

OTHER_FILES +=

RESOURCES +=
