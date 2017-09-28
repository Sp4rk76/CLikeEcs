//
// Created by Sp4rk on 25-09-17.
//

#ifndef CLIKEECS_ENTITY_H
#define CLIKEECS_ENTITY_H

const unsigned ENTITY_INDEX_BITS = 22;
const unsigned ENTITY_INDEX_MASK = (1<<ENTITY_INDEX_BITS)-1;

const unsigned ENTITY_GENERATION_BITS = 8;
const unsigned ENTITY_GENERATION_MASK = (1 << ENTITY_GENERATION_BITS)-1;

struct Entity
{
    unsigned id;

    unsigned index() const { return id & ENTITY_INDEX_MASK; }
    unsigned generation() const { return (id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }
};

#endif //CLIKEECS_ENTITY_H
