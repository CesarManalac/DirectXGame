#pragma once
#include <iostream>
#include <vector>
#include "AUIScreen.h"
#include <unordered_map>
#include "Window.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "GraphicsEngine.h"
#include "UINames.h"
#include "CreditsScreen.h"
#include "MainMenu.h"
#include "Placeholder.h"

using namespace std;

class UIManager
{
public:
	typedef vector<AUIScreen*> UIList;
	typedef unordered_map<string, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};

