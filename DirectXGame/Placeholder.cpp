#include "Placeholder.h"

bool Placeholder::isOpen = false;

Placeholder::Placeholder() : AUIScreen("PLACEHOLDER_SCREEN")
{
}

Placeholder::~Placeholder()
{
}

void Placeholder::drawUI()
{
	if (isOpen) {
		if (ImGui::Begin("Color Picker", &isOpen, ImGuiWindowFlags_AlwaysAutoResize)) {
			float rgb[3] = { 1,1,1 };
			ImGui::ColorPicker3("Color", rgb, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
		}
		ImGui::End();
	}
}
