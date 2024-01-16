#include "Engine/app.h"
#include "Labs/FinalProject/Case3DTest.h"
#include "Labs/Common/ImGuiHelper.h"

namespace VCX::Labs::FinalProject 
{
    void StartSimulate(objects & objs)
    {
        for (int i = 0; i < objs.positions.size(); ++i)
        {
            objs.positions.at(i) += objs.velocities.at(i);
        }
    }

    Case3DTest::Case3DTest() :
        _program(
            Engine::GL::UniqueProgram({
                Engine::GL::SharedShader("assets/shaders/flat.vert"),
                Engine::GL::SharedShader("assets/shaders/flat.frag")})),
        _particlesItem(Engine::GL::VertexLayout()
            .Add<glm::vec3>("position", Engine::GL::DrawFrequency::Stream, 0), Engine::GL::PrimitiveType::Points)
        {
            _cameraManager.AutoRotate = false;
            _cameraManager.Save(_camera);

            objs.Reset();
        }

        void Case3DTest::OnSetupPropsUI()
        {
            ImGui::Text("Hello bro, I'm testing of ImGui %d", 2024);
            if (ImGui::Button(_stopped ? "Start" : "Stop")) _stopped = !_stopped;
        }

        Common::CaseRenderResult Case3DTest::OnRender(std::pair<std::uint32_t, std::uint32_t> const desiredSize)
        {
            if (!_stopped) StartSimulate(objs);

            _particlesItem.UpdateVertexBuffer("position", Engine::make_span_bytes<glm::vec3>(objs.positions));

            _frame.Resize(desiredSize);

            _cameraManager.Update(_camera);

            _program.GetUniforms().SetByName("u_Projection", _camera.GetProjectionMatrix((float(desiredSize.first) / desiredSize.second)));
            _program.GetUniforms().SetByName("u_View"      , _camera.GetViewMatrix());

            gl_using(_frame);
            glPointSize(_particleSize);

            _program.GetUniforms().SetByName("u_Color", _particleColor);
            _particlesItem.Draw({ _program.Use() });

            return Common::CaseRenderResult{
                .Fixed      = false,
                .Flipped    = true,
                .Image      = _frame.GetColorAttachment(),
                .ImageSize  = desiredSize,
            };
        }

        void Case3DTest::OnProcessInput(ImVec2 const & pos)
        {
            _cameraManager.ProcessInput(_camera, pos);
        }
}

