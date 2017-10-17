//
// Created by Sp4rk on 18-10-17.
//

#ifndef CLIKEECS_MASKMAPPER_H
#define CLIKEECS_MASKMAPPER_H

#include <map>
#include <iostream>
#include "Mask.h"

class MaskMapper
{
public:
    typedef std::map<std::string, size_t> MaskMap;
    typedef std::map<size_t, std::string> ReverseMaskMap;

    class MaskMapper
    {
    public:
        MaskMapper();

        void loadMaps();

        size_t get(const std::string &maskString);

        std::string getReverse(size_t maskValue);

    private:
        MaskMap masks_;
        ReverseMaskMap reverseMasks_;
    };
};

#endif //CLIKEECS_MASKMAPPER_H
