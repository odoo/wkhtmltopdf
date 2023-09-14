SOURCES = fontconfig.cpp
CONFIG += x11
CONFIG -= qt
LIBS += -lfreetype -lfontconfig -lexpat
include(../../unix/freetype/freetype.pri)
