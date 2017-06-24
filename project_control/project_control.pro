TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../VK-master/src/api.cpp \
    ../VK-master/src/attachment.cpp \
    ../VK-master/src/messages.cpp \
    comments.cpp

INCLUDEPATH += $$PWD/curl/include

LIBS += -L$$PWD/curl/lib -lcurldll

HEADERS += \
    ../VK-master/src/api.h \
    ../VK-master/src/attachment.h \
    ../VK-master/src/json.hpp \
    ../VK-master/src/messages.h \
    comments.h
