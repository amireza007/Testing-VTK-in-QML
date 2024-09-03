import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import VTK 9.3

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Component.onCompleted: {
        console.log(Qt.resolvedUrl("."))
    }
    // Instantiate the vtk render window
    VTKRenderWindow {
      id: vtkwindow
      width: 400
      height: 400
    }

    // add one or more vtk render items
    VTKRenderItem {
      objectName: "ConeView"
      x: 200
      y: 200
      width: 400
      height: 400
      // Provide the handle to the render window
      renderWindow: vtkwindow
    }
    VTKRenderItem {
      objectName: "VolumeView"
      x: 0
      y: 0
      width: 400
      height: 400
      // Provide the handle to the render window
      renderWindow: vtkwindow
    }
}
