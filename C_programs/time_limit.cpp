#include <sys/resource.h> 
 #include <sys/time.h> 
 #include <unistd.h> 
 #include<stdio.h> 
  
 int main () 
 { 
   // Define and object of structure 
   // rlimit. 
   struct rlimit rl; 
  
   // First get the time limit on CPU 
   getrlimit (RLIMIT_CPU, &rl); 
  
   printf("\n Default value is : %lld\n", (long long int)rl.rlim_cur); 
  
   // Change the time limit 
   rl.rlim_cur = 1; 
  
   // Now call setrlimit() to set the  
   // changed value. 
   setrlimit (RLIMIT_CPU, &rl); 
  
   // Again get the limit and check 
   getrlimit (RLIMIT_CPU, &rl); 
  
   printf("\n Default value now is : %lld %lld\n", (long long int)rl.rlim_cur, (long long int)rl.rlim_max); 
  
   // Simulate a long time consuming work 
   while (1); 
  
   return 0; 
 }