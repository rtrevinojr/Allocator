
// ------------------------------
// projects/allocator/Allocator.h
// Copyright (C) 2013
// Glenn P. Downing
// ------------------------------

#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // ptrdiff_t, size_t
#include <new>     // new

// my includes
#include <cmath> // std::abs(val)

using namespace std;

// ---------
// Allocator
// ---------

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
            return true;}                                              // this is correct

        // -----------
        // operator !=
        // -----------

        friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
            return !(lhs == rhs);}

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
            // <your code>
	    cout << "VALID() ------------------ " << endl;	
	    cout << endl;
	    int index = 0;
	    int next_senti = view(0);
	    int abs_next_senti = std::abs( next_senti );
	    int match_senti = 0;
	    while (index < N) {
		abs_next_senti = std::abs(next_senti);
		int match_index = index + abs_next_senti + sizeof(int);
		match_senti = view(match_index);
		cout << "match_senti = " << match_senti << endl;

		if (match_senti > N || match_senti < -N) {
		    match_senti = view(index + abs_next_senti);
		}

		cout << "match_senti = " << match_senti << endl;
		if (next_senti != match_senti)
		    return false;

		int next_index = index + abs_next_senti + 2 * sizeof(int);
		//cout << "next_index = " << next_index << endl;
		if (next_index < N) {	
		    next_senti = view(next_index);
		}
		cout << "iterate next_senti = " << next_senti << endl;
	 	index += abs_next_senti + (2 * sizeof(int));
		
		cout << "valid index = " << index << endl;
	    }
	
	    cout << endl;
	    return true;
	}

        /**
         * O(1) in space
         * O(1) in time
         * <your documentation>
         */
        int& view (int i) {
            return *reinterpret_cast<int*>(&a[i]);
	}
	
	int& view_ch (char& c) {
	    return *reinterpret_cast<int*>(&c);
	}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * O(1) in space
         * O(1) in time
         * <your documentation>
         */
        Allocator () {
            // <your code>
	    cout << "Allocator() ------- " << endl;
   	    int senti = N - 2 * sizeof(int);
	    view(0) = senti;
	    view(N - 2 * sizeof(int)) = senti;
            assert(valid());
	    cout << endl;
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
         * <your documentation>
         * after allocation there must be enough space left for a valid block
         * the smallest allowable block is sizeof(T) + (2 * sizeof(int))
         * choose the first block that fits
         */
        pointer allocate (size_type n) {
            // <your code>
	    cout << "x.ALLOCATE(n) ------------ " << endl;
	    //cout << "x.allocate(" << n << ") = " << view(a[0]) << endl;
	    cout << "x.allocate(" << n << ") = " << view(0) << endl;
	    size_type malloc_size = sizeof(T) * n;
	    //int senti_it = view_ch(a[0]);
	    int senti_it = view(0);
	    int abs_senti_it = std::abs( senti_it );
	    int index = 0;
	    int neg_msize = -malloc_size;
	    cout << "Initial senti_it = " << senti_it << endl;

	    cout << "Find free heap space: " << endl;
	    while (senti_it < 0) {
		abs_senti_it = std::abs( senti_it );
		int senti_index = abs_senti_it + 2 * sizeof(int);
		cout << "senti_index = " << senti_index << endl;
		//senti_it = view( a[abs_senti_it + 2 * sizeof(int)] );
		senti_it = view(abs_senti_it + 2 * sizeof(int));
		cout << "senti_it = " << senti_it << endl;
		index += abs_senti_it + 2 * sizeof(int);
	    	cout << "allocate index = " << index << endl;
	    }
	
	    cout << "index = " << index << endl;
	    int match_index = index;
	    match_index += malloc_size + sizeof(int);
	    cout << "match_index = " << match_index << endl;
		
	    int abs_n= std::abs(malloc_size);
	    cout << "abs_senti_it = " << abs_n << endl;
	    view(index) = neg_msize;
	    view(match_index) = neg_msize;
	    cout << "view(index) = " << view(index) << endl;
	    cout << "view(match_index) = " << view(match_index) << endl; 
	    int next_free_index = index + malloc_size + 2 * sizeof(int);
	    cout << "next_free_index = " << next_free_index << endl;
	    int avail = N - next_free_index - 2 * sizeof(int);
	    cout << "avail heap left = " << avail << endl;
	    view(next_free_index) = avail;
	    view(next_free_index + avail) = avail;

	    cout << view(next_free_index) << endl;
	    cout << "next_free_index + avail = " << next_free_index + avail << endl;
	    cout << view(next_free_index + avail) << endl << endl;
/*
	    cout << "before index = " << index << endl;
	    if (index == 0) {
		//view_ch( a[index] ) = neg_n;
		view(0) = neg_n;
		//cout << "view_ch(a[0]) = " << view_ch( a[index] ) << endl;
		cout << "view(0) = " << view(0) << endl;
		view(index + 4) = neg_n;
		cout << "view(index + 4) = " << view(index + 4) << endl;
	    }
	    else {
		//cout << "view( a[0] ) in not 0check  = " << view( a[0] ) << endl;	
		cout << "neg_n matching a[index + 8] index = " << index << endl;
		
	        //view(a[index + 8]) = neg_n;
		//cout << "view( a[0] ) in not 0check  = " << &view(a[0]) << endl;	

		cout << "insertion index a[index] = " << index << endl; 	

	    	view(index) = neg_n;
		cout << "view(index) = " << view(index) << endl;
		int next_index_diff = view(index);
		cout << "next_index_diff = " << next_index_diff << endl;
		view(index + next_index_diff) = neg_n;
		cout << "view(index + next_index_diff) = " << view(index + next_index_diff) << endl;
		index += next_index_diff + sizeof(int);
	    }
	    int avail = N - (index + n + 2 * sizeof(int));
	    difference_type diff = avail - 2 * sizeof(int);

	    if (a[index + avail - 8] < 100) {
		//cout << "view(a[0]) check = " << view(a[0]) << endl;
		
                //view(a[index + avail - 2 * sizeof(int)]) = neg_n; 	
		cout << "index + avail - 8 = " << index + avail - 8 << endl;
		view(index + avail - 2 * sizeof(int)) = neg_n;
		cout << "view(index + avail - 8) = " << view(index + avail - 8) << endl;
		cout << "index + avail = " << index + avail << endl;
		//cout << "view( a[0] ) check  = " << view( a[0] ) << endl;	
		//cout << view_ch( a[0] ) << endl;
	    }
	    cout << "match_index = " << index + avail - 2 * sizeof(int);
	    cout << "n = " << n << endl;
	    cout << "avail - " << avail << endl;
	    cout << "ptrdiff_t: diff = " << diff << endl;
	    cout << "x.allocate(n): n = " << n << endl;
	    //cout << "view(a[0]) after allocate: " << view(a[0]) << endl;
	    cout << "view(a[avail - 8]) = " << view(a[avail - 8]) << endl;
	  
	    if (n + 8 < 100) { 
	        //view( a[n + 8] ) = diff;
	        //view( a[n + 8 + diff + 4] ) = diff;
	    	
		view(n + 8) = diff;
		view(n + 8 + diff + 4) = diff;
	    	cout << "view( a[n + 8] ) = " << view( a[n + 8] ) << endl;
	    	cout << "view( a[n + 8 + diff + 4] ) = " << view( a[n + 8 + diff + 4]) << endl;

	    }
	    //cout << "view(a[0]) end func = " << view(a[0]) << endl;
	    cout << "return allocate index = " << index << endl;
*/
	    assert(valid());
	    return (pointer) (a + index + 4); 
            //return 0; // Replace!
	}                   

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
            assert(valid());}                           // from the prohibition of new

        // ----------
        // deallocate
        // ----------

        /**
         * O(1) in space
         * O(1) in time
         * <your documentation>
         * after deallocation adjacent free blocks must be coalesced
         */
        void deallocate (pointer p, size_type) {
            // <your code>
            assert(valid());}

        // -------
        // destroy
        // -------

        /**
         * O(1) in space
         * O(1) in time
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

	int view_ch (const char& c) const {
	    return *reinterpret_cast<const int*>(&c);
	}
};

#endif // Allocator_h

