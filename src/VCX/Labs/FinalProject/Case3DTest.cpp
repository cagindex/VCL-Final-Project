#include "Engine/app.h"
#include "Labs/FinalProject/Case3DTest.h"
#include "Labs/Common/ImGuiHelper.h"

namespace VCX::Labs::FinalProject 
{
    /**
     * BackGround Section
    */
    BackGroundRender::BackGroundRender():
        LineItem(Engine::GL::VertexLayout().Add<glm::vec3>("position", Engine::GL::DrawFrequency::Stream, 0), Engine::GL::PrimitiveType::Lines)
    {
        std::vector<glm::vec3> poses;
        std::vector<std::uint32_t> indices;

        // Load poses
        int num = 600;
        float dis = 0.1f;
        for (int row = 1; row <= num; ++row)
        {
            for (int col = 1; col <= num; ++col)
            {
                poses.push_back({ dis*(row-num/2), 0.0f, dis*(col-num/2) });
            }
        }

        // Load indices
        for (int row = 0; row < num; ++row)
        {
            int startIdx = row*num;
            for (int col = 0; col < num-1; ++col)
            {
                indices.push_back(startIdx+col);
                indices.push_back(startIdx+col+1);
            }
        }
        for (int col = 0; col < num; ++col)
        {
            int startIdx = col;
            for (int row = 0; row < num-1; ++row)
            {
                indices.push_back(startIdx+row*num);
                indices.push_back(startIdx+(row+1)*num);
            }
        }

        // Update
        LineItem.UpdateVertexBuffer("position", Engine::make_span_bytes<glm::vec3>(poses));
        LineItem.UpdateElementBuffer(indices);
    };

    void BackGroundRender::render(Engine::GL::UniqueProgram & program)
    {
        program.GetUniforms().SetByName("u_Color", glm::vec3( 111.0f/255, 111.0f/255, 111.0f/255 ));
        LineItem.Draw({ program.Use() });
    }
    // BackGround End

    /**
     * SkeletonRender Section
    */
    SkeletonRender::SkeletonRender():
        LineItem(Engine::GL::VertexLayout().Add<glm::vec3>("position", Engine::GL::DrawFrequency::Stream, 0), Engine::GL::PrimitiveType::Lines),
        PointItem(Engine::GL::VertexLayout().Add<glm::vec3>("position", Engine::GL::DrawFrequency::Stream, 0), Engine::GL::PrimitiveType::Points)
    {}

    void SkeletonRender::render(Engine::GL::UniqueProgram & program)
    {
        program.GetUniforms().SetByName("u_Color", glm::vec3( 1.0f, 0.0f, 0.0f ));
        glPointSize(10.f);
        PointItem.Draw({ program.Use() });
        glPointSize(1.f);

        program.GetUniforms().SetByName("u_Color", glm::vec3( 1.0f, 1.0f, 1.0f ));
        glLineWidth(3.f);
        LineItem.Draw({ program.Use() });
        glLineWidth(1.f);
    }

    void SkeletonRender::load(const Skeleton & skele)
    {
        auto res = skele.Convert();
        LineItem.UpdateVertexBuffer("position", Engine::make_span_bytes<glm::vec3>(res.first));

        PointItem.UpdateVertexBuffer("position", Engine::make_span_bytes<glm::vec3>(res.first));
    }
    void SkeletonRender::loadAll(const Skeleton & skele)
    {
        auto res = skele.Convert();
        LineItem.UpdateElementBuffer(res.second);
        LineItem.UpdateVertexBuffer("position", Engine::make_span_bytes<glm::vec3>(res.first));

        PointItem.UpdateVertexBuffer("position", Engine::make_span_bytes<glm::vec3>(res.first));
    }
    // SkeletonRender End



    Case3DTest::Case3DTest() :
        _program(
            Engine::GL::UniqueProgram({
                Engine::GL::SharedShader("assets/shaders/flat.vert"),
                Engine::GL::SharedShader("assets/shaders/flat.frag")}))
        {
            _cameraManager.AutoRotate = false;
            _cameraManager.Save(_camera);

            _BVHLoader.Load(_filePath.c_str(), _skeleton, _action);

            skeletonRender.loadAll(_skeleton);
        }

        void Case3DTest::OnSetupPropsUI()
        {
            ImGui::Text("Hello bro, I'm testing of ImGui %d", 2024);
            if (ImGui::Button(_stopped ? "Start" : "Stop")) _stopped = !_stopped;
        }

        Common::CaseRenderResult Case3DTest::OnRender(std::pair<std::uint32_t, std::uint32_t> const desiredSize)
        {
            if (!_stopped)
            {
                _action.Load(_skeleton, Engine::GetDeltaTime());
            }

            skeletonRender.load(_skeleton);

            _frame.Resize(desiredSize);

            _cameraManager.Update(_camera);

            _program.GetUniforms().SetByName("u_Projection", _camera.GetProjectionMatrix((float(desiredSize.first) / desiredSize.second)));
            _program.GetUniforms().SetByName("u_View"      , _camera.GetViewMatrix());

            gl_using(_frame);

            BackGround.render(_program);
            skeletonRender.render(_program);

            glPointSize(1.f);
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

