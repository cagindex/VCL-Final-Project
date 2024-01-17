#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>

namespace VCX::Labs::FinalProject 
{
    struct Joint
    {
        Joint();

        Joint *BroPtr = nullptr, *ChiPtr = nullptr;

        int             PositionIdx[3] = { 0, 1, 2 };
        int             RotationIdx[3] = { 2, 0, 1 };
        std::string     Name;
        glm::vec3       Offset         = { 0.f, 0.f, 0.f };
        glm::vec3       Position       = { 0.f, 0.f, 0.f };
        glm::quat       Rotation;
    };

    struct Skeleton
    {
        Skeleton();

        Joint *Root;
    };
}