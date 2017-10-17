//
// Created by Sp4rk on 17-10-17.
//

#include "components/Vector3.h"

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float xi, float yi, float zi)
{
    x = xi;
    y = yi;
    z = zi;
}

bool Vector3::operator==(Vector3 const &other)
{
    return ((x == other.x) && (y == other.y) && (z == other.z));
}

void Vector3::operator*(float other)
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

void Vector3::operator+=(int o)
{
    x += o;
    y += o;
    z += o;
}

void Vector3::operator+=(Vector3 const &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}