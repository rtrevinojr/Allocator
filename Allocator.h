
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

		cout << "Match_index = " << match_index << endl;
		if (match_senti > N || match_senti < -N) {
		    match_senti = view(index + abs_next_senti);
		}

		cout << "match_senti = " << match_senti << endl;
		cout << "next_senti = " << next_senti << endl;
		if (next_senti != match_senti)
		    return false;

		int next_index = index + abs_next_senti + 2 * sizeof(int);
		//cout << "next_index = " << next_index << endl;
		if (next_index < N) {	
		    next_senti = view(next_index);
		    cout << "next_senti = " << next_senti << endl;
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
	    cout << "x.allocate(" << n << ") = " << view(0) << endl;
	    size_type malloc_size = sizeof(T) * n;
	    size_type total_malloc_size = malloc_size + 2 * sizeof(int);
	    cout << "malloc_size = " << malloc_size << endl;
	    cout << "total_malloc_size = " << total_malloc_size << endl;
	    int senti_it = view(0);
	    bool no_space = false;
	    int abs_senti_it = std::abs( senti_it );
	    int index = 0;
	    int neg_msize = -malloc_size;
	    while (senti_it < 0) {
		abs_senti_it = std::abs( senti_it );
		//cout << "senti_index = " << senti_index << endl;
		senti_it = view(abs_senti_it + 2 * sizeof(int));
		//cout << "senti_it = " << senti_it << endl;
		index += abs_senti_it + 2 * sizeof(int);
	    	//cout << "allocate index = " << index << endl;
	    }
	
	    int match_index = index;
	    match_index += malloc_size + sizeof(int);
	    //cout << "match_index = " << match_index << endl;
	    int abs_n= std::abs(malloc_size);

	    int next_free_index = index + malloc_size + 2 * sizeof(int);
	    cout << "next_free_index = " << next_free_index << endl;
	    int avail = N - next_free_index - 2 * sizeof(int);
	    cout << "avail heap left = " << avail << endl;

	    if (total_malloc_size > avail + malloc_size + 2 * sizeof(int)) { 
		return 0;
	    }
	    if (avail < 0) {
		return 0;
	    }
	    if (avail < sizeof(T) + 2 * sizeof(int)) {
		int test_neg_msize = neg_msize; 
		test_neg_msize = test_neg_msize - avail - (2 * sizeof(int));
	  	cout << "test_neg_msize = " << test_neg_msize << endl;
		no_space = true;
		cout << "new index = " << index << endl;
		int test_match_index = match_index;
		test_match_index += avail + 2 * sizeof(int);
		cout << "new match_index = " << match_index << endl;
		cout << "test_match_index = " << test_match_index << endl;
		neg_msize = test_neg_msize;
		match_index = test_match_index;
	    }

	    view(index) = neg_msize;
	    view(match_index) = neg_msize;
	    cout << "view(index) = " << view(index) << endl;
	    cout << "view(match_index) = " << view(match_index) << endl; 

	    if(!no_space) {
	        view(next_free_index) = avail;
	        view(next_free_index + avail + 4) = avail;
	    }
	    cout << "next_free_index = " << next_free_index << endl;
	    cout << "view(next_free_index) = " << view(next_free_index) << endl;
	    cout << "next_free_index + avail = " << next_free_index + avail << endl;
	    cout << "view(next_free_index + avail) = " << view(next_free_index + avail) << endl << endl;

	    assert(valid());
	    return (pointer) (a + index + 4); 
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
	    
	    cout << endl << "x.DEALLOCATE()-----------------" << endl;
	    bool no_neigh = false;
	    bool both_neigh = false;
	    bool right_neigh = true;
	    bool left_neigh = true;

	    char* p_cast = reinterpret_cast<char*> (p);

	    int front_senti = view_ch( *(p_cast - 4) );
	    int abs_front_senti = std::abs(front_senti);
	    int end_senti = view_ch( *(p_cast + abs_front_senti) );

	    int abs_end_senti = std::abs(end_senti);
	    cout << "front_senti = " << front_senti << endl;
	    cout << "end_senti = " << end_senti << endl;


	    int left_adj = view_ch( *(p_cast - 2 * sizeof(int)) );
	    int right_adj = view_ch( *(p_cast + abs_front_senti + sizeof(int)) );
	    cout << "left = " << left_adj << endl;
	    cout << "right = " << right_adj << endl;

	    if (front_senti == view_ch(*a) || left_adj < 0 || left_adj > N)
		left_neigh = false;
	    if (end_senti == view_ch(*(a + N)) || right_adj < 0 || right_adj > N)
	 	right_neigh = false;
	    if (!left_neigh && !right_neigh)
		no_neigh = true;
	    if (left_neigh && right_neigh)
		both_neigh = true;

	    cout << "left neighbor = " << left_neigh << endl;
	    cout << "right_neighbor = " << right_neigh << endl;
	    cout << "no_neighbor = " << no_neigh << endl;
	    cout << "both_neighbor = " << both_neigh << endl;

	    int avail = abs_front_senti;
	    cout << "avail = " << avail << endl;

	    ptrdiff_t p_begin = p_cast - a - sizeof(int);
	    ptrdiff_t p_back = p_begin + abs_front_senti + sizeof(int);

	    cout << "ptrdiff_t p_index = " << p_begin << endl;
	    cout << "p_begin = " << p_begin << endl;
	    cout << "p_back = " << p_back << endl;

	    if (no_neigh) {
		cout << "NONE" << endl;
		view(p_begin) = abs_front_senti;
		view(p_back) = abs_end_senti;
		cout << "view(p_begin) = " << view(p_begin) << endl;
		cout << "view(p_back) = " << view(p_back) << endl;
						
	    }	       
	    else if (left_neigh && !right_neigh) {
		cout << "LEFT" << endl;
		avail += left_adj + (2 * sizeof(int));
		ptrdiff_t newindex = p_begin - std::abs(left_adj) - 2 * sizeof(int);
		view(newindex) = avail;
		view(p_back) = avail;
	 	cout << "new index = " << newindex << endl;
		cout << "avail = " << avail << endl;
		cout << "view(newindex) = " << view(newindex) << endl;
		cout << "view(p_back) = " << view(p_back) << endl;
	    } 
	    else if (right_neigh && !left_neigh) {
		cout << "RIGHT" << endl;
		avail += right_adj + (2 * sizeof(int));
		ptrdiff_t newindex = p_back + right_adj + 2 * sizeof(int);
		view(p_begin) = avail;
		view(newindex) = avail;
		cout << "new index = " << newindex << endl;
		cout << "avail = " << avail << endl;
		cout << "view(newindex) = " << view(newindex) << endl;
		cout << "view(p_begin) = " << view(p_begin) << endl;
	    }
	    else {
		cout << "BOTH NEIGHBORS" << endl;
		avail += left_adj + right_adj + 2 * sizeof(int) + 2 * sizeof(int);
		ptrdiff_t right_index = p_back + right_adj + 2 * sizeof(int);
	  	ptrdiff_t left_index = p_begin - left_adj - 2 * sizeof(int);
		view(right_index) = avail;
		view(left_index) = avail;
		cout << "new index right = " << right_index << endl;
		cout << "new index left = " << left_index << endl;
		cout << "avail = " << avail << endl;
		cout << "view(right_index) = " << view(right_index) << endl;
		cout << "view(left_index) = " << view(left_index) << endl;
	    }

            assert(valid());

	}

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

