//
// Created by Sp4rk on 11-10-17.
//

#ifndef CLIKEECS_MASK_H
#define CLIKEECS_MASK_H

#define DEFAULT 0

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
    Total = 1 << 5
};

#endif //CLIKEECS_MASK_H
