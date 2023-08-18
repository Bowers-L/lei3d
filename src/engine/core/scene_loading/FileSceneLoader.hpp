#pragma once

#include "SceneLoader.hpp"

#include <string>

namespace lei3d
{
    class FileSceneLoader : SceneLoader
    {
    private:
        std::string m_SceneFilePath;
        Scene* m_CurrScene = nullptr;
    public:
        FileSceneLoader(std::string sceneFilePath);
        void Load(Scene& scene) override;

    private:
        Entity* ParseEntityStart(std::ifstream& currFstream) const;
        void ParseEntityComponents(std::ifstream& fileStream, Entity& entity) const;
        void ParseSkyBox(std::ifstream& fileStream, Entity& entity) const;
    };
}