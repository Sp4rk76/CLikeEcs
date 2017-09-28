//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_VECTOR3_H
#define CLIKEECS_VECTOR3_H

struct Vector3
{
    float x = 0;
    float y = 0;
    float z = 0;

    bool operator==(Vector3 const& other)
    {
        return ( (x == other.x) && (y == other.y) && (z == other.z) );
    }

    Vector3 operator*(float other)
    {
        x = x * other;
        y = y * other;
        z = z * other;
    }

    Vector3 operator+=(Vector3 const& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
};

#endif //CLIKEECS_VECTOR3_H
