#include<fstream>
#include<iostream>
#include<vector>
#include<ctime>
#include<list>
#include<random>

long long int process_lists( std::list<std::pair<int,int>> &inc_l, std::list<std::pair<int,int>> &dec_l )
{   
    /**
        Given 2 lists, one containing start and ending indices of increasing subranges, and 
        one containing containing start and ending indices of decreasing subranges, this 
        function calculates the score of the window containing these lists.
    */
    long long int total = 0, s = 0 ; 
    for( auto pair : inc_l )
    {
        s = pair.second - pair.first + 1 ; // SIZE OF AN INCREASING SUBRANGE
        total += (s-1)*s/2 ;               // NUMBER OF POSSIBLE SUBRANGES WITHIN THE SUBRANGE
    }
    for( auto pair : dec_l )
    {
        s = pair.second - pair.first + 1 ; // SIZE OF A DECREASING SUBRANGE
        total -= (s-1)*s/2 ;               // NUMBER OF POSSIBLE SUBRANGES WITHIN THE SUBRANGE
    }
    return total ; 
}

void calculate( std::vector<int> &nums , int k )
{
    long long int total = 0 ; 
    std::ofstream o ; 
    o.open("answer.txt") ; 
    std::list<std::pair<int,int>> inc_l,dec_l ; 
    // Populate inc_l for the first window
    int start = 0 ; 
    for( int i = 1 ; i < k ; i++ )
    {
        if( nums[i] <= nums[i-1] ) // no longer increasing
        {
            if( start != i-1 ) inc_l.push_back( std::make_pair(start,i-1) ) ; 
            start = i ; 
        }
    }
    if( start != k-1 ) inc_l.push_back( std::make_pair(start,k-1) ) ; 
    // POPULATE DEC_L FOR THE FIRST WINDOW
    start = 0 ; 
    for( int i = 1 ; i < k ; i++ )
    {
        if( nums[i] >= nums[i-1] ) // no longer increasing
        {
            if( start != i-1 ) dec_l.push_back( std::make_pair(start,i-1) ) ; 
            start = i ; 
        }
    }
    if( start != k-1 ) dec_l.push_back( std::make_pair(start,k-1) ) ; 
    total = process_lists( inc_l , dec_l ) ;
    o << total << '\n' ; 

    // use previous window information with front and back change to 
    for( int start_w = 1,end_w = k ; start_w < nums.size()-k+1 ; start_w++, end_w++ ) 
    {   
        // see if end element can extend any subarrays
        if( nums[end_w] > nums[end_w-1] )
        {
            if( inc_l.back().second == end_w-1 ) { inc_l.back().second++ ; }
            else { inc_l.push_back( std::make_pair(end_w-1,end_w) ) ; }

            int s = inc_l.back().second - inc_l.back().first + 1 ; // s has new subarray size
            total += s*(s-1)/2 - (s-1)*(s-2)/2 ; 
        }
        else if( nums[end_w] < nums[end_w-1] )
        {
            if( dec_l.back().second == end_w-1 ) dec_l.back().second++ ; 
            else dec_l.push_back( std::make_pair(end_w-1,end_w) ) ; 
            
            int s = dec_l.back().second - dec_l.back().first + 1 ; // s has new subarray size
            total -= s*(s-1)/2 - (s-1)*(s-2)/2 ; 
        }
        if( inc_l.front().first == start_w - 1 )
        {
            int s = inc_l.front().second - inc_l.front().first + 1 ; // s has new subarray size
            total -= s*(s-1)/2 - (s-1)*(s-2)/2 ; 

            if( inc_l.front().second > start_w ) inc_l.front().first++ ; 
            else inc_l.pop_front() ; 
        }
        else if( dec_l.front().first == start_w - 1 )
        {
            int s = dec_l.front().second - dec_l.front().first + 1 ; // s has new subarray size
            total += s*(s-1)/2 - (s-1)*(s-2)/2 ; 

            if( dec_l.front().second > start_w ) dec_l.front().first++ ; 
            else dec_l.pop_front() ; 
        }
        o << total << '\n' ; 
    }
}

int main()
{
    std::cout << "1 - COMPLETE INPUT IS READ FROM FILE \"input.txt\" .     \n"
              << "2 - manually enter n and k. values will be generated randomly.\n" 
              << " Please input either 1 or 2..." << std::endl ; 
    int n,k ; 
    int option ; 
    std::cin >> option ; 
    std::ifstream inp ;
    if( option == 1 )
    {
        inp.open("input.txt") ; 
        if( inp.is_open() ) inp >> n >> k ;  
        else 
        {
            std::cout << "FILE WAS NOT OPENED . TERMINATING PROGRAM."  ; 
            return 0 ; 
        }
        if( n < 1 || n > 200000 )
        {
            std::cout << "N NOT IN RANGE [1,200000], INVALID INPUT" << std::endl ; 
            return 0 ; 
        }
        if( k < 1 || k > n )
        {
            std::cout << "k NOT IN RANGE [1,N], INVALID INPUT" << std::endl ; 
            return 0 ; 
        }
    }
    else if( option == 2 )
    {
        std::cout << "\nPlease enter n :.. " ;
        std::cin >> n ; 
        std::cout << "\nPlease enter k :.. " ;
        std::cin >> k ; 
        if( n < 1 || n > 200000 )
        {
            std::cout << "N NOT IN RANGE [1,200000], INVALID INPUT" << std::endl ; 
            return 0 ; 
        }
        if( k < 1 || k > n )
        {
            std::cout << "k NOT IN RANGE [1,N], INVALID INPUT" << std::endl ; 
            return 0 ; 
        }    
    }
    std::vector<int> nums(n) ; 
    if( option == 2 )
        for( int i = 0 ; i < nums.size() ; i++ ) nums[i] = rand()%1000 ; 
    else if( option == 1 )
        for( int i = 0 ; i < nums.size() ; i++ ) inp >> nums[i] ; 

    // ASSUMING THAT THE LIST OF NUMBERS IS WELL DEFINED AND VALID
    inp.close() ; 
    std::cout << "LENGTH OF ARRAY:" << n << '\n' << "LENGTH OF WINDOW:" << k << std::endl ; 
    clock_t time = clock() ; 
    calculate( nums , k ) ; 
    std::cout << "ELAPSED TIME:" << (float)(clock()-time )/CLOCKS_PER_SEC << " SECS.." ; 
    return 0 ;
}