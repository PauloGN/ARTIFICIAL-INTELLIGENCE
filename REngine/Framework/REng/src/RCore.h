#pragma once

#include <iostream>
#include <raylib.h>
#include <string>
#include <imgui.h>
#include "RayLibImGui.h"

namespace REng
{
	inline void Start(const char* windowTitle)
	{
		InitWindow(1600, 900, windowTitle);
		rlImGuiSetup(true);
	}

	inline void Start(const char* windowTitle, int width, int height)
	{
		InitWindow(width, height, windowTitle);
		rlImGuiSetup(true);
	}

	inline void Run(bool (*gameLoop)(), void (*uiDebugUpdate)())
	{
        bool shouldCloseWindow = false;
        // Main game loop
        do
        {
            // Render
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(BLACK);
            shouldCloseWindow = gameLoop();
            //Update UI
            rlImGuiBegin();
            uiDebugUpdate();
            rlImGuiEnd();

            EndDrawing();
            //----------------------------------------------------------------------------------
        } while (!shouldCloseWindow);
	}

    inline void Run(bool (*gameLoop)())
    {
        bool shouldCloseWindow = false;
        // Main game loop
        do
        {
            // Render
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(BLACK);
            shouldCloseWindow = gameLoop();
            EndDrawing();
            //----------------------------------------------------------------------------------
        } while (!shouldCloseWindow);
    }
    
    inline void Stop()
    {
        rlImGuiShutdown();
        CloseWindowRaylib();
    }

    inline void ResourcesFullPath(const std::string& imageName, std::string& fullPath)
    {
        fullPath = "..\\Resources\\" + imageName;
    }
}
