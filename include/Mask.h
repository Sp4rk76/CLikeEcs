//
// Created by Sp4rk on 11-10-17.
//

#ifndef CLIKEECS_MASK_H
#define CLIKEECS_MASK_H

#include <map>
#include <string>
#include <iostream>

enum Mask : size_t
{
    None = 0,
    Transform = 1 << 0,
    Position = 1 << 1,
    Velocity = 1 << 2,
    Acceleration = 1 << 3,
    Sprite = 1 << 4,
};

typedef std::map<std::string, size_t> MaskMap;

class MaskMapper
{
public:
    MaskMapper()
    {
        masks_["none"] = None;
        masks_["transform"] = Transform;
        masks_["position"] = Position;
        masks_["velocity"] = Velocity;
        masks_["acceleration"] = Acceleration;

        // TODO: find an alternative between position & transform use cases
        masks_["physics2D"] = (Transform | Velocity | Acceleration);
        masks_["renderer2D"] = (Transform | Sprite);
    }

    size_t get(const std::string& maskString)
    {
        if (masks_.count(maskString) == 0) // not found
        {
            std::cout << "Error: mask string not found (mapping is impossible)" << std::endl;
            return None;
        }
        return masks_[maskString];
    }
private:
    MaskMap masks_;
};


#define DEFAULT 0

#endif //CLIKEECS_MASK_H
