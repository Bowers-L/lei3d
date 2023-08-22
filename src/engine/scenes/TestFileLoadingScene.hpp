#pragma once 

// #include "core/Entity.hpp"
#include "core/Scene.hpp"

// #include "rendering/Shader.hpp"

// #include "physics/PhysicsWorld.hpp"

namespace lei3d {
     class Entity;
     class Model;
     class Shader;
     class SkyBox;
     class PhysicsWorld;

    class TestFileLoadingScene : public Scene {
    private:
        std::string m_SceneFilepath;
    public:
        TestFileLoadingScene(std::string filepath);
        ~TestFileLoadingScene();

        void OnLoad() override;
        void OnPhysicsUpdate() override;
    };
}