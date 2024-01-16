#include "Labs/FinalProject/CaseTest.h"
#include "Labs/Common/ImGuiHelper.h"

namespace VCX::Labs::FinalProject 
{
    static constexpr auto c_Sizes = std::to_array<std::pair<std::uint32_t, std::uint32_t>>({
        { 320U, 320U },
        { 640U, 640U },
    });

    CaseTest::CaseTest(){}

    void CaseTest::OnSetupPropsUI() 
    {
        ImGui::Checkbox("Zoom Tooltip", &_enableZoom);
    }

    Common::CaseRenderResult CaseTest::OnRender(std::pair<std::uint32_t, std::uint32_t> const desiredSize)
    {
        Common::ImageRGB image = Common::CreateCheckboardImageRGB(400, 400);

        _textures[0].Update(image);

        return Common::CaseRenderResult {
            .Fixed     = true,
            .Image     = _textures[0],
            .ImageSize = { 400, 400 },
        };
    }

    void CaseTest::OnProcessInput(ImVec2 const & pos)
    {
        auto window = ImGui::GetCurrentWindow();
        bool hovered = false;
        bool anyHeld = false;
        ImVec2 const delta = ImGui::GetIO().MouseDelta;
        // 获取交互信息
        ImGui::ButtonBehavior(window->Rect(), window->GetID("##io"), &hovered, &anyHeld);
        if (! hovered) return;
        // 调整窗⼝⼤⼩
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && delta.x != 0.f)
            ImGui::SetScrollX(window, window->Scroll.x - delta.x);
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && delta.y != 0.f)
            ImGui::SetScrollY(window, window->Scroll.y - delta.y);
        // 决定是否调⽤放⼤镜功能
        if (_enableZoom && ! anyHeld && ImGui::IsItemHovered())
            Common::ImGuiHelper::ZoomTooltip(_textures[_sizeId], c_Sizes[_sizeId], pos);
    }
}