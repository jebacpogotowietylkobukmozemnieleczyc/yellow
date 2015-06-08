import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import com.ean.newton 1.0

ApplicationWindow {
    title: qsTr("Yellow Project")

    statusBar: StatusBar {
    RowLayout {
        Label {
            id: status
            }
        }
    }

    width: 369
    height: 250

    ColumnLayout {
        x: 10
        y: 10

        // Key
        RowLayout {
        Label {
            text: qsTr("Arytmetyka:")
        }
        ComboBox {
            id: combobox
            Layout.fillWidth: true
            model: newton.types
            currentIndex: 0
        }
    }


        // Filename
        RowLayout {
            Label {
                text: qsTr("Library:")
            }
            TextField {
                id: filename
                text: qsTr("testlib.dll")
                implicitWidth: 200
                onTextChanged: updateStatusBar()
            }
            Button {
                text: qsTr("&Browse...")
                onClicked: filedialog.visible = true
            }
        }

        // mfunction
        RowLayout {
            Label {
                text: qsTr("Funkcja:")
            }
            TextField {
                id: mfunction
                text: qsTr("funtion")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }

        }

        // mdfunction
        RowLayout {
            Label {
                text: qsTr("Pochodna funkcja:")
            }
            TextField {
                id: mdfunction
                text: qsTr("dfuntion")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }

        }
        // X
        RowLayout {
            Label {
                text: qsTr("x:")
            }
            TextField {
                id: x
                text: qsTr("1")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }
            TextField {
                id: x2
                text: qsTr("")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }
        }

        // mit
        RowLayout {
            Label {
                text: qsTr("Mit:")
            }
            TextField {
                id:mit
                text: qsTr("100")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }
        }

        // Eps
        RowLayout {
            Label {
                text: qsTr("Eps:")
            }
            TextField {
                id: eps
                text: qsTr("1e-16")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }
        }

        // Buttons: Generate, Quit
        RowLayout {
            Button {
                id: generate
                text: qsTr("&Calculate")
                onClicked: newton.generateResult(x.text,mit.text,eps.text)
            }
            Button {
                text: qsTr("&Quit")
                onClicked: Qt.quit()
            }
        }

    }

    FileDialog {
        id: filedialog
        title: qsTr("Select a file")
        selectMultiple: false
        selectFolder: false
        nameFilters: [ "All files (*)" ]
        selectedNameFilter: "All files (*)"
        onAccepted: {
            filename.text = fileUrl.toString().replace("file://", "")
        }
    }

    Newton {
        id: newton
        filename: filename.text
        mfunction: mfunction.text
        mdfunction: mdfunction.text
        x: x.text
        x2: x2.text
        mit:mit.text
        eps:eps.text
        type:combobox.currentText
        onResultGenerated: {
            //if (success) {
                status.text = qsTr('<font color="green">Wynik: </font>'+result+'<br />
                                   <font color="green">width: </font>'+width+'<br />
                                   <font color="green">fx: </font>'+fx+'<br />
                                   <font color="green">status: </font>'+state+'<br />
                                   <font color="green">i: </font>'+i)
            //} else {
              //  status.text = qsTr('<font color="red">Key generation failed</font>')
            //}
        }
    }

    function updateStatusBar() {

        if (mfunction.text == "") {
            status.text = qsTr('<font color="red">Pole funkcji jest puste.</font>')
            generate.enabled = false
        } else if (mdfunction.text == "") {
            status.text = qsTr('<font color="red">Pole pochodnej funkcji jest puste.</font>')
            generate.enabled = false
        } else if (filename.text == "") {
            status.text = qsTr('<font color="red">Pole nazwy pliku jest puste.</font>')
            generate.enabled = false
        } else if (x.text == "") {
            status.text = qsTr('<font color="red">Pole x jest puste.</font>')
            generate.enabled = false
        } else if (eps.text == "") {
            status.text = qsTr('<font color="red">Pole eps jest puste.</font>')
            generate.enabled = false
        } else if (mit.text == "") {
            status.text = qsTr('<font color="red">Pole mit jest puste.</font>')
            generate.enabled = false
        } else if (mit.text == "") {
            status.text = qsTr('<font color="red">Pole mit jest puste.</font>')
            generate.enabled = false
        } else {
            status.text = ""
            generate.enabled = true
        }

    }

    Component.onCompleted: updateStatusBar()
}
