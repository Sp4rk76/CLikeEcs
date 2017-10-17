//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_VECTOR3_H
#define CLIKEECS_VECTOR3_H

struct Vector3
{
public:
    Vector3();

    Vector3(float xi, float yi, float zi);

    bool operator==(Vector3 const &other);

    void operator*(float other);

    void operator+=(int o);

    void operator+=(Vector3 const& other);

    float x = 0;
    float y = 0;
    float z = 0;
};

#endif //CLIKEECS_VECTOR3_H
