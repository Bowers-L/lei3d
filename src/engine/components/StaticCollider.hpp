#pragma once

#include "core/Component.hpp"
#include "rendering/Model.hpp"

namespace lei3d
{
    class Entity;
    class Component;

    class StaticCollider : public Component
    {
    public:
        StaticCollider(Entity& entity);

        void Init();
        void SetColliderToModel(const Model& model);

        void OnEditorUpdate() override;
    private:
        void AddCollisionsFromTriangleMesh(btTriangleMesh* triMesh, const Transform& transform);
    };
}