// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import org.kde.desktop as Desktop

Desktop.ComboBox {
    id: control

    delegate: MenuItem {
        required property var model
        required property int index
        text: model[control.textRole]
        highlighted: control.highlightedIndex === index
    }
}
