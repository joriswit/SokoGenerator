#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T16:57:49
#
#-------------------------------------------------

#QT       -= gui
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SokoSolverPlugin
TEMPLATE = lib

CONFIG += c++11
QMAKE_CFLAGS += -std=c99
QMAKE_LFLAGS += -Wl,--kill-at -static -static-libgcc -static-libstdc++ -lpthread

DEFINES += SOKOSOLVERPLUGIN_LIBRARY

SOURCES += sokosolverplugin.cpp \
    solvercpp/solver.cpp \
    solvercpp/allocator.c \
    solvercpp/crs.c \
    solvercpp/deadlock_table.c \
    solvercpp/global.c \
    solvercpp/hashtable.c \
    solvercpp/level.c \
    solvercpp/level_info.c \
    solvercpp/move.c \
    solvercpp/position.c \
    solvercpp/queue.c \
    solvercpp/solution.c \
    solvercpp/solving_routine.c

HEADERS += sokobanpluginsdll.h \
    solvercpp/allocator.h \
    solvercpp/crs.h \
    solvercpp/deadlock_table.h \
    solvercpp/global.h \
    solvercpp/hashtable.h \
    solvercpp/level.h \
    solvercpp/level_info.h \
    solvercpp/move.h \
    solvercpp/position.h \
    solvercpp/queue.h \
    solvercpp/solution.h \
    solvercpp/solver.h \
    solvercpp/solving_routine.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32: RC_ICONS = SokoGenerator.ico

RESOURCES += \
    resources.qrc
