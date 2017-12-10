//
// Created by Sp4rk on 12-10-17.
//

#ifndef CLIKEECS_PHYSICS2D_H
#define CLIKEECS_PHYSICS2D_H

#include "System.h"

class Physics2D : public System
{
public:
    explicit Physics2D(InstanceData *data);

    void simulate(float dt) override;

    void setLocal(size_t instance_id, const glm::mat4 &matrix);

    void transform(const glm::mat4 &parent, size_t instance_id);

    bool isValid(int instance_id);

    glm::mat4 matrix4x4Identity();

    ~Physics2D();

private:
    Vector3 *position = nullptr;
    Vector3 *velocity = nullptr;
    Vector3 *acceleration = nullptr;
};

#endif //CLIKEECS_PHYSICS2D_H
