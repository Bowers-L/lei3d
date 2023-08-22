#include "SceneManager.hpp"

#include "scenes/EmptyScene.hpp"
#include "scenes/TestSceneKevin.hpp"
#include "scenes/TestSceneLogan.hpp"
#include "scenes/TestFileLoadingScene.hpp"

namespace lei3d {
    SceneManager* SceneManager::s_Instance = nullptr;

    SceneManager::SceneManager()
    {
        if (s_Instance)
        {
            LEI_ERROR("Multiple instances detected. Only one SceneManager should exist.");
        }

        s_Instance = this;
    }

    void SceneManager::Init()
    {
        m_AllScenes.push_back({ "Test File Loading", std::make_unique<TestFileLoadingScene>("data/scenes/TestSceneFile.lei") });
        m_AllScenes.push_back({ "Test Kevin", std::make_unique<TestSceneKevin>() });
        m_AllScenes.push_back({ "Test Logan", std::make_unique<TestSceneLogan>() });
        m_AllScenes.push_back({ "Empty", std::make_unique<EmptyScene>() });
    }

    void SceneManager::SetScene(int sceneIndex)
    {
        const auto& scenes = s_Instance->m_AllScenes;

        if (sceneIndex < 0 || sceneIndex >= scenes.size())
        {
            LEI_ERROR("Tried to load scene with out of bounds index.");
            return;
        }

        Scene* nextScene = scenes[sceneIndex].second.get();
        s_Instance->SetNextScene(*nextScene);
    }

    void SceneManager::SetScene(std::string sceneName)
    {
        //This is a structured binding. It allows us to unpack the scene name and object from an std::pair implicitly.
	    for (const auto& [ currName, currScene] : s_Instance->m_AllScenes)
	    {
		    if (sceneName == currName)
		    {
                s_Instance->SetNextScene(*currScene);
                return;
		    }
	    }

        LEI_ERROR("DID NOT FIND SCENE: {0}", sceneName);
    }

    std::vector<std::string> SceneManager::GetSceneNames()
    {
        std::vector<std::string> names;
        for (const auto& [name, scene] : s_Instance->m_AllScenes)
        {
            names.push_back(name);
        }

        return names;
    }

    void SceneManager::SetNextScene(Scene& scene)
    {
        m_NextScene = &scene;
        m_NeedsSceneSwitch = true;
    }

    Scene& SceneManager::ActiveScene()
    {
        LEI_ASSERT(m_ActiveScene, "Attempt to access active scene when there wasn't one.");
        return *(s_Instance->m_ActiveScene);
    }

    void SceneManager::LoadNextScene()
    {
        if (m_NextScene == nullptr)
        {
            LEI_ERROR("Cannot load next scene because a scene was not set.");
            return;
        }

        m_ActiveScene = m_NextScene;
        LoadScene(*m_ActiveScene);
        m_NeedsSceneSwitch = false;
    }

    bool SceneManager::NeedsSceneSwitch() const {
        return m_NeedsSceneSwitch;
    }

    void SceneManager::LoadScene(Scene& scene)
    {
        if (m_ActiveScene != nullptr)
        {
            m_ActiveScene->Unload();
        }

        m_ActiveScene = &scene;
        m_ActiveScene->Load();
    }
}