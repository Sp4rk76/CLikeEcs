//
// Created by Sp4rk on 05-10-17.
//

#ifndef CLIKEECS_SYSTEM_H
#define CLIKEECS_SYSTEM_H

#include <iostream>
#include <map>
#include "InstanceData.h"

class System
{
public:
    const unsigned int SYSTEM_INDEX_BITS = 22;

    const int SYSTEM_INDEX_MASK = (1 << SYSTEM_INDEX_BITS) - 1;

    const unsigned int SYSTEM_GENERATION_BITS = 8;

    const int SYSTEM_GENERATION_MASK = (1 << SYSTEM_GENERATION_BITS) - 1;

    unsigned int set_id(size_t id) { id_ = id; }

    unsigned int id() const { return id_ & SYSTEM_INDEX_MASK; }

    unsigned int generation() const { return (id_ >> SYSTEM_INDEX_BITS) & SYSTEM_GENERATION_MASK; }

    void start();

    void stop();

    bool running();

    explicit System(InstanceData *data);

    ~System();

    // NOTE: this method is polymorphic
    // It can be redefined by children;
    virtual void simulate(float dt = 1) = 0;

    unsigned int requiredMask();

    std::set<size_t> entityMatches();

    unsigned int entityMatch(Entity *entity);

    unsigned int entityMatch(unsigned int matchingEntity);

    void setEntityMatch(std::size_t id);

    void unsetEntityMatch(std::size_t id);

    void setRequiredMask(std::size_t requiredMask);

    void setName(const std::string &name);

    std::string name() const;

    void clear();

    void free();

    void setData(InstanceData *instanceData);

    std::set<size_t> matches_;

    // Non-const: if need to remove one component verification ? for some game it can be problematic ? => need to refresh entity subscriptions.
    unsigned int requiredMask_;

    std::string name_;

    unsigned int id_ = INVALID_INDEX;

    bool running_;

    InstanceData *data_;


private:
};

#endif //CLIKEECS_SYSTEM_H
