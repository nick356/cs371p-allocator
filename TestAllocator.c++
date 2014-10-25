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

template <typename A>
struct TestConstruct : testing::Test {
	// --------
	// typedefs
	// --------

	typedef          A                  allocator_type;
	typedef typename A::value_type      value_type;
	typedef typename A::difference_type difference_type;
	typedef typename A::pointer         pointer;
};

template <typename A>
struct TestView : testing::Test {
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
            Allocator<double, 100> >
        my_types;

typedef testing::Types<
		Allocator<int,100>,
		Allocator<double, 100> >
	class_types;	

typedef testing::Types<
		Allocator<int, 100>,
		Allocator<int, 200>,
		Allocator<int, 500>,
		Allocator<double, 100>,
		Allocator<double, 200>,
		Allocator<double, 500> >
	constructor_type_tests;		

TYPED_TEST_CASE(TestAllocator, my_types);
TYPED_TEST_CASE(TestView, class_types);
TYPED_TEST_CASE(TestConstruct, constructor_type_tests);


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

TYPED_TEST(TestView, Eleven){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;
		
		allocator_type x;
		const difference_type	s = 11;
		const value_type	v = 4;
		int size = sizeof(x);

	try{
		const pointer		b = x.allocate(s);
		if(sizeof(value_type)*11 < size-8)
			ASSERT_TRUE(true);
		else 
			ASSERT_FALSE(true);
	}catch (...) {
		if(sizeof(value_type)*11 > size - 8)
			ASSERT_TRUE(true);
		else
			ASSERT_FALSE(false);
	}
	
}	

TYPED_TEST(TestView, Twelve){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const difference_type	s = 12;
	const value_type	v = 4;
	try{
		const pointer		b = x.allocate(s);
		if(sizeof(value_type)*12 < sizeof(x)-2*sizeof(value_type))
			ASSERT_TRUE(true);
		else 
			ASSERT_FALSE(true);
	}catch (...) {
		if(sizeof(value_type)* 12 > sizeof(x) - 2*sizeof(value_type))
			ASSERT_TRUE(true);
		else
			ASSERT_FALSE(true);
	}
}

TYPED_TEST(TestView, TestView1){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const difference_type s = 6;
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

TYPED_TEST(TestView, TestView2){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const difference_type s = 4;
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

TYPED_TEST(TestView, TestView3){
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

TYPED_TEST(TestConstruct, Constructors1){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const allocator_type& cx = x;
	int beginValue = cx.view(0);
	int endIndex = beginValue+4;
	ASSERT_TRUE(beginValue == cx.view(endIndex));
}

TYPED_TEST(TestConstruct, Constructors2){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	Allocator<int, 100> y;

	const allocator_type& cx = x;
	const Allocator<int,100>& tempy= y;
	int size = sizeof(x);
	int beginValue = cx.view(0);

	if(size == 100){
		int endIndex = beginValue+4;
		if(beginValue == tempy.view(0))
			ASSERT_TRUE(cx.view(endIndex) == tempy.view(endIndex));
		else{
			int endY = tempy.view(96);
			ASSERT_FALSE(cx.view(endIndex) != endY);
		}

	}else
		ASSERT_TRUE(cx.view(0) != tempy.view(0));
}

TYPED_TEST(TestConstruct, Constructors3){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	Allocator<double, 100> y;

	const allocator_type& cx = x;
	const Allocator<double,100>& tempy= y;
	int size = sizeof(x);
	int beginValue = cx.view(0);
	if(size == 100){
		int endIndex = beginValue+4;
		if(size - 4 == 96)
			ASSERT_TRUE(cx.view(endIndex) == tempy.view(endIndex));
		else{
			int endY = tempy.view(92);
			ASSERT_FALSE(cx.view(endIndex) == endY);
		}

	}else
		ASSERT_TRUE(cx.view(0) != tempy.view(0));
}

TYPED_TEST(TestConstruct, Constructors4){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	Allocator<char, 100> y;

	const allocator_type& cx = x;
	const Allocator<char,100>& tempy= y;
	int size = sizeof(x);
	if(size == 100){
		ASSERT_FALSE(false);
	}else
		ASSERT_FALSE(cx.view(0) == tempy.view(0));
}

TYPED_TEST(TestConstruct, Constructors5){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	allocator_type y;

	const allocator_type& cx = x;
	const allocator_type& cy = y;


	ASSERT_TRUE(cx.view(0) == cy.view(0));

	int xIndex = 4+cx.view(0);
	int yIndex = 4+cy.view(0);

	ASSERT_TRUE(cx.view(xIndex) == cy.view(yIndex));
}
//I did not realise calling sizeof(allocator_type) would give me the N value we for allocator.
//Now I do! So here are two simple tests using it.
TYPED_TEST(TestConstruct, Constructors6){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const allocator_type& cx = x;
	int indexValue = cx.view(0);
	int valueType = 8;
	int size = sizeof(x);
	ASSERT_TRUE(valueType + indexValue == size);

}

TYPED_TEST(TestConstruct, Constructors7){
	typedef typename TestFixture::allocator_type  allocator_type;
	typedef typename TestFixture::value_type      value_type;
	typedef typename TestFixture::difference_type difference_type;
	typedef typename TestFixture::pointer         pointer;

	allocator_type x;
	const allocator_type& cx = x;
	int indexValue = cx.view(0);
	int size = sizeof(x);
	ASSERT_TRUE(indexValue == cx.view(size-4));

}

TEST(Deallocator, default1){
	Allocator<int,100> x;
	typedef int* pointer;
	const pointer p = x.allocate(5);
	const pointer t = x.allocate(3);
	const pointer q = x.allocate(2);
	x.destroy(t);
	x.deallocate(t,3);
	const Allocator<int,100>& cx = x;
	ASSERT_TRUE(cx.view(28) == 12 && cx.view(44) == 12);
	x.destroy(q);
	x.deallocate(q,2);
	ASSERT_TRUE(cx.view(28) == 64 && cx.view(64) == 28);
	x.destroy(p);
	x.deallocate(p,5);
}

TEST(Deallocator, default2){
	Allocator<int, 100> x;
	const Allocator<int,100>& cx = x;
	typedef int* pointer;
	const pointer p = x.allocate(5);
	const pointer t = x.allocate(3);
	x.destroy(t);
	x.deallocate(t,3);
	ASSERT_TRUE(cx.view(28) == 64 && cx.view(96) == 64);
	x.destroy(p);
	x.deallocate(p,5);
}

TEST(Deallocator, default3){
	Allocator<int, 100> x;
	const Allocator<int,100>& cx = x;
	typedef int* pointer;
	const pointer p = x.allocate(5);
	const pointer t = x.allocate(3);
	x.destroy(p);
	x.deallocate(p,5);
	ASSERT_TRUE(cx.view(0) == 20 && cx.view(28) == -12);
	x.destroy(t);
	x.deallocate(t,3);
	ASSERT_TRUE(cx.view(0) == 92);
}

TEST(Deallocator, default4){
	Allocator<int, 100> x;
	const Allocator<int,100>& cx = x;
	typedef int* pointer;
	const pointer p = x.allocate(5);
	x.destroy(p);
	x.deallocate(p,5);
	assert(cx.view(0) == 92);
}

TEST(Allocator, default1){
	Allocator<int, 100> x;
	const Allocator<int,100>& cx = x;
	typedef int* pointer;

	const pointer p = x.allocate(5);
	const pointer t = x.allocate(3);
	const pointer q = x.allocate(2);
	if(cx.view(0) != -20){
		x.destroy(p);
		x.destroy(t);
		x.destroy(q);
		x.deallocate(p,5);
		x.deallocate(t,3);
		x.deallocate(q,2);
		ASSERT_FALSE(true);
	}else if(cx.view(28) != -12){
		x.destroy(p);
		x.destroy(t);
		x.destroy(q);
		x.deallocate(p,5);
		x.deallocate(t,3);
		x.deallocate(q,2);
		ASSERT_FALSE(true);
	}else if(cx.view(48) != -8){
		x.destroy(p);
		x.destroy(t);
		x.destroy(q);
		x.deallocate(p,5);
		x.deallocate(t,3);
		x.deallocate(q,2);
		ASSERT_FALSE(true);
	}else{
		ASSERT_TRUE(true);
		x.destroy(p);
		x.destroy(t);
		x.destroy(q);
		x.deallocate(p,5);
		x.deallocate(t,3);
		x.deallocate(q,2);

	}
}
