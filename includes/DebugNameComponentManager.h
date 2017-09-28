//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_DEBUGNAMECOMPONENTMANAGER_H
#define CLIKEECS_DEBUGNAMECOMPONENTMANAGER_H

#include "Entity.h"

class DebugNameComponentManager
{
public:
    void set_debug_name(Entity e, const char *name);
    const char *debug_name(Entity e) const;
};

#endif //CLIKEECS_DEBUGNAMECOMPONENTMANAGER_H
