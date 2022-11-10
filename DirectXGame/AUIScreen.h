#pragma once
#include <iostream>
#include <vector>
#include "ImGui/imgui.h"


class UIManager;
using namespace std;

class AUIScreen
{
protected:

	AUIScreen(string name);
	~AUIScreen();

	string getName();

	virtual void drawUI() = 0;
	string name;

	friend class UIManager;
};

