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
	const difference_type	s = 4;
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

TEST(Allocator, default1){
	Allocator<int,100> x;
	typedef int* pointer;
        const pointer p = x.allocate(5);
        const pointer t = x.allocate(3);
        /*const Allocator<int, 100>& cx =x;
	int i = cx.view(0);
	int j = cx.view(28);
	int k = cx.view(48);
	if(i!= -20){
	     x.destroy(p);
	     x.destroy(t);
	     x.deallocate(p,5);
             x.deallocate(t,3);
	     assert(false);	
	}else if(j!=-12){
	     x.destroy(p);
	     x.destroy(t);
             x.deallocate(p,5);
             x.deallocate(t,3);	
	    assert(false);

	}else{
	     assert(true);
	     x.destroy(p);
             x.destroy(t);
             x.deallocate(p,5);
             x.deallocate(t,3);
	}*/
}

TEST(Allocator, default2){
	Allocator<int,100> x;
        typedef int* pointer;
//	cout<<"This is silly"<<endl;
        const pointer p = x.allocate(5);
//	cout<<"I shouldn't have to do this"<<endl;
        const pointer t = x.allocate(3);
//	cout<<"But I have to"<<endl;
	const pointer q = x.allocate(2);
//	cout<<"We are about to enter it"<<endl;
       
	
}
TEST(Deallocator, default3){
	Allocator<int,100> x;
        typedef int* pointer;
	const pointer p = x.allocate(5);
        x.destroy(p);
	x.deallocate(p,5);
  
}

TEST(Deallocator, default4){
	Allocator<int,100> x;
	typedef int* pointer;
	const pointer p = x.allocate(5);
	const pointer t = x.allocate(3);
	x.destroy(p);
	x.deallocate(p,5);
	x.destroy(t);
	x.deallocate(t,3);	
}

TEST(Deallocator,default5){
	Allocator<int,100> x;
	typedef int* pointer;
	const pointer p = x.allocate(5);
	const pointer t = x.allocate(3);
	x.destroy(t);
	x.deallocate(t,3);
	x.destroy(p);
	x.deallocate(p,5);
}



TEST(Deallocator,default6){
	Allocator<int,100> x;
        typedef int* pointer;
        const pointer p = x.allocate(5);
        const pointer t = x.allocate(3);
        const pointer q = x.allocate(2);
        x.destroy(t);
        x.deallocate(t,3);
	x.destroy(q);
	x.deallocate(q,2);
        x.destroy(p);
        x.deallocate(p,5);
}

TEST(Constructor,default1){
    Allocator<int, 16> x;
      //x.destroy(p);
      //x.deallocate(p,3);
   


}

TEST(Constructor,default2){
    Allocator<double,88> x;
      assert( true);
     // x.destroy(p);
     // x.deallocate(p,5);
   }




TEST(Constructor,default3){
    Allocator<int,100> x;
      assert( true);
      //x.destroy(p);
      //x.deallocate(p,8);
   }




TEST(Constructor,default4){
    Allocator<double, 72> x;
	assert(true);

}


