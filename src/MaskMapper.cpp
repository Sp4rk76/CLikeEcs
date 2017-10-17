//
// Created by Sp4rk on 18-10-17.
//

#include "MaskMapper.h"

MaskMapper::MaskMapper::MaskMapper()
{
    loadMaps();
}

void MaskMapper::MaskMapper::loadMaps()
{
    masks_["none"] = None;
    masks_["transform"] = Transform;
    masks_["position"] = Position;
    masks_["velocity"] = Velocity;
    masks_["acceleration"] = Acceleration;
    // TODO: find an alternative between position & transform use cases
    masks_["physics2D"] = (Position | Velocity | Acceleration);
    masks_["renderer2D"] = (Position | Sprite);

    reverseMasks_[None] = "none";
    reverseMasks_[Transform] = "transform";
    reverseMasks_[Position] = "position";
    reverseMasks_[Velocity] = "velocity";
    reverseMasks_[Acceleration] = "acceleration";
    reverseMasks_[(Position | Velocity | Acceleration)] = "physics2D";
    reverseMasks_[(Position | Sprite)] = "renderer2D";
}

size_t MaskMapper::MaskMapper::get(const std::string &maskString)
{
    if (masks_.count(maskString) == 0) // not found
    {
        std::cout << "Error: mask string not found (mapping is impossible)" << std::endl;
        return None;
    }
    return masks_[maskString];
}

std::string MaskMapper::MaskMapper::getReverse(size_t maskValue)
{
    if (reverseMasks_.count(maskValue) == 0) // not found
    {
        std::cout << "Error: mask value not found (mapping is impossible)" << std::endl;
        return "None";
    }
    return reverseMasks_[maskValue];
}