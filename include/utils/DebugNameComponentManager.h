//
// Created by Sp4rk on 26-09-17.
//

#ifndef CLIKEECS_DEBUGNAMECOMPONENTMANAGER_H
#define CLIKEECS_DEBUGNAMECOMPONENTMANAGER_H

#include <malloc.h>
#include "entities/Entity.h"

class DebugNameComponentManager
{
public:

    DebugNameComponentManager();

    void set_debug_name(Entity entity, const char *name);

    const char *debug_name(Entity entity) const;

    char** names();

private:
    char** names_;

    short unsigned int MAX_NAME_CHARS = 32;
};

#endif //CLIKEECS_DEBUGNAMECOMPONENTMANAGER_H
