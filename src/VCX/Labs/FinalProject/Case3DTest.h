#pragma once

#include "Engine/GL/Frame.hpp"
#include "Engine/GL/Program.h"
#include "Engine/GL/RenderItem.h"
#include "Labs/Common/OrbitCameraManager.h"
#include "Labs/Common/ICase.h"
#include "Labs/Common/ImageRGB.h"

namespace VCX::Labs::FinalProject 
{   
    struct objects 
    {
        void Reset()
        {
            positions.clear(); positions.push_back({ 0.f, 0.f, 0.f });
            velocities.clear(); velocities.push_back({ 0.001f, 0.001f, 0.f });
        }

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> velocities;
    };

    class Case3DTest : public Common::ICase 
    {
    public:
        Case3DTest();

        virtual std::string_view const GetName() override { return "Case 3D Test"; }

        virtual void OnSetupPropsUI() override;
        virtual Common::CaseRenderResult OnRender(std::pair<std::uint32_t, std::uint32_t> const desiredSize) override;
        virtual void OnProcessInput(ImVec2 const & pos) override;
    
    private:
        Engine::GL::UniqueProgram               _program;
        Engine::GL::UniqueRenderFrame           _frame;
        Engine::Camera                          _camera { .Eye = glm::vec3(-3, 3, 3) };
        Common::OrbitCameraManager              _cameraManager;
        Engine::GL::UniqueRenderItem            _particlesItem;
        float                                   _particleSize  { 2 };
        glm::vec3                               _particleColor { 1.f, 0.f, 0.f };
        bool                                    _stopped       { false };


        // self defined object 
        objects                                  objs;
    };
}