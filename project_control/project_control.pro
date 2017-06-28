TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../VK-master/src/api.cpp \
    ../VK-master/src/attachment.cpp \
    ../VK-master/src/messages.cpp \
    ../gtest/googletest/src/gtest-all.cc \
    post.cpp \
    tests.cpp \
    controller.cpp \
    ../Timestamp/timestamp.cpp

INCLUDEPATH += $$PWD/curl/include \
    ../gtest/googletest/include \
    ../gtest/googletest

LIBS += -L$$PWD/curl/lib -lcurldll

HEADERS += \
    ../VK-master/src/api.h \
    ../VK-master/src/attachment.h \
    ../VK-master/src/json.hpp \
    ../VK-master/src/messages.h \
    post.h \
    controller.h \
    ../Timestamp/timestamp.h
