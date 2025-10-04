#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "convert_integer.h"
#include <math.h>
int freearray(char ***array, char *filename);
int countlines(const char *filename);
int countcolumn(const char *filename);
char*** read_csv(char *filename,int columns);
char* getgrade(const char *classfile, const char *activityfile, char ***studentarray,char ***activityarray,int i);
int main(int argc, char **argv)
{   


    char *class= argv[1];
    char *activity=argv[2];
    int i;
    FILE *fp;
    char *filename;
    char ***studentarray;
    char ***activityarray;
    char *grade;


   
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
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp);




    if (countcolumn(class)<countcolumn(activity)){
        fprintf(stderr, "ERROR: File %s is not valid.\nMust be student CSV first", argv[1]);
        return 1;
    } 


    studentarray=read_csv(class,countcolumn(class));
    activityarray=read_csv(activity,countcolumn(activity));
   

        
    for (i=0;i<(countlines(class)-1);i++)
    {
     

        printf("%s ",studentarray[i][2]);
        printf("%s ",studentarray[i][1]);
        grade=getgrade(class,activity,studentarray,activityarray,i);
        printf("%s",grade);
        printf("\n");
    }

    
    freearray(studentarray,class);
    freearray(activityarray,activity);
    return 0;
}

char* getgrade(const char *classfile, const char *activityfile, char ***studentarray,char ***activityarray,int i)
{

    int j;
    char *grade="0";
 
    for (j=0;j<(countlines(activityfile)-1);j++)
        {
            
            if (strcmp(studentarray[i][0],activityarray[j][0])==0)
            {
                grade=activityarray[j][1];
                return grade;
            }
        }
    
    return grade;
}
int countcolumn(const char *filename)
{
    
    char text[256];/*holds each line*/
    const char s[2]=",";
    char *token;
    int column=0;
    FILE *fp;
    

    if (!(fp = fopen(filename, "r"))) {
        fprintf(stderr, "error opening %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if(fgets(text,sizeof(text),fp))
    {
        text[strcspn(text, "\r\n")] = '\0';
        token=strtok(text,s);
        while(token != NULL)
        {
            column++;
            token=strtok(NULL,s);
        }
        
        
    }
    fclose(fp);

    return (column);

    
}
char*** read_csv(char *filename, int columns)
{
    int row = countlines(filename)-1;
    int column = columns;
    int i=0; 
    int j=0;
    int x;
    int y;
    char text[256];/*holds each line*/
    const char s[2]=",";
    char *token;
    char ***array;
    FILE *file = fopen(filename, "r");

    if (fgets(text,256,file)==NULL) {
        fprintf(stderr,"error opening %s\n",filename);
        fclose(file);
        exit(EXIT_FAILURE);
        
    }
    array=malloc(sizeof(char**)*row);/*allocates columns*/
        if (!(array)) {
            free(array);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    
    while (fgets(text,256,file) && (i<row))
    {
        text[strcspn(text, "\r\n")] = '\0';
        token=strtok(text,s);
        array[i]=malloc(sizeof(char*)*column);/*allocates rows*/
        if (!(array[i]))
        {
            fclose(file);
            for (j=0;j<i;j++){
                free(array[j]);
            }
            free(array);
            exit(EXIT_FAILURE);    
        }
        
        for (j=0;j<column;j++)
        {
            
            array[i][j]=malloc((strlen(token)+1)*sizeof(char));
                    
            if (!(array[i][j])) {
                for (x=0;x<i;x++)
                {
                    for(y=0;y<j;y++)
                    {   
                        
                        free(array[x][y]);
                    }
                    free(array[x]);
                
                    

                }
                free(array);
                fclose(file);

                exit(EXIT_FAILURE);
            }
                    
            strncpy(array[i][j],token,strlen(token)+1);
            token=strtok(NULL,s);
                    
        }
        i++;
    }
    

    
    /*for (i=0;i<row;i++)
    {
     
        for(j=0;j<column;j++)
        {
            printf("%s ",array[i][j]);
          
        }
        printf("\n");
    }*/
  

    fclose(file);
  
    

    
    return array;
}

int freearray(char ***array,char*filename)
{
    int i;
    int j;
    int row = countlines(filename)-1;
    int column = countcolumn(filename);
    for (i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {   
            
            free(array[i][j]);
        }
        free(array[i]); 

    }
    free(array);
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

    return (lines);

    
}
/*        if ((i < row)||(j==column)){ 
            i++;
            j=0;
            }
        else if((i==row)||(j==column)){
            i=0;
            j=0;
        }
        else{
            i++;
            j++;
        }*/