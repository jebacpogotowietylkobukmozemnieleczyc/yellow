TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    newton.cpp \
    IntervalArithmetic.cpp \
    Interval.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    newton.hpp \
    Interval.h \
    ErrorCode.h \
    IntervalArithmetic.h \
    Number.h \
    conversion.h

LIBS += -lmpfr -lgmp
