//
// Created by Sp4rk on 03-10-17.
//

#include "DebugNameComponentManager.h"

void DebugNameComponentManager::set_debug_name(Entity entity, const char *name)
{
    names_[entity.id] = const_cast<char *>(name);
}

const char *DebugNameComponentManager::debug_name(Entity entity) const
{
    return names_[entity.id];
}

DebugNameComponentManager::DebugNameComponentManager()
{
    names_ = (char **) malloc(MAX_NAME_CHARS * sizeof(char *));
}

char **DebugNameComponentManager::names()
{
    // TODO: check if null or empty
    return names_;
}