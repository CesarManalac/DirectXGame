#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"

class UINames {
public:
	const string PROFILER_SCREEN = "PROFILER_SCREEN";
	const string MENU_SCREEN = "MENU_SCREEN";
	const string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const string CREDITS_SCREEN = "CREDITS_SCREEN";
	const string PLACEHOLDER_SCREEN = "PLACEHOLDER_SCREEN";
};