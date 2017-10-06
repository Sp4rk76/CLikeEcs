//
// Created by Sp4rk on 03-10-17.
//

#include "JSONLoader.h"

#include <iostream>
#include <cstdio>

#include "rapidjson/fwd.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"

rapidjson::Document JSONLoader::read(const char *filePath, const char *mode)
{
    // 1. Open file for read
    file_ = fopen(filePath, mode);

    // 2. Read Stream
    rapidjson::FileReadStream fileReadStream(file_, buffer_, sizeof(buffer_));

    // 3. Parse in Document
    rapidjson::Document document;
    document.ParseStream(fileReadStream);

    return document;
}

void JSONLoader::close()
{
    if (file_ == nullptr)
    {
        std::cout << "Error: File already closed or never opened" << std::endl;
        return;
    }

    fclose(file_);
}

void JSONLoader::free()
{
    if(file_ != nullptr)
    {
        delete file_;
        file_ = nullptr;
    }

    std::free(buffer_);
}
