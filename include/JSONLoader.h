//
// Created by Sp4rk on 03-10-17.
//

#ifndef CLIKEECS_JSONLOADER_H
#define CLIKEECS_JSONLOADER_H

#include "rapidjson/document.h"

class JSONLoader
{
public:
    ///< Read JSON to load entities
    rapidjson::Document read(const char *filePath, const char *mode = "rb");

    void close();

private:
    char *buffer_ = (char *) malloc(65536 * sizeof(char));

    FILE *file_ = nullptr;
};

#endif //CLIKEECS_JSONLOADER_H