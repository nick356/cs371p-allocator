// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2014
// Glenn P. Downing
// ------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

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

template <typename A>
struct TestView : testing::Test{
	typedef          A                  allocator_type;
	typedef typename A::value_type      value_type;
	typedef typename A::difference_type difference_type;
	typedef typename A::pointer         pointer;
};

typedef testing::Types<
            std::allocator<int>,
            std::allocator<double>,
            Allocator<int, 100>,
            Allocator<double, 100> >
        my_types;

typedef testing::Types<
		Allocator<int,100>,
		Allocator<double, 100> >
	class_types;	

TYPED_TEST_CASE(TestAllocator, my_types);
TYPED_TEST_CASE(TestView, class_types);


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
				++p;
			}
		}
		catch (...) {
			while (b != p) {
				--p;
				x.destroy(p);
			}
			x.deallocate(b, s);
		throw;
		}
		ASSERT_EQ(s, std::count(b, e, v));
		while (b != e) {
			--e;
			x.destroy(e);
		}
		x.deallocate(b, s);
	}
}

TYPED_TEST(TestAllocator, Eleven){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const difference_type	s = 5;
	const value_type	v = 4;
	const pointer		b = x.allocate(s);
	if(b != 0){
		pointer end = b + s;
		pointer point = b;
		try{
			while(point != end){
				x.construct(point, v);
				++point;
			}
		}catch(...){
			while(b != point){
				--point;
				x.destroy(point);
			}
			x.deallocate(b, s);
		throw;
		}
		ASSERT_EQ(s, std::count(b,end,v));
		while(b != end){
			--end;
			x.destroy(end);
		}
		x.deallocate(b, s);
	}
}	

TYPED_TEST(TestAllocator, Twelve){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const difference_type	s = 50;
	const value_type	v = 4;
	const pointer		b = x.allocate(s);
	if(b != 0){
		pointer end = b + (int)s;
		pointer point = b;
		try{
			while(point != end){
				x.construct(point, v);
				++point;
			}
		}catch(...){
			while(b != point){
				--point;
				x.destroy(point);
			}
			x.deallocate(b, s);
		throw;
		}
		ASSERT_EQ(s, std::count(b,end,v));
		while(b != end){
			--end;
			x.destroy(end);
		}
		x.deallocate(b, s);
	}
}

TYPED_TEST(TestView, TestView1){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const difference_type s = 1;
	const value_type      v = 2;
	const pointer         p = x.allocate(s);
	if (p == 0) {
		x.construct(p, v);
		ASSERT_EQ(v, *p);
		x.destroy(p);
		x.deallocate(p, s);
	}
}

TYPED_TEST(TestView, TestView2){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const difference_type	s = 50;
	const value_type	v = 4;
	const pointer		b = x.allocate(s);
	if(b != 0){
		pointer end = b + (int)s;
		pointer point = b;
		try{
			while(point != end){
				x.construct(point, v);
				++point;
			}
		}catch(...){
			while(b != point){
				--point;
				x.destroy(point);
			}
			x.deallocate(b, s);
		throw;
		}
		const allocator_type& temp = x;
		const int& sigh = temp.view(0);
		ASSERT_EQ(sigh, 4);
		while(b != end){
			--end;
			x.destroy(end);
		}
		x.deallocate(b, s);
	}
}

TYPED_TEST(TestView, TestView3){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const difference_type	s = 100;
	const value_type	v = 4;
	const pointer		b = x.allocate(s);
	if(b != 0){
		pointer end = b + (int)s;
		pointer point = b;
		try{
			while(point != end){
				x.construct(point, v);
				++point;
			}
		}catch(...){
			while(b != point){
				--point;
				x.destroy(point);
			}
			x.deallocate(b, s);
		throw;
		}
		const allocator_type& temp = x;
		const int& sigh = temp.view(0);
		const int& sigh2 = temp.view(1);
		ASSERT_EQ(sigh, 4);
		ASSERT_EQ(sigh2, 4);
		while(b != end){
			--end;
			x.destroy(end);
		}
		x.deallocate(b, s);
	}
}



