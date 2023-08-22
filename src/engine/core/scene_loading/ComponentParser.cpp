#include "ComponentParser.hpp"

#include "components/CharacterController.hpp"
#include "components/ModelInstance.hpp"
#include "components/SkyBox.hpp"
#include "components/StaticCollider.hpp"

#include "util/StringUtil.hpp"

namespace lei3d
{
    void ParseCharacterController(std::ifstream& fileStream, Entity& entity) {
        //LEI_INFO("STARTING CHARACTER CONTROLLER PARSE");

        std::string line;
        while (fileStream.good() && std::getline(fileStream, line))
        {
            if (strContains(line, '}'))
            {
                LEI_INFO("CREATING CHARACTER CONTROLLER");
                auto cc = entity.AddComponent<CharacterController>();
                cc->Init();
                return;
            }
        }
    }

    void ParseModelInstance(std::ifstream& fileStream, Entity& entity) {
        
    }

    void ParseSkyBox(std::ifstream& fileStream, Entity& entity)
    {
        //LEI_INFO("STARTING SKYBOX PARSE");
        std::vector<std::string> faces;

        std::string line;
        while (fileStream.good() && std::getline(fileStream, line))
        {
            if (strContains(line, "faces"))
            {
                faces = streamArrayParse(fileStream, line);
            }
            if (strContains(line, '}'))
            {
                LEI_INFO("CREATING SKYBOX");
                auto skybox = entity.AddComponent<SkyBox>();
                skybox->Init(faces);
                return;
            }
        }
    }

    void ParseStaticCollider(std::ifstream& fileStream, Entity& entity) {
        
    }

    std::unordered_map<std::string, void (*) (std::ifstream&, Entity&)> componentParsers = {
        {"CharacterController", ParseCharacterController},
        {"ModelInstance", ParseModelInstance},
		{"SkyBox", ParseSkyBox},
        {"StaticCollider", ParseStaticCollider},
    };
}
