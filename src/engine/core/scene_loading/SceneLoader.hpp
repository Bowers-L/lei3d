#pragma once

#include "core/Scene.hpp"

namespace lei3d
{
    class Scene;

    //This is a loading interface called by the Scene class.
    class SceneLoader
    {
    public:
        virtual void Load(Scene& scene) = 0;
    };
	
}