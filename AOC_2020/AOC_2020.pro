QT -= gui
QT += concurrent

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Y20Day02.cpp \
        Y20Day03.cpp \
        Y20Day04.cpp \
        Y20Day05.cpp \
        Y20Day06.cpp \
        Y20Day07.cpp \
        Y20Day08.cpp \
        Y20Day09.cpp \
        Y20Day1.cpp \
        Y20Day10.cpp \
        Y20Day11.cpp \
        Y20Day12.cpp \
        Y20Day13.cpp \
        Y20Day14.cpp \
        Y20Day15.cpp \
        Y20Day16.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Y20Day02.h \
    Y20Day03.h \
    Y20Day04.h \
    Y20Day05.h \
    Y20Day06.h \
    Y20Day07.h \
    Y20Day08.h \
    Y20Day09.h \
    Y20Day1.h \
    Y20Day10.h \
    Y20Day11.h \
    Y20Day12.h \
    Y20Day13.h \
    Y20Day14.h \
    Y20Day15.h \
    Y20Day16.h
