#pragma once
#include "AUIScreen.h"

class Placeholder:public AUIScreen
{
public:

	Placeholder();
	~Placeholder();

	// Inherited via AUIScreen
	virtual void drawUI() override;

	static bool isOpen;
};

