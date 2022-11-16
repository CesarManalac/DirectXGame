#include "UIManager.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
    sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < this->uiList.size(); i++) {
        this->uiList[i]->drawUI();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(windowHandle);
    ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->m_d3d_device, GraphicsEngine::get()->getRenderSystem()->m_imm_context);
    UINames uiNames;

    MainMenu* mainMenu = new MainMenu();
    this->uiTable[uiNames.MENU_SCREEN] = mainMenu;
    this->uiList.push_back(mainMenu);

    CreditsScreen* credits = new CreditsScreen();
    this->uiTable[uiNames.CREDITS_SCREEN] = credits;
    this->uiList.push_back(credits);
    
    Placeholder* placeHolder = new Placeholder();
    this->uiTable[uiNames.PLACEHOLDER_SCREEN] = placeHolder;
    this->uiList.push_back(placeHolder);
}

UIManager::~UIManager()
{
}
