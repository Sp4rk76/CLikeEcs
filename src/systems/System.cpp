//
// Created by Sp4rk on 05-10-17.
//

#include <malloc.h>
#include <iostream>
#include <systems/System.h>
#include <managers/Manager.h>

// TODO: check try/catch on data !
System::System(InstanceData *data)  // Test
{
    data_ = data;
    id_ = 0;
    name_ = "";
    requiredMask_ = DEFAULT;
    running_ = false;
    data_ = nullptr;
}

System::~System()
{
    delete data_;
    data_ = nullptr;
}

unsigned int System::requiredMask()
{
    return requiredMask_;
}

std::set<size_t> System::entityMatches()
{
    return matches_;
}

unsigned int System::entityMatch(Entity *entity)
{
    /// NOTE: O(n) temporal complexity
    return *matches_.find(entity->id);
}

unsigned int System::entityMatch(std::size_t id)
{
    return *matches_.find(id);
}

void System::setEntityMatch(std::size_t id)
{
    /// ??? < or <=
    if (id < DEFAULT)
    {
        std::cout << "Error: Trying to set (register) an invalid entity to a system (invalid id)" << std::endl;
        return;
    } else
    {
        /// NOTE: O(1) temporal complexity ?
        matches_.insert(id);
    }
}

void System::unsetEntityMatch(std::size_t id)
{
    matches_.erase(id);
}

void System::setRequiredMask(std::size_t requiredMask)
{
    requiredMask_ = requiredMask;
}

void System::clear()
{
    matches_.clear();
}

void System::free()
{
    clear();

    requiredMask_ = 0;
}

void System::setName(const std::string &name)
{
    name_ = name;
}

std::string System::name() const
{
    return name_;
}

void System::setData(InstanceData *instanceData)
{
    if (instanceData == nullptr)
    {
        std::cout << "Error: cannot assign null data as system data" << std::endl;
        return;
    }

    data_ = instanceData;
}

void System::start()
{
    running_ = true;
}

void System::stop()
{
    running_ = false;
    matches_.clear();
}

bool System::running()
{
    return running_;
}

bool System::has(size_t instance_id) const
{
    /// can be implemented in two ways:
    /// == instance_id
    /// or
    /// != matches_.size()
    return *matches_.find(instance_id) == instance_id;
}
