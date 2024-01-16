#pragma once

#include "Engine/Async.hpp"
#include "Labs/Common/ICase.h"
#include "Labs/Common/ImageRGB.h"

namespace VCX::Labs::FinalProject {
    class CaseTest : public Common::ICase {
    public:
        CaseTest();

        virtual std::string_view const GetName() override { return "Draw Fixed Images"; }

        virtual void OnSetupPropsUI() override;
        virtual Common::CaseRenderResult OnRender(std::pair<std::uint32_t, std::uint32_t> const desiredSize) override;
        virtual void OnProcessInput(ImVec2 const & pos) override;

    private:
     
        std::array<Engine::GL::UniqueTexture2D, 2> _textures;

        int _sizeId      = 0;
        bool _enableZoom = true;
    };
}