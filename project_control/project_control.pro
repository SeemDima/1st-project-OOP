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
    ../../total_control/total_control/timestamp.cpp \
    controller.cpp

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
    ../../total_control/total_control/timestamp.h \
    controller.h
