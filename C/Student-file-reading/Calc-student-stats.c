#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "convert_integer.h"
#include <math.h>


int countlines(const char *filename);
int getgrade(const char *filename,int *array, int size);
float getmean(int *array, int size,int totalstudents);
float deviation(int *array, int size,float mean, int totalstudents,int absent);
int main(int argc, char **argv)
{   


    char *class= argv[1];
    char *activity=argv[2];
    int i;
    int pupils;
    int activities;
    int *activitygrades;
    int absent;
    float mean;
    float stand;
    FILE *fp;
    char *filename;
    char text[256];
    const char s[2]=",";
    char *token;
    char *last="last_name";


   
    /*validation*/
  
    if (argc<3)
    {
    fprintf(stderr,"ERROR: not enough command line values entered. \n");
    return 1;
    }
    if (argc>3)
    {
    fprintf(stderr,"ERROR: too many command line values entered. \n");
    return 1;   
    }

    for (i=1;i<argc;i++){
        if (access(argv[i],R_OK)!=0){
            fprintf(stderr, "ERROR: File %s is not valid.\nMust be CSV form", argv[i]);
            exit(EXIT_FAILURE);
        }
    }


    filename=argv[1];
    if (!(fp = fopen(filename, "r"))) {
        fprintf(stderr, "error opening %s\n", filename);
        exit(EXIT_FAILURE);
    }




    fgets(text,256,fp); 
    
    text[strcspn(text, "\r\n")] = '\0';
    token=strtok(text,s);
    token=strtok(NULL,s);
    if (*token!=*last){
        fprintf(stderr, "ERROR: File %s is not valid.\nMust be student CSV first", argv[1]);
        return 1;
    } 


    

    fclose(fp);






    pupils=countlines(class);
    


    activities=countlines(activity);
    
   
    absent=pupils-activities;
    printf("total students = %d\n", pupils);
    printf("absent students = %d\n", absent);
    
    activitygrades=(int *) calloc(activities,sizeof(int));

    if(!activitygrades)/*if array currentgen cannot fit into memory, return an error*/
        {
           
            free(activitygrades);
            return 1;
        }
    
    getgrade(activity,activitygrades,activities);
    mean=getmean(activitygrades,activities,pupils);
    stand=deviation(activitygrades,activities,mean,pupils,absent);
    printf("grade mean = %.2f\n", mean);
    printf("grade sd = %.2f\n", stand);
    free(activitygrades);
    return 0;
}


float deviation(int *array, int size,float mean,int totalstudents,int absent)
{
    /*calculate mean, subtract mean from each value, square all deviations, add together, divide by numb students, square root*/
    int i;
    float sub;
    float total=0;
    float square;
    for (i=0;i<absent;i++){
        sub=0-mean;
        square=sub*sub;
        total=total+square;

    }

    for(i=0;i<size;i++){

        sub=(array[i]-mean);

        square=sub*sub;

        total=total+square;

    }
    total=total/totalstudents;
    total=sqrt(total);
    return total;

}


float getmean(int *array, int size,int totalstudents)
{
    int i;
    float total=array[0];
    float mean;
    for(i=1;i<size;i++){
        
        total=total+array[i];

    }
    
    mean = total/totalstudents;
    return mean;

}




int getgrade(const char *filename,int *array, int size)
{   
    FILE *fp;
    char text[256];
    const char s[2]=",";
    char *token;
    int i=0;
    int grade;


    if (!(fp=fopen(filename,"r"))) {
        fprintf(stderr,"error opening %s\n",filename);
        exit(EXIT_FAILURE);
    }
    
    while (fgets(text,256,fp)!=NULL) 
    {
        text[strcspn(text, "\r\n")] = '\0';
        token=strtok(text,s);
        token=strtok(NULL,s);

        if(((i>0)&&i<=size)&&(token!=NULL)){
            grade=convert_integer(token);
            array[i-1]=grade;
        }
        i=i+1;
    }
        
    
    /*for (i=0;i<size;i++){
        printf("%d,",array[i]);
    }*/
    fclose(fp);
    

    return 0;
}

int countlines(const char *filename)
{
    FILE *fp;
    int ch;
    int lines=0;


    if (!(fp = fopen(filename, "r"))) {
        fprintf(stderr, "error opening %s\n", filename);
        exit(EXIT_FAILURE);
    }
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='\n')
        {
            lines++;
        }
    }
    fclose(fp);

    return (lines-1);

    
}
/*


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
*/

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