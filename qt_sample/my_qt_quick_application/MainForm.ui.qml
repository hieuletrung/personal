import QtQuick 2.6
import QtQuick.Controls 2.2

Item {
    id: loginForm
    width: 400
    height: 400
    property alias emailTouch: emailTouch
    property alias passwordTouch: passwordTouch
    property alias loginMouseArea: loginMouseArea
    property alias emailDisplay: emailDisplay
    property alias emailInput: emailInput
    property alias passwordDisplay: passwordDisplay
    property alias passwordInput: passwordInput
    opacity: 1

    Image {
        id: background
        x: 0
        y: 0
        width: 400
        height: 400
        fillMode: Image.Stretch
        source: "qrc:/images/background.jpg"

        Rectangle {
            id: loginRect
            x: 100
            y: 150
            width: 402
            height: 210
            color: "#fcf9f4"
            anchors.verticalCenterOffset: 50
            anchors.verticalCenter: parent.verticalCenter
            border.color: "#efedeb"
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: image
                width: 100
                height: 100
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: -110
                fillMode: Image.PreserveAspectFit
                source: "qrc:/images/logo_sample.png"
            }

            Rectangle {
                id: passwordRect
                y: 0
                height: 35
                color: "#ffffff"
                border.color: "#efedeb"
                anchors.verticalCenterOffset: -18
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 25

                TextInput {
                    id: passwordInput
                    height: 20
                    text: qsTr("")
                    echoMode: TextInput.Password
                    anchors.verticalCenterOffset: 2
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 40
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    selectionColor: "#4f0080"
                    font.pixelSize: 12
                }

                Image {
                    id: image1
                    width: 18
                    height: 18
                    opacity: 0.6
                    anchors.verticalCenterOffset: 0
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/images/password-icon.png"
                }

                MouseArea {
                    id: passwordTouch
                    anchors.fill: parent
                }

                Text {
                    id: passwordDisplay
                    color: "#cbbdbd"
                    text: qsTr("Password")
                    enabled: false
                    anchors.verticalCenterOffset: -1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 41
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    font.pixelSize: 12
                }
            }

            Rectangle {
                id: loginButton
                height: 35
                color: "#27ae61"
                radius: 2
                border.width: 0
                anchors.verticalCenterOffset: 35
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 25

                MouseArea {
                    id: loginMouseArea
                    visible: true
                    anchors.fill: parent
                }

                Text {
                    id: loginText
                    color: "#ffffff"
                    text: qsTr("LOGIN")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                }
            }

            Rectangle {
                id: emailRect
                x: 26
                y: -100
                height: 35
                color: "#ffffff"
                anchors.verticalCenterOffset: -55
                anchors.verticalCenter: parent.verticalCenter
                border.color: "#efedeb"
                anchors.right: parent.right
                anchors.rightMargin: 25
                anchors.left: parent.left
                anchors.leftMargin: 25

                TextInput {
                    id: emailInput
                    y: -32
                    height: 20
                    text: qsTr("")
                    selectionColor: "#4f0080"
                    anchors.verticalCenterOffset: 3
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 40
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    font.pixelSize: 12
                }

                Image {
                    id: image2
                    width: 18
                    height: 18
                    opacity: 0.6
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/images/email-icon.png"
                }

                MouseArea {
                    id: emailTouch
                    anchors.fill: parent
                    hoverEnabled: false
                }

                Text {
                    id: emailDisplay
                    color: "#cbbdbd"
                    text: qsTr("E-Mail")
                    enabled: false
                    anchors.verticalCenterOffset: -1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 40
                    anchors.left: parent.left
                    anchors.leftMargin: 21
                    font.pixelSize: 12
                }
            }
        }
    }
}




/*##^## Designer {
    D{i:5;anchors_width:80}D{i:7;anchors_height:100;anchors_width:100;anchors_x:0;anchors_y:"-37"}
D{i:4;anchors_width:200;anchors_x:0}D{i:10;anchors_height:100;anchors_width:100}D{i:9;anchors_width:200}
D{i:13;anchors_width:80;anchors_x:"-25"}D{i:15;anchors_height:100;anchors_width:100}
D{i:12;anchors_width:200}
}
 ##^##*/
