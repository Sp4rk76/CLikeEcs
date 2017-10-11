//
// Created by Sp4rk on 11-10-17.
//

#ifndef CLIKEECS_MASK_H
#define CLIKEECS_MASK_H

enum Mask
{
    None = 0,
    Transform = 1 << 0,
    Position = 1 << 1,
    Velocity = 1 << 2,
    Acceleration = 1 << 3,
};

#define DEFAULT_POSITION 0
#define DEFAULT_VELOCITY 0
#define DEFAULT_ACCELERATION 0

#endif //CLIKEECS_MASK_H
