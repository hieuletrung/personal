import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 400
    height: 400
    title: qsTr("My App")

    MainForm
    {
        anchors.fill: parent
        loginMouseArea.onClicked: {
            console.log("Login pressed");
        }

        emailTouch.onClicked: {
            emailDisplay.visible = false; // Hide emailDisplay
            emailInput.forceActiveFocus(); // Focus emailInput
            Qt.inputMethod.show(); // Activate virtual keyboard
        }

        emailInput.onFocusChanged: {
            if (emailInput.focus == false && emailInput.text == "") {
                emailDisplay.visible = true; // Show emailDisplay if emailInput is empty when loses focus
            }
        }

        passwordTouch.onClicked: {
            passwordDisplay.visible = false; // Hide passwordDisplay
            passwordInput.forceActiveFocus(); // Focus passwordInput
            Qt.inputMethod.show(); // Activate virtual keyboard
        }

        passwordInput.onFocusChanged: {
            if (passwordInput.focus == false && passwordInput.text == "") {
                passwordDisplay.visible = true; // Show passwordDisplay if passwordInput is empty when loses focus
            }
        }
    }
}
