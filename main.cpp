#include<fstream>
#include<iostream>
#include<vector>
#include<list>

long long int process_lists( std::list<std::pair<int,int>> &inc_l, std::list<std::pair<int,int>> &dec_l )
{   
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
    int start = 0 ; 
    for( int i = 1 ; i < k ; i++ )
    {
        if( nums[i] <= nums[i-1] ) 
        {
            if( start != i-1 ) inc_l.push_back( std::make_pair(start,i-1) ) ; 
            start = i ; 
        }
    }
    if( start != k-1 ) inc_l.push_back( std::make_pair(start,k-1) ) ; 
    start = 0 ; 
    for( int i = 1 ; i < k ; i++ )
    {
        if( nums[i] >= nums[i-1] ) 
        {
            if( start != i-1 ) dec_l.push_back( std::make_pair(start,i-1) ) ; 
            start = i ; 
        }
    }
    if( start != k-1 ) dec_l.push_back( std::make_pair(start,k-1) ) ; 
    total = process_lists( inc_l , dec_l ) ;
    o << total << '\n' ; 
    for( int start_w = 1,end_w = k ; start_w < nums.size()-k+1 ; start_w++, end_w++ ) 
    {   
        if( nums[end_w] > nums[end_w-1] ) 
        {
            if( inc_l.back().second == end_w-1 ) { inc_l.back().second++ ; }
            else { inc_l.push_back( std::make_pair(end_w-1,end_w) ) ; }

            long long int s = inc_l.back().second - inc_l.back().first + 1 ; // s has new subarray size
            total += s*(s-1)/2 - (s-1)*(s-2)/2 ; 
        }
        else if( nums[end_w] < nums[end_w-1] ) 
        {
            if( dec_l.back().second == end_w-1 ) dec_l.back().second++ ; 
            else dec_l.push_back( std::make_pair(end_w-1,end_w) ) ; 
            
            long long int s = dec_l.back().second - dec_l.back().first + 1 ; // s has new subarray size
            total -= s*(s-1)/2 - (s-1)*(s-2)/2 ; 
        }
        if( inc_l.front().first == start_w - 1 ) 
        {
            long long int s = inc_l.front().second - inc_l.front().first + 1 ; // s has new subarray size
            total -= s*(s-1)/2 - (s-1)*(s-2)/2 ; 

            if( inc_l.front().second > start_w ) inc_l.front().first++ ; 
            else inc_l.pop_front() ; 
        }
        if( dec_l.front().first == start_w - 1 ) 
        {
            long long int s = dec_l.front().second - dec_l.front().first + 1 ; // s has new subarray size
            total += s*(s-1)/2 - (s-1)*(s-2)/2 ; 

            if( dec_l.front().second > start_w ) dec_l.front().first++ ; 
            else dec_l.pop_front() ; 
        }
        o << total << '\n' ;
    }
}

int main(int argc , char* argv[] )
{
    if( argc == 1 )
    {
        std::cout << "not enough inputs" ;
        return 0 ; 
    }
    int n,k ; 
    std::ifstream inp( argv[1] ) ;
    inp >> n >> k ;  
    if( k == 1 )
    {
        std::ofstream o ;
        o.open("answer.txt") ; 
        for( int i = 0 ; i < n ; i++ ) o << 0 << '\n' ; 
        o.close() ; 
        return 0 ; 
    }
    std::vector<int> nums(n) ;
    for( int i = 0 ; i < nums.size() ; i++ ) inp >> nums[i] ; 
    inp.close() ;  
    calculate( nums , k ) ; 
    return 0 ;
}