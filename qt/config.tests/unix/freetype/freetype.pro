SOURCES = freetype.cpp
CONFIG += x11
CONFIG -= qt
LIBS += -lfreetype -lbrotlidec -lbrotlicommon
include(freetype.pri)
