#pragma once
#include "AUIScreen.h"
#include <d3d11.h>

class CreditsScreen : public AUIScreen
{
public:
	// Inherited via AUIScreen
	virtual void drawUI() override;
	CreditsScreen();
	~CreditsScreen();
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	static bool isOpen;

private:
	int my_image_width;
	int my_image_height;
	ID3D11ShaderResourceView* my_texture;
};

