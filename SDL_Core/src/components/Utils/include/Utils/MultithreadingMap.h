/**
 *
 * SDLP SDK
 * Cross Platform Application Communication Stack for In-Vehicle Applications
 *
 * Copyright (C) 2013, Luxoft Professional Corp., member of IBS group
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

#ifndef MULTITHREADED_MAP_CLASS
#define MULTITHREADED_MAP_CLASS

#include <map>

template <typename T, typename K> class MultithreadingMap
{
public:
    MultithreadingMap();
    ~MultithreadingMap();

    int size() const;

    bool empty() const;

    void insert( const std::pair<const T,K> & element );

    K & find( const T & key );

private:
    std::multimap<T,K> mMap;

    /**
      *\brief Mutex for queue locking.
    */
    mutable pthread_mutex_t mMutex;    

};

template <typename T, typename K> MultithreadingMap<T,K>::MultithreadingMap() :
mMutex( PTHREAD_MUTEX_INITIALIZER )
{
    pthread_mutex_init( &mMutex, NULL );
}

template <typename T, typename K> MultithreadingMap<T,K>::~MultithreadingMap()
{
    pthread_mutex_destroy( &mMutex );
}



#endif // MULTITHREADED_MAP_CLASS
