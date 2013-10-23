
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
	
	    int add_sentinals = 2 * sizeof(int);
  	    cout << "a[0] = " << (int) a[0] << endl;	

	    int byte_size = (int) a[0];

	    int first_senti = view(a[0]);
	    cout << "first_senti: " << first_senti << endl;
	    int next_senti = view_ch(a[0]);
	    cout << "next_senti: " << next_senti << endl;
	    int zero_senti = view(0);
	    cout << "zero_senti: " << zero_senti << endl;
	    if ( first_senti < 100 )
	        cout << "check end senti - view(a[senti]) - " << view(a[first_senti + sizeof(int)]) << endl;
	    else
		cout << "check end senti - view(a[first_senti]) - " << view(a[next_senti + sizeof(int)]) << endl;	
	    
	    
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
	    //cout << "N = " << N << endl;
   	    int senti = N - 2 * sizeof(int);
	    cout << "senti = " << senti << endl;	    
	    view(a[0]) = senti;
	    view(a[N - sizeof(int)]) = senti;
	    cout << "view(a[0]): " << view(a[0]) << endl;
	    difference_type diff = N - senti;
	    cout << "ptrdiff_t - " << diff << endl;

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
	    size_type neg_n = ~n + 1;
	    view(a[0]) = n;
	    int avail = N - (n + 2 * sizeof(int));
	    cout << "avail - " << avail << endl;
	    difference_type diff = avail - 2 * sizeof(int);
	    cout << "ptrdiff_t: " << diff << endl;
	    cout << "x.allocate(n): n = " << n << endl;
	    cout << "view(a[0]) after allocate: " << view(a[0]) << endl;
            view(a[avail - 2 * sizeof(int)]) = n; 	
	    cout << "view(a[avail - 8]) = " << view(a[avail - 8]) << endl;

	    view( a[n + 8] ) = diff;
	    view( a[n + 8 + diff + 4] ) = diff;

	    cout << "view( a[n + 8] ) = " << view( a[n + 8] ) << endl;
	    cout << "view( a[n + 8 + diff + 4] ) = " << view( a[n + 8 + diff + 4]) << endl;

	    //assert(valid());
	    cout << endl;
	    return (pointer) (a + 4);
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

