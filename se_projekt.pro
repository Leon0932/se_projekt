QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createhauptorganisatorview.cpp \
    daten.cpp \
    hauptorganisator.cpp \
    klassenmitglied.cpp \
    kontakt.cpp \
    main.cpp \
    loginwindow.cpp \
    organisator.cpp \
    qtdatendao.cpp \
    qthauptorganisatordao.cpp \
    qtklassenmitglieddao.cpp \
    qtkontaktdao.cpp \
    qtorganisatordao.cpp

HEADERS += \
    createhauptorganisatorview.h \
    daten.h \
    datendao.h \
    hauptorganisator.h \
    hauptorganisatordao.h \
    klassenmitglied.h \
    klassenmitglieddao.h \
    kontakt.h \
    kontaktdao.h \
    loginwindow.h \
    organisator.h \
    organisatordao.h \
    qtdatendao.h \
    qthauptorganisatordao.h \
    qtklassenmitglieddao.h \
    qtkontaktdao.h \
    qtorganisatordao.h

FORMS += \
    createhauptorganisatorview.ui \
    loginwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
