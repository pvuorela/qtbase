/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QTEXTBOUNDARYFINDER_H
#define QTEXTBOUNDARYFINDER_H

#include <QtCore/qchar.h>
#include <QtCore/qstring.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE


class QTextBoundaryFinderPrivate;

class Q_CORE_EXPORT QTextBoundaryFinder
{
public:
    QTextBoundaryFinder();
    QTextBoundaryFinder(const QTextBoundaryFinder &other);
    QTextBoundaryFinder &operator=(const QTextBoundaryFinder &other);
    ~QTextBoundaryFinder();

    enum BoundaryType {
        Grapheme,
        Word,
        Line,
        Sentence
    };

    enum BoundaryReason {
        NotAtBoundary = 0,
        StartWord = 1,
        EndWord = 2,
        SoftHyphen = 4
    };
    Q_DECLARE_FLAGS( BoundaryReasons, BoundaryReason )

    QTextBoundaryFinder(BoundaryType type, const QString &string);
    QTextBoundaryFinder(BoundaryType type, const QChar *chars, int length, unsigned char *buffer = 0, int bufferSize = 0);

    inline bool isValid() const { return d; }

    inline BoundaryType type() const { return t; }
    QString string() const;

    void toStart();
    void toEnd();
    int position() const;
    void setPosition(int position);

    int toNextBoundary();
    int toPreviousBoundary();

    bool isAtBoundary() const;
    BoundaryReasons boundaryReasons() const;

private:
    BoundaryType t;
    QString s;
    const QChar *chars;
    int length;
    int pos;
    uint freePrivate : 1;
    uint unused : 31;
    QTextBoundaryFinderPrivate *d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QTextBoundaryFinder::BoundaryReasons)

QT_END_NAMESPACE

QT_END_HEADER

#endif

