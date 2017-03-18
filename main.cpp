#include<fstream>
#include<iostream>
#include<vector>
#include<ctime>
#include<random>
int calculate( std::vector<int> &n , int k , int i )  
{
    int total = 0 ;
    int inc = 0 , dec = 0 ; 
    for( int end = i+1 ; end <= i+k-1 ; end++ )
    {
        if ( n[end] > n[end-1] )
        {
            inc++ ;  
            dec = 0 ; 
        } 
        else if ( n[end] < n[end-1] )
        {
            dec++ ; 
            inc = 0 ; 
        }
        else
        {
            inc = 0 ; 
            dec = 0 ;
        }
        total += inc-dec ; 

    }
    return total ; 
}

int main()
{
    std::ifstream inp ;
    std::ofstream opt ; 
    inp.open("input.txt") ; 
    inp.open("answer.txt") ; 
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
    std::vector<int> diff(n-1) ;
    for( int i = 0 ; i < nums.size() ; i++ )
    {
        //inp >> nums[i] ; 
        nums[i] = rand()%1000 ; 
    }
    inp.close() ; 
    clock_t time = clock() ; 
    for( int i = 0 ; i < n - k + 1 ; i++ )
    {
        opt << calculate( nums , k , i ) << '\n' ; 
    }
    std::cout << "ELAPSED TIME:" << (float)(clock()-time )/CLOCKS_PER_SEC ; 
    return 0 ;    
}