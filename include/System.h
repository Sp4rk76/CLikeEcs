//
// Created by Sp4rk on 05-10-17.
//

#ifndef CLIKEECS_SYSTEM_H
#define CLIKEECS_SYSTEM_H

#include <vector>
#include <iostream>
#include "Entity.h"
#include "Instance.h"

const unsigned int SYSTEM_INDEX_BITS = 22;

const unsigned int SYSTEM_INDEX_MASK = (1 << SYSTEM_INDEX_BITS) - 1;

const unsigned int SYSTEM_GENERATION_BITS = 8;

const unsigned int SYSTEM_GENERATION_MASK = (1 << SYSTEM_GENERATION_BITS) - 1;

class System
{
public:
    unsigned int set_id(size_t id)
    { id_ = id; }

    unsigned int id() const
    { return id_ & ENTITY_INDEX_MASK; }

    unsigned int generation() const
    { return (id_ >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }

    void start()
    { running_ = true; }

    void stop()
    { running_ = false; }

    bool running()
    { return running_; }

    explicit System();

    void simulate(float dt = 1);

    unsigned int requiredMask();

    std::vector<std::size_t> entityMatches() const;

    unsigned int entityMatch(Entity *entity);

    unsigned int entityMatch(unsigned int matchingEntity);

    void setEntityMatch(std::size_t id);

    void unsetEntityMatch(std::size_t id);

    void setRequiredMask(std::size_t requiredMask);

    void setName(const std::string &name);

    std::string name() const;

    void clear();

    void free();

    std::vector<std::size_t> matches_;

    // Non-const: if need to remove one component verification ? for some game it can be problematic ? => need to refresh entity subscriptions.
    unsigned int requiredMask_;

    std::string name_;

    unsigned int id_ = INVALID_INDEX;

    bool running_ = false;


private:
};

#endif //CLIKEECS_SYSTEM_H
