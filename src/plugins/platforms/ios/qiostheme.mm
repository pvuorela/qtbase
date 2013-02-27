/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
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

#include "qiostheme.h"

#include <QtCore/QStringList>
#include <QtCore/QVariant>

#include <QtGui/QFont>

#include <UIKit/UIFont.h>
#include <UIKit/UIInterface.h>

QT_BEGIN_NAMESPACE

const char *QIOSTheme::name = "ios";

QIOSTheme::QIOSTheme()
{
}

QIOSTheme::~QIOSTheme()
{
}

QVariant QIOSTheme::themeHint(ThemeHint hint) const
{
    switch (hint) {
    case QPlatformTheme::StyleNames:
        return QStringList(QStringLiteral("fusion"));
    default:
        return QPlatformTheme::themeHint(hint);
    }
}

const QFont *QIOSTheme::font(Font type) const
{
    static QHash<QPlatformTheme::Font, QFont *> fonts;
    if (fonts.isEmpty()) {
        // The real system font on iOS is '.Helvetica Neue UI', as returned by both [UIFont systemFontOfSize]
        // and CTFontCreateUIFontForLanguage(kCTFontSystemFontType, ...), but this font is not included when
        // populating the available fonts in QCoreTextFontDatabase::populateFontDatabase(), since the font
        // is internal to iOS and not supposed to be used by applications. We could potentially add this
        // font to the font-database, but it would then show up when enumerating user fonts from Qt
        // applications since we don't have a flag in Qt to mark a font as a private system font.
        // For now we hard-code the font to Helvetica, which should be very close to the actual
        // system font.
        QLatin1String systemFontFamilyName("Helvetica");
        fonts.insert(QPlatformTheme::SystemFont, new QFont(systemFontFamilyName, [UIFont systemFontSize]));
        fonts.insert(QPlatformTheme::SmallFont, new QFont(systemFontFamilyName, [UIFont smallSystemFontSize]));
        fonts.insert(QPlatformTheme::LabelFont, new QFont(systemFontFamilyName, [UIFont labelFontSize]));
        fonts.insert(QPlatformTheme::PushButtonFont, new QFont(systemFontFamilyName, [UIFont buttonFontSize]));
    }

    return fonts.value(type, 0);
}

QT_END_NAMESPACE