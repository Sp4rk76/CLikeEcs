//
// Created by Sp4rk on 13-11-17.
//

#ifndef CLIKEECS_MATRIX4X4_H
#define CLIKEECS_MATRIX4X4_H

struct Matrix4x4
{
    float right[4] = {1, 0, 0, 0};
    float up[4] = {0, 1, 0, 0};
    float forward[4] = {0, 0, 1, 0};
    float position[4] = {0, 0, 0, 1};

    float matrix[4][4] =
            {
                    {right[0],    right[1],    right[2],    right[3]},   // First column
                    {up[0],       up[1],       up[2],       up[3]},      // Second column
                    {forward[0],  forward[1],  forward[2],  forward[3]}, // Third column
                    {position[0], position[1], position[2], position[3]} // Fourth column
            };
};

#endif //CLIKEECS_MATRIX4X4_H
