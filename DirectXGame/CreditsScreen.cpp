#include "CreditsScreen.h"
#include "UIManager.h"
#include "GraphicsEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "ImGui\stb_image.h"

bool CreditsScreen::isOpen = false;

CreditsScreen::CreditsScreen() : AUIScreen ("CREDITS_SCREEN")
{
    my_image_width = 0;
    my_image_height = 0;
    my_texture = NULL;
    bool ret = LoadTextureFromFile("Logo.png", &my_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);
}

CreditsScreen::~CreditsScreen()
{
}

bool CreditsScreen::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    GraphicsEngine::get()->getDevice()->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    GraphicsEngine::get()->getDevice()->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

void CreditsScreen::drawUI()
{
    //ImGui::SetWindowSize(ImVec2(UIManager::WINDOW_WIDTH, UIManager::WINDOW_HEIGHT));
    if (isOpen) {
        if (ImGui::Begin("Credits", &isOpen, ImGuiWindowFlags_AlwaysAutoResize)) {
            const ImVec2 image_size = ImVec2(my_image_width / 4, my_image_height / 4);
            ImGui::Image((void*)my_texture, image_size);
            ImGui::Text("About:");
            ImGui::Text("Scene Editor V.1.0");
            ImGui::Text("Developer: Cesar Dominic Manalac");
            ImGui::Spacing();
            ImGui::Text("Acknowledgements:");
            ImGui::Spacing();
            ImGui::Text("Sir Neil Patrick Del Gallego");
            ImGui::Text("PardCode\n(https://www.youtube.com/playlist?list=PLv8DnRaQOs5-ST_VDqgbbMRtzMtpK36Hy)");
            ImGui::Text("IMGUI (https://github.com/ocornut/imgui)");
        }
        //ImGui::Begin("Credits");
        ImGui::End();
    }

}
