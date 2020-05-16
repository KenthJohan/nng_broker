message("PWD" $$PWD)

TEMPLATE = app
CONFIG += console
CONFIG += c11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

DEFINES += __USE_MINGW_ANSI_STDIO

QMAKE_CFLAGS_WARN_ON += -Wno-unused-function

#NNG
INCLUDEPATH += $$PWD/nng/include
LIBS += -L$$PWD/nng/build
LIBS += -lnng
LIBS += -lws2_32 -lmswsock -ladvapi32 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
