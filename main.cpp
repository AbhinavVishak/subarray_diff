#include<iostream>
#include<fstream>
#include<vector>

int calculate( std::vector<int> &d , int k ) 
{

}

int main()
{
    std::ifstream inp ; 
    inp.open("input.txt") ; 
    int n,k ; 
    
    if( inp.is_open()  )
    {
        inp >> n >> k ;  
    }
    else 
    {
        std::cout << "FILE WAS NOT OPENED . TERMINATING PROGRAM."  ; 
        return 0 ; 
    }
    std::vector<int> nums(n) ;
    std::vector<int> diff(n-1) ;
    for( int i = 0 ; i < nums.size() ; i++ )
            inp >> nums[i] ; 
    inp.close() ; 
    for( int i = 0 ; i < nums.size()-1 ; i++ )
    {
        if( nums[i] < nums[i+1] ) diff[i] = 1 ; 
        else if ( nums[i] > nums[i+1] ) diff[i] = -1 ; 
        else diff[i] = 0 ; 
    }
    calculate( diff , k) ; 
}