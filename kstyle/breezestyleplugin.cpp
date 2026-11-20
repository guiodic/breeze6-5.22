/*
 * SPDX-FileCopyrightText: 2014 Hugo Pereira Da Costa <hugo.pereira@free.fr>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "breezestyleplugin.h"
#include "breezestyle.h"

#include <QApplication>

namespace Breeze
{
// Keep the fork distinguishable from stock Breeze in qqc2-desktop-style.
class Breeze522Style final : public Style
{
    Q_OBJECT
};

//_________________________________________________
QStyle *StylePlugin::create(const QString &key)
{
    if (key.compare(QLatin1String("breeze-5.22"), Qt::CaseInsensitive) == 0) {
        return new Breeze522Style;
    }
    return nullptr;
}

//_________________________________________________
QStringList StylePlugin::keys() const
{
    return QStringList(QStringLiteral("Breeze-5.22"));
}

}

#include "breezestyleplugin.moc"
