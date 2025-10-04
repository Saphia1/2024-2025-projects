#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*int intdiv(float numb);*/
/*int rules(int a, int b, int c);*/

void printgen(char *array, int size);
int shift(int rule, int total);
int calcstate(int a,int b,int c,int rule);
int main(int argc, char **argv)
{   
    int numcells, gens, ruleset;
    int i, half,a,b,c,j,state;
    char *endptr, *currentgen, *nextgen;

   
    /*validation*/
    if (argc<4)
    {
    printf("ERROR: not enough values entered. \n");
    return 1;
    }
    if (argc>4)
    {
    printf("ERROR: too many values entered. \n");
    return 1;   
    }
    for (i=1;i<4;i++){
        const char *str= argv[i];
        strtol( str, &endptr, 10);
        if (endptr == str)
        {
        printf("Non digits were found. \n");
        return 1;
        }
        else if (*endptr != '\0')
        {
        printf("Invalid character: %c\n", *endptr);
        return 1;
        }
    }
   


    numcells=(int)(atof(argv[1]));
    gens=(int)(atof(argv[2]));
    ruleset=(int)(atof(argv[3]));
 

    if ((numcells<=0)||(gens<=0)||(ruleset>256)||(ruleset<0)){
        printf("ERROR: values entered are not in a valid range");
        return 1;
    }



    /*setting up initial array, first gen*/
    currentgen=(char *) calloc(numcells,sizeof(char));
    nextgen=(char *) calloc(numcells,sizeof(char));
    
    if((!currentgen) || (!nextgen))/*if array currentgen cannot fit into memory, return an error*/
        {
            free(currentgen);
            free(nextgen);
            return 1;
        }

 

    /*filling gen with 0s*/
    for(i=0; i<(numcells-1); i++){
        currentgen[i]=0;/*setting up the array and initialising all parts of memory to 0*/
        nextgen[i]=0;
    }

    /*adding 1 as mid point*/
    half=(int)(numcells/2);
    /*printf("Half:%d\n",half);*/
    currentgen[half]=1;

    
    for (i=0;i<gens;i++){/*outer loop iterating each gen*/
        
        for (j=0;j<numcells;j++)/*inner loop for each cell, skip edge cases*/
        {
            if (j==0){
                a=currentgen[numcells-1];
            }
            else{
                a=currentgen[j-1];
            }
            b=currentgen[j];
            if (j==numcells-1){
                c=currentgen[0];
            }
            else{
                c=currentgen[j+1];
            }
            state=calcstate(a,b,c,ruleset);
            /*printf("state:%d\n",state);*/
            nextgen[j]=state;
        }
        printgen(currentgen,numcells);
        for (j = 0; j<numcells;j++)
        {
            currentgen[j]=nextgen[j];/*set the current gen to be the next gen*/
        }

        
        
    }




    
    free(currentgen);
    free(nextgen);
    return 0;
}

int calcstate(int a,int b,int c,int rule)
{   
    int shifted;
    int state;
    int total=0;
    if (a==1)
    {
        total=total+4;
    }
    if (b==1)
    {
        total=total+2;
    }
    if (c==1)
    {
        total=total+1;
    }
    shifted=shift(rule,total);
    
    state=shifted%2;
    
    return state;
    

}

int shift(int rule, int total)
{   
    int shifted;
    shifted=(rule>>total);
    return shifted;
}


void printgen(char *array, int size)
{
    int i;
    for (i=0;i<size;i++){
        if (array[i]==0)
        {
            printf(" ");
        }
        else
        {
            printf("*");
        }
    }
    printf("\n");
}


/*int intdiv(float numb)
{
  int minuses;
  minuses=0;
  while ((numb-1)>=0)
  {
    numb=numb-1;
    minuses=minuses+1;
  }

  return minuses;
  
}*/
/*int rules(a,b,c)
int whole(float numb)
{

  while ((numb-1)!=0)
  {
    if (numb<0){
        printf("ERROR: integers only");
        return 1;
    }
    numb=numb-1;

  }

  return 0;
  
}*/