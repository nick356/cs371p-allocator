// ------------------------------
// projects/allocator/Allocator.h
// Copyright (C) 2014
// Glenn P. Downing
// ------------------------------

#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <new>       // bad_alloc, new
#include <stdexcept> // invalid_argument

// ---------
// Allocator
// ---------

using namespace std;

template <typename T, int N>
class Allocator {
	public:
		// --------
		// typedefs
		// --------

		typedef T                 value_type;

		typedef std::size_t       size_type;
		typedef std::ptrdiff_t    difference_type;

		typedef       value_type*       pointer;
		typedef const value_type* const_pointer;

		typedef       value_type&       reference;
		typedef const value_type& const_reference;

	public:
		// -----------
		// operator ==
		// -----------

		friend bool operator == (const Allocator&, const Allocator&) {
			return true;
		}                                              // this is correct

		// -----------
		// operator !=
		// -----------

		friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
			return !(lhs == rhs);
		}

	private:
		// ----
		// data
		// ----

		char a[N];

		// -----
		// valid
		// -----

		/**
		* O(1) in space
		* O(n) in time
		* <your documentation>
		*/
		bool valid () const {
			unsigned int i = 0;
			bool isVal = true;
			int value=0;
			//int tempend=0;
			while(i<N-sizeof(T)){
				if(a[i]<0)
					value = a[i]*-1;
				else
					value = a[i];
				//cout<<"i is: "<< i<<" and a[i] is: "<<(T)a[i]<<endl;
				//cout<<"a["<<i+value+sizeof(T)<<"] is: "<<(T)a[i+value+sizeof(T)]<<endl;
				if(a[i] != a[i+value+sizeof(T)]){
					isVal = false;
					break;
				}

				/*if(a[i+value+sizeof(T)]<0){
					tempend = a[i+value+sizeof(T)]*-1;
				}else{
					tempend = a[i+value+sizeof(T)];
				}*/
				//cout<<"i is: "<< i<<" and a[i] is: "<<(T)a[i]<<endl;
				//cout<<"a["<<i+value+sizeof(T)<<"] is: "<<(T)a[i+value+sizeof(T)]<<endl;
				i = i+value+sizeof(T)*2;
				//cout<<"This is i before it jumps back through the while loop: "<< i<<endl;
			}
			return isVal;
		}

		/**
		* O(1) in space
		* O(1) in time
		* <your documentation>
		*/
		int& view (int i) {
			return *reinterpret_cast<int*>(&a[i]);
		}

	public:
		// ------------
		// constructors
		// ------------

		/**
		* O(1) in space
		* O(1) in time
		* throw a bad_alloc exception, if N is less than sizeof(T) + (2 * sizeof(int))
		*/
		Allocator () {
			if(N < sizeof(T) + (2 * sizeof(int)))
				throw bad_alloc();
			a[0] = N - 2*sizeof(T);
			a[N-sizeof(T)] = N - 2*sizeof(T);

			//cout<<"This is a[0]: "<<(T)a[0]<<endl;
			//cout<<"This is a[N-sizeof(T)]: "<<(T)a[N-sizeof(T)]<<endl;

			assert(valid());
		}

		// Default copy, destructor, and copy assignment
		// Allocator  (const Allocator&);
		// ~Allocator ();
		// Allocator& operator = (const Allocator&);

		// --------
		// allocate
		// --------

		/**
		* O(1) in space
		* O(n) in time
		* after allocation there must be enough space left for a valid block
		* the smallest allowable block is sizeof(T) + (2 * sizeof(int))
		* choose the first block that fits
		* return 0, if allocation fails
		*/
		pointer allocate (size_type n) {
			if(n == 0)
				throw bad_alloc();
			bool isFound = false;
			int sizeofN = sizeof(T) * n;
			unsigned int i = 0;
			while(i<N-sizeof(T) && !isFound){
				if(a[i]<0){
					int temp = -1*a[i];
					i = i+temp + sizeof(T);
				}else if(a[i] < sizeofN){
					i = i + a[i] +sizeof(T) ;
				}else{
					int orig_size = a[i];
					int orig_last = i+a[i]+sizeof(T);
					int negsize = (-1 *sizeofN);
					int oldI = i;
					
					/*cout<<endl;
					cout<<"This is the orig_size: "<<orig_size<<endl;
					cout<<"This is the orig_last: "<<orig_last<<endl;
					cout<<endl;
					cout<<"This is the size being taken up: "<<negsize<<endl;
					cout<<endl;
					cout<<endl;*/
					a[i] = negsize;
					a[i + sizeofN+sizeof(T)] = negsize;
					//cout<<"This is the address of the second part: "<< i+sizeofN+sizeof(T)<<endl;
					//cout<<endl;
					i = i + sizeofN +sizeof(T)*2;
					//cout<<"This is the new i: "<<i;
					//cout<<endl;					
					a[i] = orig_size + (negsize)-2*sizeof(T);
					//cout<<"This is what goes in it: "<<orig_size+negsize-2*sizeof(T)<<endl;
					a[orig_last] = orig_size + (negsize)-2*sizeof(T);
					isFound = true;
					assert(valid());
					return (pointer)&a[oldI+sizeof(T)];
				}
			}
			return 0;
		}// replace!

		// ---------
		// construct
		// ---------

		/**
		* O(1) in space
		* O(1) in time
		* <your documentation>
		*/
		void construct (pointer p, const_reference v) {
			new (p) T(v);                               // this is correct and exempt
			assert(valid());
		} 			                          // from the prohibition of new

		// ----------
		// deallocate
		// ----------

		/**
		* O(1) in space
		* O(1) in time
		* after deallocation adjacent free blocks must be coalesced
		* <your documentation>
		*/
		void deallocate (pointer p, size_type) {
			int index = ((char*)p - a)-sizeof(T);
			if(a[index] > 0)
				throw bad_alloc();
			int size = a[index] * -1;
			int endsent = size+(2*sizeof(T));
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"This should be the index:  "<<index<<endl;
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"?????????????????????????"<<endl;
			cout<<"This should be the size: "<<size<<endl;
			cout<<"?????????????????????????"<<endl;
			cout<<"........................."<<endl;
			cout<<"This should be the end sentinal index: "<<endsent<<endl;
			cout<<"........................."<<endl;
			
			assert(valid());
		}

		// -------
		// destroy
		// -------

		/**
		* O(1) in space
		* O(1) in time
		* throw an invalid_argument exception, if pointer is invalid
		* <your documentation>
		*/
		void destroy (pointer p) {
			p->~T();               // this is correct
			assert(valid());
		}

		/**
		* O(1) in space
		* O(1) in time
		* <your documentation>
		*/
		const int& view (int i) const {
			return *reinterpret_cast<const int*>(&a[i]);
		}
};
#endif // Allocator_h
