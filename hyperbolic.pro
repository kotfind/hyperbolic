TARGET = hyperbolic

QT += widgets sql

CONFIG += c++17

QMAKE_CXXFLAGS = -I $$_PRO_FILE_PWD_/include $$_PRO_FILE_PWD_/lib/x64/libLeap.so

HEADERS += $$_PRO_FILE_PWD_/src/*.h
SOURCES += $$_PRO_FILE_PWD_/src/*.cpp
