TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    veiculo.cpp \
    via.cpp \
    anotacoes.cpp \
    utilidades.cpp

HEADERS += \
    veiculo.h \
    via.h \
    header.hpp \
    utilidades.h

unix:LIBS += -L /lib/python2.7 -lpython2.7
unix:INCLUDEPATH += /usr/include/python2.7
unix:DEPENDPATH += /usr/include/python2.7

DISTFILES += \
    utilidades.py

