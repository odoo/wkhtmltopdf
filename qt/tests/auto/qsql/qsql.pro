CONFIG += testcase

TARGET = tst_qsql
QT += sql testlib
SOURCES  += tst_qsql.cpp

contains(QT_CONFIG, qt3support): QT += qt3support

wince*: {
   DEPLOYMENT_PLUGIN += qsqlite
}

symbian {
    qt_not_deployed {
        contains(S60_VERSION, 3.1)|contains(S60_VERSION, 3.2)|contains(S60_VERSION, 5.0) {
            sqlite.path = /sys/bin
            sqlite.files = sqlite3.dll
            DEPLOYMENT += sqlite
        }
    }
}
