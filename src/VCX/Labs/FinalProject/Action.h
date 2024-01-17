#pragma once

#include <vector>

namespace VCX::Labs::FinalProject 
{
    using Actions = std::vector<float>;

    struct Action
    {    
        Action();

        std::vector<std::vector<float>>     FrameParams;
        std::uint32_t                       TimeIndex = 0;
        std::uint32_t                       Frames;
        float                               FrameTime;
    };
}