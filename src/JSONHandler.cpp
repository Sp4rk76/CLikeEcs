//
// Created by Sp4rk on 03-10-17.
//

#include "JSONHandler.h"
#include <cstdio>
#include <fstream>
#include "rapidjson/fwd.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <rapidjson/prettywriter.h>

rapidjson::Document JSONHandler::read(const char *filePath, const char *mode)
{
    char readBuffer[65536];

    // Open file for read
    file_ = fopen(filePath, mode);

    // Read Stream
    rapidjson::FileReadStream fileReadStream(file_, readBuffer, sizeof(readBuffer));

    // Parse
    rapidjson::Document document;
    document.ParseStream(fileReadStream);

    return document;
}

void JSONHandler::querySave(const InstanceData &data, const char *filePath, const char *mode)
{
    if (canWrite(filePath, mode))
    {
        save(data, filePath, mode);
    }
}

void JSONHandler::querySave(const InstanceSystem &sys, const char *filePath, const char *mode)
{
    if (canWrite(filePath, mode))
    {
        save(sys, filePath, mode);
    }
}

void JSONHandler::save(const InstanceData &data, const char *filePath, const char *mode)
{
    rapidjson::StringBuffer stringBuffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);

    /// Write SysData here !
    writer.StartObject();
    writer.Key("systems");
    writer.StartArray();


    writer.EndArray();
    writer.EndObject();

//    write(filePath, mode, stringBuffer.GetString());
}

void JSONHandler::save(const InstanceSystem &sys, const char *filePath, const char *mode)
{
    rapidjson::StringBuffer stringBuffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);

    /// Write SysData here !
    writer.StartObject();
    writer.Key("systems");
    writer.StartArray();

    // For each system
    for (auto &id : sys.id)
    {
        // TODO: check if system is null ?
        auto s = sys.systems[id];

        writer.StartObject();
        writer.Key("id");
        writer.Uint(id);
        writer.Key("name");
        writer.String((s->name()).c_str());
        writer.Key("requiredMask");
        writer.Uint(s->requiredMask());
        writer.EndObject();
    }

    writer.EndArray();
    writer.EndObject();

    write(filePath, mode, stringBuffer.GetString());
}

void JSONHandler::write(const char *filePath, const char *mode, const char *buffer)
{
    file_ = fopen(filePath, mode);

    if (file_ == nullptr)
    {
        std::cout << "Error: cannot open file" << std::endl;
        return;
    }

    fprintf(file_, buffer);
}

bool JSONHandler::canWrite(const char *filePath, const char *mode)
{
    if (isNullOrEmpty(filePath))
    {
        std::cout << "Error: file path not specified" << std::endl;
        return false;
    }

    if (isNullOrEmpty(mode))
    {
        std::cout << "Error: mode not specified" << std::endl;
        return false;
    }

    return true;
}

bool JSONHandler::isNullOrEmpty(const char *data)
{
    return ((data == nullptr) || (data[0] == '\0'));
}

void JSONHandler::close()
{
    if (file_ == nullptr)
    {
        std::cout << "Error: File already closed or never opened" << std::endl;
        return;
    }

    fclose(file_);
}

void JSONHandler::free()
{
    close();

    if (file_ != nullptr)
    {

        delete file_;
        file_ = nullptr;
    }
}

