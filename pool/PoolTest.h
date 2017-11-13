//
//  PoolTest.h
//  TestHarness
//
//  Created by Stephen Gowen on 11/12/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef NoctisGames_PoolTest_h
#define NoctisGames_PoolTest_h

#include <pool/Pool.h>
#include <vector/Vector.h>

#include <iostream>

namespace NoctisGames
{
    class MyClass
    {
    public:
        float _x, _y, _z;
    };
    
    class SomethingThatHasAPool
    {
    public:
        Pool< Vector<std::string> > _poolOfVectorStrings;
        Pool<MyClass> _poolOfClass;
    };
    
    class PoolTest
    {
    public:
        static void test()
        {
            SomethingThatHasAPool obj;
            
            using namespace std;
            
            cout << "Testing _poolOfClass" << endl;
            
            MyClass* mc1 = obj._poolOfClass.obtain();
            mc1->_x = 5;
            mc1->_y = 6;
            mc1->_z = 7;
            
            MyClass* mc2 = obj._poolOfClass.obtain();
            mc2->_x = 6;
            mc2->_y = 7;
            mc2->_z = 8;
            
            cout << "Freeing mc1" << endl;
            
            obj._poolOfClass.free(mc1);
            
            // I shouldn't be able to free it again
            obj._poolOfClass.free(mc1);
            
            MyClass* mc3 = obj._poolOfClass.obtain();
            mc3->_x += 10;
            mc3->_y += 10;
            mc3->_z += 10;
            
            assert(mc3->_x == 15);
            
            cout << "mc3->_x == 15, sweet, that means mc3 == mc1" << endl;
            
            cout << "Okay, what about a pool of vectors?" << endl;
            
            // I expect to allocate a new Vector here
            Vector<string>* vec1P = obj._poolOfVectorStrings.obtain();
            Vector<string>& vec1 = *vec1P;
            vec1.push_back("This is a test");
            vec1.push_back("This is a test as well");
            vec1.push_back("This is a test too");
            
            // I expect to allocate a new Vector here as well
            Vector<string>* vec2P = obj._poolOfVectorStrings.obtain();
            Vector<string>& vec2 = *vec2P;
            vec2.push_back("This is a test2");
            vec2.push_back("This is a test2 as well");
            vec2.push_back("This is a test2 too");
            
            cout << "Freeing vec1" << endl;
            
            // Okay, sure had a lot of fun using that vector, time to throw it away
            obj._poolOfVectorStrings.free(&vec1);
            
            // I shouldn't be able to free it again
            obj._poolOfVectorStrings.free(&vec1);
            
            // We should get back vec1 here, which already has 3 strings in it
            Vector<string>* vec3P = obj._poolOfVectorStrings.obtain();
            Vector<string>& vec3 = *vec3P;
            
            assert(vec3.size() == 3);
            
            cout << "vec3.size() == 3, which means that vec3 == vec1" << endl;
            
            vec3.clear();
            
            assert(vec3.size() == 0);
            
            vec3.push_back("This is a test3");
            vec3.push_back("This is a test3 as well");
            vec3.push_back("This is a test3 too");
            
            obj._poolOfVectorStrings.free(vec2P);
            obj._poolOfVectorStrings.free(vec3P);
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        PoolTest();
        PoolTest(const PoolTest&);
        PoolTest& operator=(const PoolTest&);
    };
}

#endif /* NoctisGames_PoolTest_h */
