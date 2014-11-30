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


SOURCES += Main.cpp\
    RobotSim.cpp

HEADERS  += \
    RobotSim.h

FORMS    +=

OTHER_FILES +=

RESOURCES +=
