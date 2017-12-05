import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 600
    height: 600
    title: qsTr("Circles")

    Repeater {
        model: circleModel
        delegate: Rectangle {
            radius: 30
            width: 60
            height: 60
            x: model.circlePosX - width / 2
            y: model.circlePosY - height / 2
            color: model.circleColor

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (model.isReadyToDie) {
                        circleModel.removeCircle(index);
                    } else {
                        circleModel.changeColor(index);
                    }
                }
            }
        }
    }

    onWidthChanged: {
        circleManager.fieldWidth = width;
    }

    onHeightChanged: {
        circleManager.fieldHeight = height;
    }

    Component.onCompleted: {
        circleManager.fieldWidth = width;
        circleManager.fieldHeight = height;
    }
}
