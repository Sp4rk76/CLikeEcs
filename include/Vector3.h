//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_VECTOR3_H
#define CLIKEECS_VECTOR3_H

struct Vector3
{
    Vector3(float xi, float yi, float zi)
    {
        x = xi;
        y = yi;
        z = zi;
    }

    float x = 0;
    float y = 0;
    float z = 0;

    bool operator==(Vector3 const &other)
    {
        return ((x == other.x) && (y == other.y) && (z == other.z));
    }

    void operator*(float other)
    {
        if (other == 0)
        {
            x = 0;
            y = 0;
            z = 0;
        } else
        {
            x = x * other;
            y = y * other;
            z = z * other;
        }
    }

    void operator+=(int o)
    {
        x += o;
        y += o;
        z += o;
    }

    void operator+=(Vector3 const& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
};

#endif //CLIKEECS_VECTOR3_H
