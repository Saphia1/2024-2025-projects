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
char* getgrade(const char *classfile, const char *activityfile, char ***studentarray,char ***activityarray,int i, int first);
int main(int argc, char **argv)
{   
    char *file1= argv[1];
    char *activity=argv[2];
    char *results=argv[3];
    int i;
    /*int j;*/
    char ***file1array;
    char ***activityarray;
    char ***resultsarray;
    char *grades;
    char *g1;
    char *g2;
    float mean=0.00;
    char header[256];
    int first=0;
    FILE *fp;
    FILE *rp;

    /*validation*/
  
    if (argc<4)
    {
    fprintf(stderr,"ERROR: not enough command line values entered. \n");
    return 1;
    }
    if (argc>4)
    {
    fprintf(stderr,"ERROR: too many command line values entered. \n");
    return 1;   
    }

    for (i=1;i<argc;i++){
        if (i==3){
            break;
        }
        if (access(argv[i],R_OK)!=0){
            fprintf(stderr, "ERROR: File %s is not valid.\nMust be CSV form", argv[i]);
            exit(EXIT_FAILURE);
        }
    }





    if (countcolumn(file1)<countcolumn(activity)){
        fprintf(stderr, "ERROR: File %s is not valid.\nMust be student or results CSV first", argv[1]);
        return 1;
    } 
    /*need to check if results file is bigger than class IF class file enetered*/ 



    file1array=read_csv(file1,countcolumn(file1));
    activityarray=read_csv(activity,countcolumn(activity));

    if((countcolumn(file1)==3)){/*if student file entered as file 1*/
        first=0;
        if (!(fp = fopen(results, "w"))) 
        {
            fprintf(stderr, "error opening %s\n", results);
            
            exit(EXIT_FAILURE);
        }
        fprintf ( fp , "id,last_name,first_name,average,grade01\n");
        /*printf("id,last_name,first_name,average,grade01\n");*/
        for (i=0;i<(countlines(file1)-1);i++)
        {
            grades=getgrade(file1,activity,file1array,activityarray,i,first);
            mean=(convert_integer(grades)+convert_integer(grades));
            mean=mean/2;
            fprintf ( fp , "%s,%s,%s,%.2f,%s\n",file1array[i][0],file1array[i][1],file1array[i][2],mean,grades);
        }
    }
    else{

        if (!(fp = fopen(results, "w"))) 
        {
            fprintf(stderr, "error opening %s\n", results);
            
            exit(EXIT_FAILURE);
        }
        if (!(rp = fopen(file1, "r"))) 
        {
            fprintf(stderr, "error opening %s\n", argv[1]);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        if (fgets(header,256,rp)!=NULL){
        header[strcspn(header, "\r\n")] = '\0';
        fprintf ( fp , "%s,grade02\n",header);
        /*printf("%s,grade02\n",header);*/
        
        }
        for (i=0;i<(countlines(file1)-1);i++)
        {
            /*printf("\nID:%s",file1array[i][0]);*/
            g2=getgrade(file1,activity,file1array,activityarray,i,first);
            first=1;
            g1=getgrade(file1,activity,file1array,activityarray,i,first);
            first=0;

            /*printf("\n%s,%s",g1,g2);*/
            mean=((convert_integer(g1)+convert_integer(g2)));
            /*printf("\nadd:%.2f",mean);*/
            mean=mean/2;
            /*printf("\nmean:%.2f",mean);*/
            
            
            fprintf ( fp , "%s,%s,%s,%.2f,%s,%s\n",file1array[i][0],file1array[i][1],file1array[i][2],mean,g1,g2);
            /*printf("%s,%s,%s,%d,%s,%s\n",file1array[i][0],file1array[i][2],file1array[i][1],mean,grade1,grade2);*/
        }
        fclose(rp);
    }
        
    
    fclose(fp);
    
    

    resultsarray=read_csv(results,countcolumn(results));
  
        
    /*for (i=0;i<(countlines(results)-1);i++)
    {
     
        for (j=0;j<(countcolumn(results));j++){
            printf("%s ",resultsarray[i][j]);
           
        }
        
        printf("\n");
    }*/

    
    freearray(file1array,file1);
    freearray(activityarray,activity);
    freearray(resultsarray,results);
    return 0;
}

char* getgrade(const char *classfile, const char *activityfile, char ***studentarray,char ***activityarray,int i,int first)
{


    int j;
    char *grade="0";
 
    for (j=0;j<(countlines(activityfile)-1);j++)
        {

            if (strcmp(studentarray[i][0],activityarray[j][0])==0)
            {
                if (first==0){
                grade=activityarray[j][1];
                /*printf("\nFound g1");*/
                return grade;
                }
                else if (first==1){
                grade=studentarray[i][4];
                /*printf("\nFound g2");*/
                return grade;
                }
      
                
            }
        }
    if (first==1){
        grade=studentarray[i][4];
        /*printf("\nAuto g2");*/
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
            if (token==NULL){
                fclose(file);
                for (j=0;j<i;j++){
                    free(array[j]);
            }
            free(array);
            exit(EXIT_FAILURE);  

            }
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
    

    
   /* for (i=0;i<row;i++)
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
    if (array==NULL){
        return 0;
    }
    for (i=0;i<(countlines(filename)-1);i++)
    {
        for(j=0;j<(countcolumn(filename));j++)
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