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
    Main.cpp \
    Random.cpp \
    RobotSim.cpp

HEADERS  += \
    Data.h \
    DataCommon.h \
    DataVec.h \
    Random.h \
    RobotSim.h

FORMS    +=

OTHER_FILES +=

RESOURCES +=
