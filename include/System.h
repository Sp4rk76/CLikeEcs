//
// Created by Sp4rk on 05-10-17.
//

#ifndef CLIKEECS_SYSTEM_H
#define CLIKEECS_SYSTEM_H

#include <vector>
#include "Entity.h"
#include "Instance.h"

class System
{
public:
    explicit System();

    void simulate(float dt = 1);

    unsigned int requiredMask();

    std::vector<std::size_t> entityMatches() const;

    unsigned int entityMatch(Entity *entity);

    unsigned int entityMatch(unsigned int matchingEntity);

    void setEntityMatch(std::size_t id);

    void unsetEntityMatch(std::size_t id);

    void setRequiredMask(std::size_t requiredMask);

    void setName(const char* name);

    const char* name();

    void clear();

    void free();

    std::vector<std::size_t> matches_;

    // Non-const: if need to remove one component verification ? for some game it can be problematic ? => need to refresh entity subscriptions.
    unsigned int requiredMask_;

    const char* name_;

private:
};

#endif //CLIKEECS_SYSTEM_H
