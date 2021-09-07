import QtQuick 2.12
import QtQml 2.12
import QtQuick.Window 2.10

import App 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("TouchEvent Test")

    TouchItem {
          anchors.fill: parent
      }
}
