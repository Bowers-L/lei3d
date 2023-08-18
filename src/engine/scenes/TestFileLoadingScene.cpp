#include "TestFileLoadingScene.hpp"

#include "core/Application.hpp"
#include "core/scene_loading/FileSceneLoader.hpp"

//#include "components/CharacterController.hpp"
#include "components/SkyBox.hpp"
//#include "components/StaticCollider.hpp"


namespace lei3d {
    TestFileLoadingScene::TestFileLoadingScene() {
    }

    TestFileLoadingScene::~TestFileLoadingScene() {

    }

    void TestFileLoadingScene::OnLoad() {
        //Temporary instantiating this loader for testing
        FileSceneLoader sceneLoader("data/scenes/TestSceneFile.lei");
        sceneLoader.Load(*this);
    }

    void TestFileLoadingScene::OnPhysicsUpdate() {
        m_PhysicsWorld->Step(Application::DeltaTime());
    }
}