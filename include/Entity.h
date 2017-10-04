//
// Created by Sp4rk on 25-09-17.
//

#ifndef CLIKEECS_ENTITY_H
#define CLIKEECS_ENTITY_H

enum Mask
{
    None = 0,
    Base = 1 << 0,
    Physics2D = 1 << 1,
};


const unsigned int ENTITY_INDEX_BITS = 22;
const unsigned int ENTITY_INDEX_MASK = (1<<ENTITY_INDEX_BITS)-1;

const unsigned int ENTITY_GENERATION_BITS = 8;
const unsigned int ENTITY_GENERATION_MASK = (1 << ENTITY_GENERATION_BITS)-1;

// ( (EntityMask == SystemMask) + SystemId)
// On a alors:
// (1) + SystemId
// Remarque: l'ID commence à 1

struct Entity
{
    unsigned int id = 0;
    unsigned int mask = None;

    unsigned int index() const { return id & ENTITY_INDEX_MASK; }
    unsigned int generation() const { return (id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }
};

#endif //CLIKEECS_ENTITY_H
