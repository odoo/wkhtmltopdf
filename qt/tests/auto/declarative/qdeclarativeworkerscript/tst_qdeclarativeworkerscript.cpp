/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <qtest.h>
#include <QtCore/qdebug.h>
#include <QtCore/qtimer.h>
#include <QtCore/qdir.h>
#include <QtCore/qfileinfo.h>
#include <QtScript/qscriptengine.h>

#include <QtDeclarative/qdeclarativecomponent.h>
#include <QtDeclarative/qdeclarativeengine.h>
#include <QtDeclarative/qdeclarativeitem.h>

#include <private/qdeclarativeworkerscript_p.h>
#include <private/qdeclarativeengine_p.h>
#include "../../../shared/util.h"

Q_DECLARE_METATYPE(QScriptValue)

#ifdef Q_OS_SYMBIAN
// In Symbian OS test data is located in applications private dir
#define SRCDIR "."
#endif

inline QUrl TEST_FILE(const QString &filename)
{
    QFileInfo fileInfo(__FILE__);
    return QUrl::fromLocalFile(fileInfo.absoluteDir().filePath(filename));
}


class tst_QDeclarativeWorkerScript : public QObject
{
    Q_OBJECT
public:
    tst_QDeclarativeWorkerScript() {}
private slots:
    void source();
    void messaging();
    void messaging_data();
    void messaging_sendQObjectList();
    void messaging_sendJsObject();
    void script_with_pragma();
    void script_included();
    void scriptError_onLoad();
    void scriptError_onCall();

private:
    void waitForEchoMessage(QDeclarativeWorkerScript *worker) {
        QEventLoop loop;
        QVERIFY(connect(worker, SIGNAL(done()), &loop, SLOT(quit())));
        QTimer timer;
        timer.setSingleShot(true);
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start(10000);
        loop.exec();
        QVERIFY(timer.isActive());
    }

    QDeclarativeEngine m_engine;
};

void tst_QDeclarativeWorkerScript::source()
{
    QDeclarativeComponent component(&m_engine, SRCDIR "/data/worker.qml");
    QDeclarativeWorkerScript *worker = qobject_cast<QDeclarativeWorkerScript*>(component.create());
    QVERIFY(worker != 0);
    const QMetaObject *mo = worker->metaObject();

    QVariant value(100);
    QVERIFY(QMetaObject::invokeMethod(worker, "testSend", Q_ARG(QVariant, value)));
    waitForEchoMessage(worker);
    QCOMPARE(mo->property(mo->indexOfProperty("response")).read(worker).value<QVariant>(), value);

    QUrl source = QUrl::fromLocalFile(SRCDIR "/data/script_fixed_return.js");
    worker->setSource(source);
    QCOMPARE(worker->source(), source);
    QVERIFY(QMetaObject::invokeMethod(worker, "testSend", Q_ARG(QVariant, value)));
    waitForEchoMessage(worker);
    QCOMPARE(mo->property(mo->indexOfProperty("response")).read(worker).value<QVariant>(), qVariantFromValue(QString("Hello_World")));

    qApp->processEvents();
    delete worker;
}

void tst_QDeclarativeWorkerScript::messaging()
{
    QFETCH(QVariant, value);

    QDeclarativeComponent component(&m_engine, SRCDIR "/data/worker.qml");
    QDeclarativeWorkerScript *worker = qobject_cast<QDeclarativeWorkerScript*>(component.create());
    QVERIFY(worker != 0);

    QVERIFY(QMetaObject::invokeMethod(worker, "testSend", Q_ARG(QVariant, value)));
    waitForEchoMessage(worker);

    const QMetaObject *mo = worker->metaObject();
    QCOMPARE(mo->property(mo->indexOfProperty("response")).read(worker).value<QVariant>(), value);

    qApp->processEvents();
    delete worker;
}

void tst_QDeclarativeWorkerScript::messaging_data()
{
    QTest::addColumn<QVariant>("value");

    QTest::newRow("invalid") << QVariant();
    QTest::newRow("bool") << qVariantFromValue(true);
    QTest::newRow("int") << qVariantFromValue(1001);
    QTest::newRow("real") << qVariantFromValue(10334.375);
    QTest::newRow("string") << qVariantFromValue(QString("More cheeeese, Gromit!"));
    QTest::newRow("variant list") << qVariantFromValue((QVariantList() << "a" << "b" << "c"));
    QTest::newRow("date time") << qVariantFromValue(QDateTime::currentDateTime());
#ifndef QT_NO_REGEXP
    // QtScript's QScriptValue -> QRegExp uses RegExp2 pattern syntax
    QTest::newRow("regexp") << qVariantFromValue(QRegExp("^\\d\\d?$", Qt::CaseInsensitive, QRegExp::RegExp2));
#endif
}

void tst_QDeclarativeWorkerScript::messaging_sendQObjectList()
{
    // Not allowed to send QObjects other than QDeclarativeWorkerListModelAgent
    // instances. If objects are sent in a list, they will be sent as 'undefined'
    // js values.

    QDeclarativeComponent component(&m_engine, SRCDIR "/data/worker.qml");
    QDeclarativeWorkerScript *worker = qobject_cast<QDeclarativeWorkerScript*>(component.create());
    QVERIFY(worker != 0);

    QVariantList objects;
    for (int i=0; i<3; i++)
        objects << qVariantFromValue(new QObject(this));

    QVERIFY(QMetaObject::invokeMethod(worker, "testSend", Q_ARG(QVariant, qVariantFromValue(objects))));
    waitForEchoMessage(worker);

    const QMetaObject *mo = worker->metaObject();
    QVariantList result = mo->property(mo->indexOfProperty("response")).read(worker).value<QVariantList>();
    QCOMPARE(result, (QVariantList() << QVariant() << QVariant() << QVariant()));

    qApp->processEvents();
    delete worker;
}

void tst_QDeclarativeWorkerScript::messaging_sendJsObject()
{
    QDeclarativeComponent component(&m_engine, SRCDIR "/data/worker.qml");
    QDeclarativeWorkerScript *worker = qobject_cast<QDeclarativeWorkerScript*>(component.create());
    QVERIFY(worker != 0);

    // Properties are in alphabetical order to enable string-based comparison after
    // QVariant roundtrip, since the properties will be stored in a QVariantMap.
    QString jsObject = "{'haste': 1125, 'name': 'zyz', 'spell power': 3101}";

    QScriptEngine *engine = QDeclarativeEnginePrivate::getScriptEngine(qmlEngine(worker));
    QScriptValue sv = engine->newObject();
    sv.setProperty("haste", 1125);
    sv.setProperty("name", "zyz");
    sv.setProperty("spell power", 3101);

    QVERIFY(QMetaObject::invokeMethod(worker, "testSend", Q_ARG(QVariant, qVariantFromValue(sv))));
    waitForEchoMessage(worker);

    QVariant result = qVariantFromValue(false);
    QVERIFY(QMetaObject::invokeMethod(worker, "compareLiteralResponse", Qt::DirectConnection, 
            Q_RETURN_ARG(QVariant, result), Q_ARG(QVariant, jsObject)));
    QVERIFY(result.toBool());

    qApp->processEvents();
    delete worker;
}

void tst_QDeclarativeWorkerScript::script_with_pragma()
{
    QVariant value(100);

    QDeclarativeComponent component(&m_engine, SRCDIR "/data/worker_pragma.qml");
    QDeclarativeWorkerScript *worker = qobject_cast<QDeclarativeWorkerScript*>(component.create());
    QVERIFY(worker != 0);

    QVERIFY(QMetaObject::invokeMethod(worker, "testSend", Q_ARG(QVariant, value)));
    waitForEchoMessage(worker);

    const QMetaObject *mo = worker->metaObject();
    QCOMPARE(mo->property(mo->indexOfProperty("response")).read(worker).value<QVariant>(), value);

    qApp->processEvents();
    delete worker;
}

void tst_QDeclarativeWorkerScript::script_included()
{
    QDeclarativeComponent component(&m_engine, SRCDIR "/data/worker_include.qml");
    QDeclarativeWorkerScript *worker = qobject_cast<QDeclarativeWorkerScript*>(component.create());
    QVERIFY(worker != 0);

    QString value("Hello");

    QVERIFY(QMetaObject::invokeMethod(worker, "testSend", Q_ARG(QVariant, value)));
    waitForEchoMessage(worker);

    const QMetaObject *mo = worker->metaObject();
    QCOMPARE(mo->property(mo->indexOfProperty("response")).read(worker).toString(), value + " World");

    qApp->processEvents();
    delete worker;
}

static QString qdeclarativeworkerscript_lastWarning;
static void qdeclarativeworkerscript_warningsHandler(QtMsgType type, const char *msg)
{
    if (type == QtWarningMsg)
         qdeclarativeworkerscript_lastWarning = QString::fromUtf8(msg);
}

void tst_QDeclarativeWorkerScript::scriptError_onLoad()
{
    QDeclarativeComponent component(&m_engine, SRCDIR "/data/worker_error_onLoad.qml");

    QtMsgHandler previousMsgHandler = qInstallMsgHandler(qdeclarativeworkerscript_warningsHandler);
    QDeclarativeWorkerScript *worker = qobject_cast<QDeclarativeWorkerScript*>(component.create());
    QVERIFY(worker != 0);

    QTRY_COMPARE(qdeclarativeworkerscript_lastWarning,
            TEST_FILE("data/script_error_onLoad.js").toString() + QLatin1String(":3: SyntaxError: Parse error"));

    qInstallMsgHandler(previousMsgHandler);
    qApp->processEvents();
    delete worker;
}

void tst_QDeclarativeWorkerScript::scriptError_onCall()
{
    QDeclarativeComponent component(&m_engine, SRCDIR "/data/worker_error_onCall.qml");
    QDeclarativeWorkerScript *worker = qobject_cast<QDeclarativeWorkerScript*>(component.create());
    QVERIFY(worker != 0);

    QtMsgHandler previousMsgHandler = qInstallMsgHandler(qdeclarativeworkerscript_warningsHandler);
    QVariant value;
    QVERIFY(QMetaObject::invokeMethod(worker, "testSend", Q_ARG(QVariant, value)));

    QTRY_COMPARE(qdeclarativeworkerscript_lastWarning,
            TEST_FILE("data/script_error_onCall.js").toString() + QLatin1String(":4: ReferenceError: Can't find variable: getData"));

    qInstallMsgHandler(previousMsgHandler);
    qApp->processEvents();
    delete worker;
}


QTEST_MAIN(tst_QDeclarativeWorkerScript)

#include "tst_qdeclarativeworkerscript.moc"
