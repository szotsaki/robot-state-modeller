#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T14:10:47
#
#-------------------------------------------------

QT       += core gui widgets network printsupport

QMAKE_CXXFLAGS +=

*-g++* {
    QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Wpedantic
}

TARGET = RobotStateModeller
TEMPLATE = app


SOURCES += main.cpp\
    DataContainer.cpp \
    Monitor.cpp \
    Network.cpp \
    MainWindow.cpp \
    QCustomPlot.cpp \
    ValueWrapper.cpp \
    ValueWrapperFactory.cpp \
    Data/DataInterface.cpp

HEADERS  += \
    DataContainer.h \
    Monitor.h \
    Network.h \
    MainWindow.h \
    QCircularBuffer.h \
    QCustomPlot.h \
    ValueWrapper.h \
    ValueWrapperFactory.h \
    Data/Command.h \
    Data/DataInterface.h \
    Data/State.h \
    Data/DataRw.h \
    Data/DataWriteOnly.h \
    Data/DataVecReadOnly.h

FORMS    += \
    MainWindow.ui

OTHER_FILES +=

RESOURCES += \
    Icons.qrc
