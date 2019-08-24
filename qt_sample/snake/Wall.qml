import Qt3D.Core 2.0

import "factory.js" as Factory

GameEntity {
    id: root
    property alias position: transform.translation
    type: Factory.WALL_TYPE

    Transform {
        id: transform
    }

    components: [transform]
}
