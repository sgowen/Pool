//
//  Pool.h
//  TestHarness
//
//  Created by Stephen Gowen on 11/12/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef NoctisGames_Pool_h
#define NoctisGames_Pool_h

#include <vector/Vector.h>
#include <vector/VectorUtil.h>

namespace NoctisGames
{
    template <typename T>
    class Pool
    {
    public:
        Pool()
        {
            // Empty
        }
        
        ~Pool()
        {
            VectorUtil::cleanUpVectorOfPointers(_objects);
        }
        
        T* obtain()
        {
            if (_objects.size() > 0)
            {
                T** object = _objects.begin();
                T* ret = *object;
                _objects.erase(0);
                
                return ret;
            }
            else
            {
                return new T();
            }
        }
        
        void free(T* object)
        {
            if (!_objects.contains(object))
            {
                _objects.push_back(object);
            }
        }
        
    private:
        Vector<T*> _objects;
    };
}

#endif /* NoctisGames_Pool_h */
