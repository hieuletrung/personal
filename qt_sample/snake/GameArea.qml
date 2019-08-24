import QtQuick 2.0
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.0

Entity {
    id: root
    property alias gameRoot: root

    Camera {
        id: camera
        property real x: 24.5
        property real y: 14.0
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( x, y, 33.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( x, y, 0.0 )
    }

    RenderSettings {
        id: frameFraph
        activeFrameGraph: ForwardRenderer {
            clearColor: Qt.rgba(0, 0, 0, 1)
            camera: camera
        }
    }

    components: [frameFraph]
}
