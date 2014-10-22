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
			int i = 0;
			bool isVal = true;
			while(i<N-sizeof(T)){
				if(a[i] != a[a[i]+sizeof(T)])
					isVal = false;
				cout<<"i is: "<< i<<" and a[i] is: "<<(int)a[i]<<endl;
				cout<<"a[i]+sizeof(T) is: "<<(int)a[i]+sizeof(T)<<" and a[a[i]+sizeof(T)] is: "<< (int)a[a[i]+sizeof(T)]<<endl;
				i = a[i]+sizeof(T);
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
			if(N < sizeof(T) + (2 * sizeof(T)))
				throw;
			a[0] = N - 2*sizeof(T);
			a[N-sizeof(T)] = N - 2*sizeof(T);

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
			assert(valid());
			bool isFound = false;
			int sizeofN = sizeof(T) * n;
			int i = 0;
			while(i<N-sizeof(T) && !isFound){
				if(a[i]<0){
					int temp = -1*a[i];
					i = i+temp + sizeof(T);
				}else if(a[i] < sizeofN){
					i = i + a[i] +sizeof(T) ;
				}else{
					int orig_size = a[i];
					int orig_last = i+a[i]+sizeof(T);
					
					a[i] = -1 * sizeofN;
					a[i + sizeofN + sizeof(T)] = -1 * sizeofN;
					i = i + sizeofN +(2*sizeof(T));
					a[
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
			// <your code>
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
