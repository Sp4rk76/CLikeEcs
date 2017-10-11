//
// Created by Sp4rk on 11-10-17.
//

#ifndef CLIKEECS_SYSTEMMANAGER_H
#define CLIKEECS_SYSTEMMANAGER_H

#include <cstring>
#include <vector>
#include <deque>
#include "Mask.h"
#include "System.h"

class SystemManager
{
public:
    std::vector<char> generation_;
    std::deque<size_t> free_indices_;

    explicit SystemManager();

    System* create(size_t mask = None);

    System* make_system(size_t index, size_t mask);

    bool alive(System &system);

    bool running(System &system);

    void destroy(System &system);
};

#endif //CLIKEECS_SYSTEMMANAGER_H
