//
// Created by Sp4rk on 06-10-17.
//

#ifndef CLIKEECS_ENTITYMATCHER_H
#define CLIKEECS_ENTITYMATCHER_H

#include <set>

struct EntityMatcher
{
    std::set<std::size_t> matchId;
    unsigned int* matches;
};

#endif //CLIKEECS_ENTITYMATCHER_H
