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
/* \file UUID.hpp
 * \brief UUID/Name pair storage
 * \author Nikolay Zamotaev
 */
#ifndef _UUID__HPP_
#define _UUID__HPP_

#include <string>
#include <fstream>
#include <map>
#include <json/json.h>

class UUIDStore {
    public:
        UUIDStore(std::string path = "./uuids.json");
        ~UUIDStore();
        bool add(std::string name, std::string uuid);
        bool clean();
        bool deleteUid(std::string uuid);
        bool findByName(std::string uuid);
        bool findByUuid(std::string uuid);
        std::string getByName(std::string name);
        std::string getByUuid(std::string uuid);
    private:
        void load();
        void save();
        static std::string const mNameField;
        static std::string const mUuidField;
        Json::Value *mRoot;
        std::string mPath;
};

#endif
