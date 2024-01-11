/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QATOMIC_H
#define QATOMIC_H

#include <QtCore/qglobal.h>
#include <QtCore/qbasicatomic.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Core)

// High-level atomic integer operations
class Q_CORE_EXPORT QAtomicInt : public QBasicAtomicInt
{
public:
    inline QAtomicInt(int value = 0)
    {
        _q_value = value;
    }
    inline QAtomicInt(const QAtomicInt &other)
    {
        _q_value = other._q_value;
    }

    inline QAtomicInt &operator=(int value)
    {
        (void) QBasicAtomicInt::operator=(value);
        return *this;
    }

    inline QAtomicInt &operator=(const QAtomicInt &other)
    {
        (void) QBasicAtomicInt::operator=(other._q_value);
        return *this;
    }
};

// High-level atomic pointer operations
template <typename T>
class QAtomicPointer : public QBasicAtomicPointer<T>
{
public:
    inline QAtomicPointer(T *value = 0)
    {
        QBasicAtomicPointer<T>::_q_value = value;
    }
    inline QAtomicPointer(const QAtomicPointer<T> &other)
    {
        QBasicAtomicPointer<T>::_q_value = other._q_value;
    }

    inline QAtomicPointer<T> &operator=(T *value)
    {
        (void) QBasicAtomicPointer<T>::operator=(value);
        return *this;
    }

    inline QAtomicPointer<T> &operator=(const QAtomicPointer<T> &other)
    {
        (void) QBasicAtomicPointer<T>::operator=(other);
        return *this;
    }
};

/*!
    This is a helper for the assignment operators of implicitly
    shared classes. Your assignment operator should look like this:

    \snippet doc/src/snippets/code/src.corelib.thread.qatomic.h 0
*/
template <typename T>
inline void qAtomicAssign(T *&d, T *x)
{
    if (d == x)
        return;
    x->ref.ref();
    if (!d->ref.deref())
        delete d;
    d = x;
}

/*!
    This is a helper for the detach method of implicitly shared
    classes. Your private class needs a copy constructor which copies
    the members and sets the refcount to 1. After that, your detach
    function should look like this:

    \snippet doc/src/snippets/code/src.corelib.thread.qatomic.h 1
*/
template <typename T>
inline void qAtomicDetach(T *&d)
{
    if (d->ref == 1)
        return;
    T *x = d;
    d = new T(*d);
    if (!x->ref.deref())
        delete x;
}

QT_END_NAMESPACE
QT_END_HEADER

#endif // QATOMIC_H
