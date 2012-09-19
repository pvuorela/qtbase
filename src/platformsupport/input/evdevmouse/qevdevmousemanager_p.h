/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QEVDEVMOUSEMANAGER_P_H
#define QEVDEVMOUSEMANAGER_P_H

#include "qevdevmousehandler_p.h"

#include <QtPlatformSupport/private/qdevicediscovery_p.h>

#include <QObject>
#include <QHash>
#include <QSocketNotifier>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QEvdevMouseManager : public QObject
{
    Q_OBJECT
public:
    QEvdevMouseManager(const QString &key, const QString &specification, QObject *parent = 0);
    ~QEvdevMouseManager();

public slots:
    void handleMouseEvent(int x, int y, Qt::MouseButtons buttons);
    void handleWheelEvent(int delta, Qt::Orientation orientation);

private slots:
    void addMouse(const QString &deviceNode = QString());
    void removeMouse(const QString &deviceNode);

private:
    QString m_spec;
    QHash<QString,QEvdevMouseHandler*> m_mice;
    QDeviceDiscovery *m_deviceDiscovery;
    int m_x;
    int m_y;
    int m_xoffset;
    int m_yoffset;
};

QT_END_HEADER

QT_END_NAMESPACE

#endif // QEVDEVMOUSEMANAGER_P_H
