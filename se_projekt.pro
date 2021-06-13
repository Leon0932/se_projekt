QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addklassenmitgliedview.cpp \
    changepasswortview.cpp \
    createhauptorganisatorview.cpp \
    daten.cpp \
    hauptorganisator.cpp \
    klassenmitglied.cpp \
    kontakt.cpp \
    kontaktview.cpp \
    loginview.cpp \
    main.cpp \
    organisator.cpp \
    profileview.cpp \
    qtdatendao.cpp \
    qthauptorganisatordao.cpp \
    qtklassenmitglieddao.cpp \
    qtkontaktdao.cpp \
    qtorganisatordao.cpp \
    showklassenlisteview.cpp

HEADERS += \
    addklassenmitgliedview.h \
    changepasswortview.h \
    createhauptorganisatorview.h \
    daten.h \
    datendao.h \
    hauptorganisator.h \
    hauptorganisatordao.h \
    klassenmitglied.h \
    klassenmitglieddao.h \
    kontakt.h \
    kontaktdao.h \
    kontaktview.h \
    loginview.h \
    organisator.h \
    organisatordao.h \
    profileview.h \
    qtdatendao.h \
    qthauptorganisatordao.h \
    qtklassenmitglieddao.h \
    qtkontaktdao.h \
    qtorganisatordao.h \
    showklassenlisteview.h

FORMS += \
    addklassenmitgliedview.ui \
    changepasswortview.ui \
    createhauptorganisatorview.ui \
    kontaktview.ui \
    loginview.ui \
    profileview.ui \
    showklassenlisteview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
