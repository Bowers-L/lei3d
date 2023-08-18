#include "FileSceneLoader.hpp"

#include "logging/Log.hpp"
#include "logging/LogGLM.hpp"

#include "components/SkyBox.hpp"

#include <fstream>

#include "util/StringUtil.hpp"


namespace lei3d
{
    FileSceneLoader::FileSceneLoader(std::string sceneFilePath)
        : m_SceneFilePath(sceneFilePath)
    {
    }

    void FileSceneLoader::Load(Scene& scene)
    {
        m_CurrScene = &scene;
        LEI_INFO("LOADING SCENE FROM FILE!");
        LEI_INFO("Opening Scene: {0}", m_SceneFilePath);
        std::ifstream fileStream(m_SceneFilePath, std::ifstream::in);

        std::string line;

        Entity* currEntity = nullptr;
        while (fileStream.good() && std::getline(fileStream, line))
        {
            LEI_INFO(line);
            if (line.find("StartEntity") != std::string::npos)
            {
                Entity* entity = ParseEntityStart(fileStream);

                if (entity == nullptr)
                {
                    LEI_ERROR("Error with StartEntity. Entity could not be created");
                    continue;
                }

                ParseEntityComponents(fileStream, *entity);
 
            }
        }

        scene.PrintEntityList();
    }

    Entity* FileSceneLoader::ParseEntityStart(std::ifstream& fileStream) const
    {
        LEI_INFO("PARSING ENTITY");
        std::string entityName = "";
        glm::vec3 pos(0, 0, 0);
        glm::vec3 scale(0, 0, 0);

        std::string line;
        int numBrackets = 0; //Doing a leetcode prob. in the middle of this parser lmao.
        while (fileStream.good() && std::getline(fileStream, line))
        {
            LEI_INFO(line);
            if (line.find('{') != std::string::npos)
            {
                numBrackets++;
            }

            auto tokens = tokenize(line);
            for (auto token : tokens)
			{
			    LEI_INFO(token);
			}
            if (tokens[0].compare("name") == 0)
            {
                if (tokens.size() != 2)
                {
                    LEI_ERROR("Wrong number of arguments. Usage: name <name>");
                    LEI_ERROR("On Line: {0}", line);
                }
                entityName = tokens[1];
            } else if (tokens[0].compare("position") == 0)
            {
                if (tokens.size() != 4)
                {
                    LEI_ERROR("Wrong number of arguments. Usage: position <x> <y> <z>");
                    LEI_ERROR("On Line: {0}", line);
                }
                pos.x = std::stof(tokens[1]);
                pos.y = std::stof(tokens[2]);
                pos.z = std::stof(tokens[3]);
            } else if (tokens[0].compare("scale") == 0)
            {
                if (tokens.size() != 4)
                {
                    LEI_ERROR("Wrong number of arguments. Usage: scale <x> <y> <z>");
                    LEI_ERROR("On Line: {0}", line);
                }
                scale.x = std::stof(tokens[1]);
                scale.y = std::stof(tokens[2]);
            	scale.z = std::stof(tokens[3]);
            }

            if (line.find('}') != std::string::npos)
            {
                if (numBrackets == 0)
                {
                    LEI_INFO("ENTITY PARSING ENDED");
                    LEI_INFO("Adding entity {0}", entityName);
                    PrintVec3("Position", pos);
                    PrintVec3("Scale", scale);

                    Entity& entity = entityName.length() > 0 ?
                        m_CurrScene->AddEntity(entityName)
                        : m_CurrScene->AddEntity();

                    entity.SetPosition(pos);
                    entity.SetScale(scale);

                    return &entity;
                }

                numBrackets--;
            }
        }

        return nullptr;
    }

    void FileSceneLoader::ParseEntityComponents(std::ifstream& fileStream, Entity& entity) const
    {
        std::string line;
        while (fileStream.good() && std::getline(fileStream, line))
        {
            if (line.find("SkyBox") != std::string::npos)
            {
                ParseSkyBox(fileStream, entity);
            }
            if (line.find("EndEntity") != std::string::npos)
            {
                return; //We're done adding components and can return to the top level
            }
        }
    }

    void FileSceneLoader::ParseSkyBox(std::ifstream& fileStream, Entity& entity) const
    {
        LEI_INFO("STARTING SKYBOX PARSE");
        std::vector<std::string> faces;

        std::string line;
        while (fileStream.good() && std::getline(fileStream, line))
        {
            if (line.find("faces") != std::string::npos)
            {
                faces = streamArrayParse(fileStream, line);
            }
            if (line.find('}') != std::string::npos)
            {
                LEI_INFO("CREATING SKYBOX");
                SkyBox* skybox = entity.AddComponent<SkyBox>();
                skybox->Init(faces);
            }
        }
    }
}