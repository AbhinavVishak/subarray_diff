#include<fstream>
#include<iostream>
#include<vector>
#include<ctime>
#include<random>
#include<list>

int process_lists( std::list<std::pair<int,int>> &inc_l, std::list<std::pair<int,int>> &dec_l )
{   
    int total = 0, s = 0 ; 
    for( auto pair : inc_l )
    {
        s = pair.second-pair.first + 1 ; 
        total += (s-1)*s/2 ; 
    }
    for( auto pair : dec_l )
    {
        s = pair.second-pair.first + 1 ; 
        total -= (s-1)*s/2 ; 
    }
    return total ; 
}

void calculate2( std::vector<int> &nums , int k )
{
    int total = 0 ; 
    std::ofstream o ; 
    o.open("answer2.txt") ; 
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
    
    o << process_lists( inc_l , dec_l ) << '\n' ; 
    // use previous window information with front and back change to 
    for( int start_w = 1,end_w = k ; start_w < nums.size()-k+1 ; start_w++, end_w++ ) 
    {
        // see if end element can extend any subarrays
        if( nums[end_w] > nums[end_w-1] )
        {
            if( inc_l.back().second == end_w-1 ) inc_l.back().second++ ; 
            else inc_l.push_back( std::make_pair(end_w-1,end_w) ) ; 
        }
        if( nums[end_w] < nums[end_w-1] )
        {
            if( dec_l.back().second == end_w-1 ) dec_l.back().second++ ; 
            else dec_l.push_back( std::make_pair(end_w-1,end_w) ) ; 
        }
        if( inc_l.front().first == start_w - 1 )
        {
            if( inc_l.front().second > start_w ) inc_l.front().first++ ; 
            else inc_l.pop_front() ; 
        }
        if( dec_l.front().first == start_w - 1 )
        {
            if( dec_l.front().second > start_w ) dec_l.front().first++ ; 
            else dec_l.pop_front() ; 
        }
        o << process_lists( inc_l , dec_l ) << '\n' ; 
    }
}
int main()
{
    std::ifstream inp ;
    std::ofstream opt ; 
    inp.open("input.txt") ; 
    int n,k ; 
    if( inp.is_open()  )
    {
        inp >> n >> k ;  
        std::cout << "LENGTH OF ARRAY:" << n << '\n' << "LENGTH OF WINDOW:" << k << std::endl ; 
    }
    else 
    {
        std::cout << "FILE WAS NOT OPENED . TERMINATING PROGRAM."  ; 
        return 0 ; 
    }
    std::vector<int> nums(n) ;
    for( int i = 0 ; i < nums.size() ; i++ )
    {
        //inp >> nums[i] ; 
        nums[i] = rand()%1000 ; 
    }
    inp.close() ; 

    clock_t time = clock() ; 
    calculate2( nums , k ) ; 
    std::cout << "ELAPSED TIME:" << (float)(clock()-time )/CLOCKS_PER_SEC << " SECS.." ; 
    return 0 ;    
}