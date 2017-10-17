//
// Created by Sp4rk on 16-10-17.
//

#ifndef CLIKEECS_RENDERER2D_H
#define CLIKEECS_RENDERER2D_H

#include "System.h"

class Renderer2D : public System
{
public:
    explicit Renderer2D(InstanceData *data);

    void simulate(float dt) override;

private:
//    Transform* position = nullptr;
    Vector3* position = nullptr;
    Sprite2D* sprite_ = nullptr;
};

#endif //CLIKEECS_RENDERER2D_H
