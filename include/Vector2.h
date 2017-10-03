//
// Created by Sp4rk on 28-09-17.
//

#ifndef CLIKEECS_VECTOR2_H
#define CLIKEECS_VECTOR2_H


struct Vector2
{
    float x = 0;
    float y = 0;
    float z = 0;

    bool operator==(Vector2 const& other)
    {
        return ( (x == other.x) && (y == other.y) && (z == other.z) );
    }

    Vector2 operator*(float other)
    {
        x = x * other;
        y = y * other;
        z = z * other;
    }

    Vector2 operator+=(Vector2 const& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
};

#endif //CLIKEECS_VECTOR2_H
