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
		
		//int view(int i){
		//	return (int)a[i];
		//}

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
         * Iterates through the block starting with the first sentinal
	 * and calculates where the end sentinal is. After the end sentinal
	 * has been found we increment the counter by the distance to that
         * sentinal plus the size of the type.
		*/
		bool valid () const {
			unsigned int i = 0;
			bool isVal = true;
			int value=0;
			//int tempend=0;

			while(i<N-4){
				//cout<<"This is i at the start of the loop "<<i<<endl;
				if(view(i)<0)
					value = view(i)*-1;
				else
					value = view(i);

				//cout<<"i is: "<< i<<" and a[i] is: "<<(T)view(i)<<endl;
				//cout<<"a["<<i+value+4<<"] is: "<<(T)view(i+value+4)<<endl;
				if(view(i) != view(i+value+4)){
					return false;
				}
				/*if(a[i+value+sizeof(T)]<0){
					tempend = a[i+value+sizeof(T)]*-1;
				}else{
					tempend = a[i+value+sizeof(T)];
				}*/
				//cout<<"i is: "<< i<<" and a[i] is: "<<(T)a[i]<<endl;
				//cout<<"a["<<i+value+sizeof(T)<<"] is: "<<(T)a[i+value+sizeof(T)]<<endl;
				i = i+value+8;
				//cout<<"This is i before it jumps back through the while loop: "<< i<<endl;
			}
			//cout<<"Out of the while loop"<<endl;
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
         * We set the beginning block with a positive sentinal vale,
	 * and we set the sentinal at the end to the same positive value

		*/
		Allocator () {
			if(N < sizeof(T) + (2 * sizeof(int)) || N <=0)
				throw bad_alloc();
			view(0) = N - 8;
			view(N-4) = N - 8;

			//cout<<"This is a[0]: "<<(T)a[0]<<endl;
			//cout<<"This is a[N-sizeof(T)]: "<<(T)view(N-4)<<endl;

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
         * We iterate through the array till we find the first non negative
         * integer. When we find it we know we have a free block. We also 
         * check to see if it will fit before we try and shove it in the block.
         * We have to cast the value stored at a to be an int pointer
	 * otherwise we will get some garbage. Once we store the value, we
         * calculate the end sentinal for the block, and then make additional
         * calculations to find the size of the now empty block. We then adjust
         * the sentinals for that free block.
         * after allocation there must be enough space left for a valid block
         * the smallest allowable block is sizeof(T) + (2 * sizeof(int))
         * choose the first block that fits
		*/
		pointer allocate (size_type n) {
			//cout<<"What is n: "<<(int)n<<endl;
			if((int)n <= 0){
				throw bad_alloc();
			}

			bool isFound = false;
			int sizeofN = sizeof(T) * n;
			unsigned int unSizeofN = sizeof(T) * n;

			if(unSizeofN > N-8){
				throw bad_alloc();
			}
			unsigned int i = 0;

			while(i<N-8 && !isFound){
				//cout<<"What is i: "<<i<<endl;
				int orig_size = view(i);
				//cout<<"What is orig_size: "<<orig_size<<endl;
				//cout<<"What is sizeofN: "<<sizeofN<<endl;
				//cout<<"What is orig_size - sizeofN: "<<orig_size - sizeofN<<endl;
				if(view(i)<0){
					int temp = -1*view(i);
					//cout<<"This is temp: "<<temp<<endl;
					i = i+temp + 8;
				}else if(orig_size - unSizeofN < sizeof(T)+(2*sizeof(4))){
					//cout<<"We should be in here"<<endl;
					unsigned int orig_last = i+view(i)+4;
					view(i) = view(i) * -1;
					view(orig_last) = view(i);
					isFound = true;
					/*cout<<"This is i: "<<i<<endl;
					cout<<"This is orig_last: "<<orig_last<<endl;
					cout<<"This is the index for the pointer: "<<i+sizeof(T)<<endl;
					cout<<"This is the value: "<<(T)a[i]<<endl;
					cout<<"Do we ever get here"<<endl; */
					return (pointer)&a[i+4];;
				}else if(view(i)<sizeofN){
					i = i+view(i)+8;
				}else{
					unsigned int orig_last = i+view(i)+4;
					signed int negsize = (-1 *sizeofN);
					signed int oldI = i;
					
						/*cout<<endl;
						cout<<"This is the orig_size: "<<orig_size<<endl;
						cout<<"This is the orig_last: "<<orig_last<<endl;
						cout<<endl;
						cout<<"This is the size being taken up: "<<negsize<<endl;
						cout<<endl;
						cout<<endl;
						cout<<"What is i: "<<i<<endl;*/
						view(i) = negsize;
						view(i + sizeofN+4) = negsize;
						//cout<<"This is the address of the second part: "<< i+sizeofN+4<<endl;
						//cout<<"This is in it: "<<view(i+sizeofN+4)<<endl;
						//cout<<endl;
						i = i + sizeofN +8;
						//cout<<"This is the new i: "<<i;
						//cout<<endl;					
						view(i) = orig_size + (negsize)-8;
						//cout<<"This is what goes in it: "<<orig_size+negsize-2*sizeof(T)<<endl;
						view(orig_last) = orig_size + (negsize)-8;
						isFound = true;
						//cout<<"Here we are"<<endl;
						assert(valid());
						//cout<<"Made it"<<endl;

						//cout<<"This is the index for the pointer: "<<oldI+sizeof(T)<<endl;
						//cout<<"This is the value: "<<(T)a[oldI]<<endl;
						return (pointer)&a[oldI+4];
					
				}
			}
			//cout<<"Do we ever get here"<<endl;
			throw bad_alloc();
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
         * To deallocate a block we check to see if the index is 4 or not, that way we will not get a segentation fault when we check back to see
	 * previouse block allocations. We then coalesced the blocks if needed and to do that we see if the next block starts with a negative. If
	 * it does we do nothing, else we look a head by the apporiate size and adjust the sentinals at the start of the new block and the end.
	 * We repeat this process if it has a block free on the left.
         * after deallocation adjacent free blocks must be coalesced
		*/
		void deallocate (pointer p, size_type) {
			if(p == 0)
				throw bad_alloc();
			unsigned int index = ((char*)p - a)-4;
			if(view(index) > 0)
				throw bad_alloc();
			int size = view(index) * -1;
			unsigned int endsent = index+ size+4;
			/*cout<<"1111111111111111111111111"<<endl;
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"This should be the index:  "<<index<<endl;
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"?????????????????????????"<<endl;
			cout<<"This should be the index value: "<<(int)a[index]<<endl;
			cout<<"?????????????????????????"<<endl;
			cout<<"........................."<<endl;
			cout<<"This should be the end sentinal index: "<<endsent<<endl;
			cout<<"........................."<<endl;
			cout<<"-------------------------"<<endl;
			cout<<"This should be the end sentinal value: "<<(int)a[endsent]<<endl;
			cout<<"-------------------------"<<endl;
			cout<<"1111111111111111111111111"<<endl;*/
			if(view(endsent) != view(index))
				throw "The endsentinal value did not match the first sentinal value";

			view(index) = (view(index)*-1);
			int tempInd = index - 4;
			//Checks to see if the block to the left is free if so it coalleses
			if(index > 4 && view(tempInd) >= 0){
				int newIndex = tempInd - view(tempInd) - 4;
				view(newIndex) = view(newIndex) + view(index)+8;
				index = newIndex;
			}

			view(endsent) = view(index);
			tempInd = endsent + 4;

			/*cout<<"2222222222222222222222222"<<endl;
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"This should be the index:  "<<index<<endl;
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"?????????????????????????"<<endl;
			cout<<"This should be the index value: "<<(int)a[index]<<endl;
			cout<<"?????????????????????????"<<endl;
			cout<<"........................."<<endl;
			cout<<"This should be the end sentinal index: "<<endsent<<endl;
			cout<<"........................."<<endl;
			cout<<"-------------------------"<<endl;
			cout<<"This should be the end sentinal value: "<<(int)a[endsent]<<endl;
			cout<<"-------------------------"<<endl;
			cout<<"2222222222222222222222222"<<endl;*/
			
			//cout<<"This is tempInd value: "<<(int)a[tempInd]<<endl;
			//cout<<"This is tempInd: "<<tempInd<<endl;
			if(endsent +4 < N - 4  && view(tempInd) >=  0){
				int newEndSent = tempInd + view(tempInd)+4;
				/*cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
				cout<<"What is newEndSent: "<<newEndSent<<endl;
				cout<<"What is the value of newEndSent: "<<(T)a[newEndSent]<<endl;
				cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
				cout<<"What is oldendSent?: "<<endsent<<endl;
				cout<<"What is it's value: "<<(T)a[endsent]<<endl;*/
				view(newEndSent) = view(newEndSent) + view(endsent)+8;
				endsent = newEndSent;
				view(index) = view(endsent);
				//cout<<"This is the value of a[index]"<<(T)a[index]<<endl;
			}
			/*cout<<"3333333333333333333333333"<<endl;
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"This should be the index:  "<<index<<endl;
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"?????????????????????????"<<endl;
			cout<<"This should be the index value: "<<(int)a[index]<<endl;
			cout<<"?????????????????????????"<<endl;
			cout<<"........................."<<endl;
			cout<<"This should be the end sentinal index: "<<endsent<<endl;
			cout<<"........................."<<endl;
			cout<<"-------------------------"<<endl;
			cout<<"This should be the end sentinal value: "<<(int)a[endsent]<<endl;
			cout<<"-------------------------"<<endl;
			cout<<"3333333333333333333333333"<<endl;*/
			assert(valid());
			//cout<<"We got passed this valid()."<<endl;
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
			//cout<<"What is a[N-sizeof(T)]: "<<view(N-sizeof(T))<<endl;
			p->~T();               // this is correct
			//cout<<"What is a[N-sizeof(T)]: "<<view(N-sizeof(T))<<endl;
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
