QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_class.cpp \
    add_student.cpp \
    add_teacher.cpp \
    json.cpp \
    main.cpp \
    management_system.cpp

HEADERS += \
    add_class.h \
    add_student.h \
    add_teacher.h \
    json.h \
    management_system.h

FORMS += \
    add_class.ui \
    add_student.ui \
    add_teacher.ui \
    management_system.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
