//
// Created by Sp4rk on 03-10-17.
//

#include "managers/JSONHandler.h"
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
    writer.Key("entities");
    writer.StartArray();

    for (size_t id = 0; id < data.n; ++id)
    {
        // TODO: if object is "alive" or smthg like this, then perform save, otherwise not.
        size_t e_id = data.entity[id].id;
        size_t e_mask = data.entity[id].mask;

        writer.StartObject();

        writer.Key("id");
        writer.Uint(e_id);
//      writer.Key("name");
//      writer.String((data.entity[id].name).c_str());
        writer.Key("mask");
        writer.Uint(e_mask);
        writer.Key("mass");
        writer.Double(data.mass[id]);

        // Position
        if (match(e_mask, Position))
        {
            writer.Key("position");
            writer.StartObject();
            writer.Key("x");
            writer.Double(data.position[id].x);
            writer.Key("y");
            writer.Double(data.position[id].y);
            writer.Key("z");
            writer.Double(data.position[id].z);
            writer.EndObject();
        }

        // Velocity
        if (match(e_mask, Velocity))
        {
            writer.Key("velocity");
            writer.StartObject();
            writer.Key("x");
            writer.Double(data.velocity[id].x);
            writer.Key("y");
            writer.Double(data.velocity[id].y);
            writer.Key("z");
            writer.Double(data.velocity[id].z);
            writer.EndObject();
        }

        // Acceleration
        if (match(e_mask, Acceleration))
        {
            writer.Key("acceleration");
            writer.StartObject();
            writer.Key("x");
            writer.Double(data.acceleration[id].x);
            writer.Key("y");
            writer.Double(data.acceleration[id].y);
            writer.Key("z");
            writer.Double(data.acceleration[id].z);
            writer.EndObject();
        }

        writer.EndObject();
    }

    writer.EndArray();
    writer.EndObject();

    write(filePath, mode, stringBuffer.GetString());
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
    for (auto &id : sys.reg_systems)
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
//        writer.StartArray();
//        size_t sys_mask = s->requiredMask();
//        size_t base_mask = 1;
//        while(sys_mask > 0 && base_mask < Total)
//        {
//            if((base_mask & sys_mask) == sys_mask)
//            {
//                sys_mask -= base_mask;
//                writer.String((maskMapper.getReverse(base_mask)).c_str());
//        }
//            base_mask <<= 1;
//        }
//        writer.EndArray();

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

bool JSONHandler::match(const size_t entityMask, const size_t requiredMask)
{
    return ((entityMask & requiredMask) == requiredMask);
}

