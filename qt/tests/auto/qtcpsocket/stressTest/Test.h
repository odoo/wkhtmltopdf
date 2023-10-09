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
#ifndef TEST_H
#define TEST_H

//------------------------------------------------------------------------------
// Qt
#ifdef QT3_SUPPORT
#include <Q3ServerSocket>
#include <Q3Socket>
#endif

#include <QTcpServer>
#include <QTcpSocket>

//------------------------------------------------------------------------------
#ifdef QT3_SUPPORT
class My3Socket : public Q3Socket
{
    Q_OBJECT
public:
    My3Socket(QObject *parent);

    void sendTest(Q_UINT32 num);
    bool safeShutDown;

private slots:
    void read();
    void closed();
};

//------------------------------------------------------------------------------
class My3Server : public Q3ServerSocket
{
    Q_OBJECT
public:
    My3Server(QObject *parent = 0);

    void newConnection(int socket);

private slots:
    void stopServer();

private:
    My3Socket *m_socket;
};
#endif

//------------------------------------------------------------------------------
class My4Socket : public QTcpSocket
{
    Q_OBJECT
public:
    My4Socket(QObject *parent);

    void sendTest(quint32 num);
    bool safeShutDown;

private slots:
    void read();
    void closed();
};

//------------------------------------------------------------------------------
class My4Server : public QTcpServer
{
    Q_OBJECT
public:
    My4Server(QObject *parent = 0);

protected:
    void incomingConnection(int socket);

private slots:
    void stopServer();

private:
    My4Socket *m_socket;
};

//------------------------------------------------------------------------------
class Test : public QObject
{
    Q_OBJECT

public:
    enum Type {
        Qt4Client,
        Qt4Server,
#ifdef QT3_SUPPORT
        Qt3Client,
        Qt3Server
#endif
    };
    Test(Type type);
};

//------------------------------------------------------------------------------
#endif	// TEST_H