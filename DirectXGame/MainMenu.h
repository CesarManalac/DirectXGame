#pragma once
#include "AUIScreen.h"
#include "UIManager.h"
#include "CreditsScreen.h"

class MainMenu:public AUIScreen
{
public:
	MainMenu();
	~MainMenu();
	// Inherited via AUIScreen
	virtual void drawUI() override;
};

