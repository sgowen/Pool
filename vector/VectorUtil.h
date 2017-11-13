//
//  VectorUtil.h
//  Vector
//
//  Created by Stephen Gowen on 11/2/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef NoctisGames_VectorUtil_h
#define NoctisGames_VectorUtil_h

#include <vector/Vector.h>

#include <string>
#include <assert.h>

namespace NoctisGames
{
    class VectorUtil
    {
    public:
        /// Finds an item by comparing each item's name.
        /// It is more efficient to cache the results of this method than to call it multiple times.
        /// @return May be NULL.
        template<typename T>
        static T* findWithName(Vector<T*>& items, std::string name)
        {
            assert(name.length() > 0);
            
            for (T** i = items.begin(); i != items.end(); ++i)
            {
                T* item = (*i);
                if (item->getName() == name)
                {
                    return item;
                }
            }
            
            return NULL;
        }
        
        /// @return -1 if the item was not found.
        template<typename T>
        static int findIndexWithName(Vector<T*>& items, std::string name)
        {
            assert(name.length() > 0);
            
            for (size_t i = 0, len = items.size(); i < len; ++i)
            {
                T* item = items[i];
                if (item->getName() == name)
                {
                    return static_cast<int>(i);
                }
            }
            
            return -1;
        }
        
        /// Finds an item by comparing each item's name.
        /// It is more efficient to cache the results of this method than to call it multiple times.
        /// @return May be NULL.
        template<typename T>
        static T* findWithDataName(Vector<T*>& items, std::string name)
        {
            assert(name.length() > 0);
            
            for (T** i = items.begin(); i != items.end(); ++i)
            {
                T* item = (*i);
                if (item->getData().getName() == name)
                {
                    return item;
                }
            }
            
            return NULL;
        }
        
        /// @return -1 if the item was not found.
        template<typename T>
        static int findIndexWithDataName(Vector<T*>& items, std::string name)
        {
            assert(name.length() > 0);
            
            for (size_t i = 0, len = items.size(); i < len; ++i)
            {
                T* item = items[i];
                if (item->getData().getName() == name)
                {
                    return static_cast<int>(i);
                }
            }
            
            return -1;
        }
        
        template<typename T>
        static void cleanUpVectorOfPointers(Vector<T*>& items)
        {
            for (size_t i = 0; i < items.size(); )
            {
                T* item = items[i];
                delete item;
                
                items.erase(i);
            }
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        VectorUtil();
        VectorUtil(const VectorUtil&);
        VectorUtil& operator=(const VectorUtil&);
    };
}

#endif /* NoctisGames_VectorUtil_h */
