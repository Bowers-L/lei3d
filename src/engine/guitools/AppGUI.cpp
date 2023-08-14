#include "AppGUI.hpp"

namespace lei3d {
	void AppGUI::RenderUI() {

        if (m_ShowDemoWindow) 
        {
            ImGui::ShowDemoWindow();
        }

        bool* p_open;
        ImGuiWindowFlags window_flags = 0;

        //Comment/Uncomment these as needed
        p_open = NULL;
        //window_flags |= ImGuiWindowFlags_NoTitleBar;
        //window_flags |= ImGuiWindowFlags_NoScrollbar;
        window_flags |= ImGuiWindowFlags_MenuBar;
        //window_flags |= ImGuiWindowFlags_NoMove;
        //window_flags |= ImGuiWindowFlags_NoResize;
        //window_flags |= ImGuiWindowFlags_NoCollapse;
        //window_flags |= ImGuiWindowFlags_NoNav;
        //window_flags |= ImGuiWindowFlags_NoBackground;
        //window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        //window_flags |= ImGuiWindowFlags_UnsavedDocument;

        if (!ImGui::Begin("LEI 3D", p_open, window_flags))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        // Menu Bar
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Menu")) 
            {
                ImGui::MenuItem("Show Demo Window", NULL, &m_ShowDemoWindow);

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Text("PRESS TAB TO TOGGLE");

        if (ImGui::CollapsingHeader("Scene List")) 
        {
            static int selectedScene = 0;
            int sceneI = 0;
            for (std::string& name : SceneManager::GetSceneNames())
            {
                const int oldSelectedScene = selectedScene;
                if (ImGui::RadioButton(name.c_str(), &selectedScene, sceneI))
                {
                    if (selectedScene != oldSelectedScene)
                    {
                        SceneManager::SetScene(name);
                    }
                }
                sceneI++;
            }
        }

        Scene& scene = SceneManager::ActiveScene();
        if (ImGui::CollapsingHeader("Scene"))
        {
            scene.ImGUIRender();
        }

        if (ImGui::CollapsingHeader("Game Info"))
        {
            ImGui::Text("fps = %f", 1.0f / Application::DeltaTime());
        }

        ImGui::SetWindowSize(ImVec2(400, 400), ImGuiCond_Once);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::End();
	}


}