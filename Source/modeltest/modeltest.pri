CONFIG += testcase
TARGET = tst_modeltest
QT += widgets testlib
SOURCES         += modeltest/modeltest.cpp modeltest/dynamictreemodel.cpp
HEADERS         += modeltest/modeltest.h modeltest/dynamictreemodel.h



DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
