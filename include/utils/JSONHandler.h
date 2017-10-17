//
// Created by Sp4rk on 03-10-17.
//

#ifndef CLIKEECS_JSONLOADER_H
#define CLIKEECS_JSONLOADER_H

#include "rapidjson/document.h"
#include "managers/InstanceSystem.h"
#include "managers/InstanceData.h"

class JSONHandler
{
public:
    ///< Read JSON to load entities
    rapidjson::Document read(const char *filePath, const char *mode = "rb");

    void querySave(const InstanceData &data, const char *filePath = "data/datwrite.json", const char *mode = "wb");

    void querySave(const InstanceSystem &sys, const char *filePath = "data/syswrite.json", const char *mode = "wb");

    void save(const InstanceData &data, const char *filePath, const char *mode);

    void save(const InstanceSystem &sys, const char *filePath, const char *mode);

    void write(const char *filePath, const char *mode, const char *buffer);

    bool canWrite(const char *filePath, const char *mode);

    bool match(size_t entityMask, size_t requiredMask);

    bool isNullOrEmpty(const char *data);

    void close();

    void free();

private:
    FILE *file_ = nullptr;
};

#endif //CLIKEECS_JSONLOADER_H