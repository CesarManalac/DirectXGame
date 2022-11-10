#include "MainMenu.h"

MainMenu::MainMenu() : AUIScreen("MENU_SCREEN")
{
}

MainMenu::~MainMenu()
{
	AUIScreen::~AUIScreen();
}

void MainMenu::drawUI()
{
	ImGui::SetWindowSize(ImVec2(UIManager::WINDOW_WIDTH, UIManager::WINDOW_HEIGHT));
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("About")) {
			if (ImGui::MenuItem("Credits")) {
				CreditsScreen::isOpen = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Color Picker")) {
			if (ImGui::MenuItem("Color Wheel")) {
				Placeholder::isOpen = true;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
