
// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2013
// Glenn P. Downing
// ------------------------------------


// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

using namespace std;

// -------------
// TestAllocator
// -------------

template <typename A>
struct TestAllocator : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A                  allocator_type;
    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;
};

typedef testing::Types<
            std::allocator<int>,
            std::allocator<double>,
            Allocator<int, 100>,
            Allocator<double, 100> 
	>
        my_types;

//char a_test[N];


TYPED_TEST_CASE(TestAllocator, my_types);

// downing test
/*
TYPED_TEST(TestAllocator, One) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 1;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);
    if (p != 0) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);
    }
}
*/

TYPED_TEST(TestAllocator, t) {

    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer pointer;

    allocator_type x;

    const difference_type s = 5;
    //cout << "s: " << s << endl;    
    const value_type v = 2;
    const pointer p = x.allocate(s);

    if (p != 0) {
	x.construct(p, v);
	ASSERT_EQ(v, *p);
    }
    const difference_type s2 = 4;
    const pointer p2 = x.allocate(s2);
/*
    const difference_type s3 = 1;
    const pointer p3 = x.allocate(s3);
    cout << "pointer test = " << p3 << endl;
*/
}

/*
TYPED_TEST(TestAllocator, Two) {

    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer pointer;

    allocator_type x;

    const difference_type s = 5;
    //cout << "s: " << s << endl;    
    const value_type v = 2;
    const pointer p = x.allocate(s);

    if (p != 0) {
	x.construct(p, v);
	ASSERT_EQ(v, *p);
	x.destroy(p);
	x.deallocate(p, s);
    }

}
*/

/*
TYPED_TEST(TestAllocator, three) {

    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 5;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);
    if (p != 0) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        //x.destroy(p);
        //x.deallocate(p, s);
    }   

    const difference_type s2 = 3;
    const value_type v2 = 3;
    const pointer p2 = x.allocate(s2);
    if (p != 0) {
	x.construct(p2, v2);
	ASSERT_EQ(v2, *p2);
	x.destroy(p);
	x.deallocate(p2, s);
    }

}

TYPED_TEST(TestAllocator, four) {

    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 5;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);
    if (p != 0) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        //x.destroy(p);
        //x.deallocate(p, s);
    }   

    const difference_type s2 = 3;
    const value_type v2 = 3;
    const pointer p2 = x.allocate(s2);
    if (p != 0) {
	x.construct(p2, v2);
	ASSERT_EQ(v2, *p2);
	x.destroy(p);
	x.deallocate(p, s);
	x.destroy(p2);
	x.deallocate(p2, s);
    }   
}
*/

// downing test
/*
TYPED_TEST(TestAllocator, Ten) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const difference_type s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != 0) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);
    }
}
*/ 







