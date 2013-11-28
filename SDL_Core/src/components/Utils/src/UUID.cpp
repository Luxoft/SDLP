/*
 *
 * SDLP SDK
 * Cross Platform Application Communication Stack for In-Vehicle Applications
 *
 * Copyright (C) 2012, Luxoft Professional Corp., member of IBS group
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; version 2.1.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 *
 */
/* \file UUID.cpp
 * \brief UUID/Name pair storage
 * \author Nikolay Zamotaev
 */
#include "Utils/UUID.hpp"

std::string const UUIDStore::mNameField = "name";
std::string const UUIDStore::mUuidField = "uuid";
       
UUIDStore::UUIDStore(std::string path)
{
    std::fstream mUUidFile;
    mPath = path;
    mRoot = new Json::Value(Json::arrayValue);
    mUUidFile.open(mPath.c_str());
    if (!mUUidFile)
    {
        save();
    }
    mUUidFile.close();
    load();
}

UUIDStore::~UUIDStore()
{
    save();
    delete mRoot;
}

bool UUIDStore::add(std::string name, std::string uuid)
{
    int i;
    Json::Value value;
    value[mUuidField] = uuid;
    value[mNameField] = name;
    if (!mRoot->isArray())
    {
        *mRoot = Json::Value(Json::arrayValue);
    }
    if (findByUuid(uuid))
    {
        for (i = 0; i < mRoot->size(); i++ )
        {
            if ((*mRoot)[i][mUuidField] == uuid)
            {
                (*mRoot)[i][mNameField] = name;
                break;
            }
        }
    }
    else
    {
        mRoot->append(value);
    }
    save();
    return true;
}

bool UUIDStore::clean()
{
    Json::Value value(Json::arrayValue);
    *mRoot = value;
    save();
    return true;
}

bool UUIDStore::deleteUid(std::string uuid)
{
    int i;
    if (mRoot->empty())
    {
        return false;
    }
    if (!mRoot->isArray())
    {
        *mRoot = Json::Value(Json::arrayValue);
        return false;
    }
    Json::Value tempValue(Json::arrayValue);
    for (i = 0; i < mRoot->size(); i++ )
    {
        if ((*mRoot)[i][mUuidField] != uuid)
        {
            tempValue.append((*mRoot)[i]);
        }
    }
    *mRoot = tempValue;
    save();
    return true;
}

std::string UUIDStore::getByName(std::string name)
{
    int i;
    if (mRoot->empty())
    {
        return "";
    }
    if (!mRoot->isArray())
    {
        *mRoot = Json::Value(Json::arrayValue);
        return "";
    }
    for (i = 0; i < mRoot->size(); i++ )
    {
        if ((*mRoot)[i][mNameField] == name)
        {
            return (*mRoot)[i][mUuidField].asString();
        }
    }
    return "";
}

std::string UUIDStore::getByUuid(std::string uuid)
{
    int i;
    if (mRoot->empty())
    {
        return "";
    }
    if (!mRoot->isArray())
    {
        *mRoot = Json::Value(Json::arrayValue);
        return "";
    }
    for (i = 0; i < mRoot->size(); i++ )
    {
        if ((*mRoot)[i][mUuidField] == uuid)
        {
            return (*mRoot)[i][mNameField].asString();
        }
    }
    return "";
}
       
bool UUIDStore::findByName(std::string name)
{
    int i;
    if (mRoot->empty())
    {
        return false;
    }
    if (!mRoot->isArray())
    {
        *mRoot = Json::Value(Json::arrayValue);
        return false;
    }
    for (i = 0; i < mRoot->size(); i++ )
    {
        if ((*mRoot)[i][mNameField] == name)
        {
            return true;
        }
    }
    return false;
}

bool UUIDStore::findByUuid(std::string uuid)
{
    int i;
    if (mRoot->empty())
    {
        return false;
    }
    if (!mRoot->isArray())
    {
        *mRoot = Json::Value(Json::arrayValue);
        return false;
    }
    for (i = 0; i < mRoot->size(); i++ )
    {
        if ((*mRoot)[i][mUuidField] == uuid)
        {
            return true;
        }
    }
    return false;
}

void UUIDStore::load()
{
    Json::Reader mReader;
    std::ifstream file;
    file.open(mPath.c_str());
    mReader.parse(file, *mRoot);
    file.close();
}

void UUIDStore::save()
{
    std::ofstream file;
    file.open(mPath.c_str());
    file << mRoot->toStyledString();
    file.close();
}
