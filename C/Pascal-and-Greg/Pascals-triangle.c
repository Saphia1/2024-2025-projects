#include <stdio.h> /* importing library to be able to use printf */
#include <stdlib.h>
long int rows(long int n);
long int factorial(long int x);
int main(int argc, char **argv)
{
  const char *str= argv[1];
  char *endptr;
  long int num;
  num =strtol( str, &endptr, 10);
  if (endptr == str){
    printf("No digits were found. \n");
    return 1;
  }else if (*endptr != '\0'){
    printf("Invalid character: %c\n", *endptr);
    return 1;
  }else if (num<=0 || num>20){
    printf("Invalid character:%c\n", *endptr);
    return 1;
  
  }else if(argv[2] != NULL){
    return 1;
  }
  else if(argv[2] == NULL){
    rows(num);
    }
    
  return 0;
}
long int rows(long int n)
{
  int i;
  int j;
  long int factor2;
  long int factor1;
  long int bottom;
  long int top;
  long int answer;
  long int x;
  int s;


  for (i = (n-1); i != -1; i--) 
  {

    for (j=0; j<=i;j++)
    {
      x=i-j;
      factor1=factorial(x);
      factor2=factorial(j);
      bottom=(factor1*factor2);
      top=factorial(i);
      answer= top/bottom;
      printf("%ld ",answer);


      
    }
    printf("\n");
    for (s=n; s>=i; s--)
    {printf(" ");
    }
    
    

  }
  return 0;}
  
  
long int factorial(long int x)
{
  int i;
  long int total;
  total=1;

  for (i = 1; i < (x+1); ++i) {
    total= total * i;
    }
        
  return total;}
