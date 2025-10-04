/*
 *  disarm.c
 *  DisARM
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int SignExtend(unsigned int x, int bits);
int Rotate(unsigned int rotatee, int amount);
int condtype(unsigned int instr);
int appendresult(int pos, char * result, unsigned int temp,int last);
int opcode(char *decodeStr, unsigned int instr, int pos);
int getop1(char *decodeStr, unsigned int instr, int pos, int type);
int getop2(char *decodeStr, unsigned int instr, int pos, int type);
int getshift(unsigned int shift);
int printshift(char *decodeStr,int pos, int type);
int getdestination(char *decodeStr, unsigned int instr, int pos,int type);
int getconditioncode(unsigned int instr);
int getsuffix( int pos,char *decodeStr, unsigned int instr);
void DecodeInstruction(unsigned int instr, char *decodeStr)
{   
    unsigned int first,second,third,fourth,fifth,sixth,offset,p,I,U,L,B,A,S,high,low,P,i,op,count;
    int pos=0,type=condtype(instr);
    char buffer[50][20];
    /*printf("Type:%d\n",type);*/
    
    
    if (type==1){/*swi 1 EF000001 */
        pos+=sprintf(decodeStr+pos,"%s","SWI ");
        first=(instr & 0x00F00000)>>20;
        pos=appendresult(pos,decodeStr,first,0);
        second=(instr & 0x000F0000)>>16;
        pos=appendresult(pos,decodeStr,second,0);
        third=(instr & 0x0000F000)>>12;
        pos=appendresult(pos,decodeStr,third,0);
        fourth=(instr & 0x00000F00)>>8;
        pos=appendresult(pos,decodeStr,fourth,0);
        fifth=(instr & 0x000000F0)>>4;
        pos=appendresult(pos,decodeStr,fifth,0);
        sixth=(instr & 0x0000000F);
        pos=appendresult(pos,decodeStr,sixth,1);
    }
    
    else if ((type==2)||(type==7)||(type==8)){/*offest shift left 2 bit, sign extended, added to PC*/
        /*if (type==7){NE
            pos+=sprintf(decodeStr+pos,"%s","BNE ");
        }
        else if(type==8){LT
            pos+=sprintf(decodeStr+pos,"%s","BLT ");
        }
        else{
            pos+=sprintf(decodeStr+pos,"%s","B ");
        }*/
  
        pos+=sprintf(decodeStr+pos,"%s","B");
        pos=getsuffix(pos,decodeStr,instr);
        offset=(instr & 0x00FFFFFF)<<2;
        
        offset=SignExtend(offset,26);
        pos+=sprintf(decodeStr+pos," %d",offset);
      
    }

    else if ((type==3)||(type==4)){/*register operand*/

        op=instr  << 7;
        op=(op & 0xF0000000);
        op=op >>28;
        pos=opcode(decodeStr,instr,pos);
        if (op==0xF||op==0xD){/*MVN or MOV*/
            pos=getdestination(decodeStr,instr,pos,type);
            pos=getop2(decodeStr,instr,pos,type);
        }
        else if(op==0xA||op==0xB||op==0x9||op==0x8){/*TEQ,TST,CMP,CMN*/
            pos=getop1(decodeStr,instr,pos,type);
            pos=getop2(decodeStr,instr,pos,type);
        }
        else{
            pos=getdestination(decodeStr,instr,pos,type);
            pos=getop1(decodeStr,instr,pos,type);
            pos=getop2(decodeStr,instr,pos,type);
        }
        

       /* condition=getconditioncode(instr);*/
        
    }
        
    else if ((type==5)){/*LOAD/STORE*/
        L=instr<<11;
        L=L>>31;
        B=instr<<9;
        B=B>>31;
        /*printf("L: %d\n", L);*/
        if(L==1){
            if (B==1){
                pos+=sprintf(decodeStr+pos,"%s ","LDRB");
            }
            else{
                pos+=sprintf(decodeStr+pos,"%s ","LDR");
            }
        }
        else{
            if (B==1){
                pos+=sprintf(decodeStr+pos,"%s ","STRB");
            }
            else{
                pos+=sprintf(decodeStr+pos,"%s ","STR");
            }
        }
        offset=instr << 21;
        offset=offset >>21;
        /*printf("offset: %d\n",offset);*/
        pos=getdestination(decodeStr,instr,pos,type);
        pos=getop1(decodeStr,instr,pos,type);
        p=instr<<7;
        p=p>>31;
        I=instr<<6;
        I=I>>31;
        
        if (offset==0||p==0){
            pos+=sprintf(decodeStr+pos,"%s","]");
        }
        if (offset!=0){
            if (I==1){
                pos+=sprintf(decodeStr+pos,", %s","R");
            }
            else{
                pos+=sprintf(decodeStr+pos,", %s","#");
            }
            U=instr<<8;
            U=U>>31;
            if(U==0){
                    pos+=sprintf(decodeStr+pos,"%s","-");
                    offset=SignExtend(offset,12);
            }
            
            pos+=sprintf(decodeStr+pos,"%d",offset);
            if(p==1){
                pos+=sprintf(decodeStr+pos,"%s","]");
            }




        }
        U=instr<<10;
        U=U>>31;
        if(U==1){
            pos+=sprintf(decodeStr+pos,"%s","!");
        }
    
    }

    else if(type==6){/*MUL/MLA*/
        A=instr<<10;
        A=A>>31;
        S=instr<<12;
        S=S>>28;
        /*S=instr<<9;
        A=A>>31;*/
        if(A==1){/*accumulate*/
            pos+=sprintf(decodeStr+pos,"%s","MLA ");
            pos+=sprintf(decodeStr+pos,"%s","R");
            pos+=sprintf(decodeStr+pos,"%d, ",S);
            S=instr<<28;
            S=S>>28;
            pos+=sprintf(decodeStr+pos,"%s","R");
            pos+=sprintf(decodeStr+pos,"%d, ",S);
            S=instr<<20;
            S=S>>28;
            pos+=sprintf(decodeStr+pos,"%s","R");
            pos+=sprintf(decodeStr+pos,"%d, ",S);
            S=instr<<16;
            S=S>>28;
            pos+=sprintf(decodeStr+pos,"%s","R");
            pos+=sprintf(decodeStr+pos,"%d",S);


            
        }
        else{
            pos+=sprintf(decodeStr+pos,"%s","MUL ");
            pos+=sprintf(decodeStr+pos,"%s","R");
            pos+=sprintf(decodeStr+pos,"%d, ",S);
            S=instr<<28;
            S=S>>28;
            pos+=sprintf(decodeStr+pos,"%s","R");
            pos+=sprintf(decodeStr+pos,"%d, ",S);
            S=instr<<20;
            S=S>>28;
            pos+=sprintf(decodeStr+pos,"%s","R");
            pos+=sprintf(decodeStr+pos,"%d",S);

        }
    }
    else if(type==9){
        U=instr<<8;
        U=U>>31;
        if (U==1){
            L=instr<<11;
            L=L>>31;
            /*printf("L: %d\n",L);*/
            if(L==1){
               pos+=sprintf(decodeStr+pos,"%s","LDMIA "); 
            }
            else{
                pos+=sprintf(decodeStr+pos,"%s","STMIB ");
            }
        }
        else{
            pos+=sprintf(decodeStr+pos,"%s","LDMDA "); 
        }
        U=instr<<12;
        U=U>>28;
        pos+=sprintf(decodeStr+pos,"%s","R"); 
        
        I=instr<<10;
        I=I>>31;
        if (I==1){
            pos+=sprintf(decodeStr+pos,"%d!, ",U);
        }
        else{
            pos+=sprintf(decodeStr+pos,"%d, ",U); 
        }
        U=instr<<16;
        low=-1;
        high=0;
        pos+=sprintf(decodeStr+pos,"%s","{");
        first=0;
        count=0;
        

        for (i=0;i<=15;i++){
            /*count=i;*/
            P=U>>31;
            /*printf("i:%d\n",i);*/
            if (P==1){
                
                if (low==-1){/*starting a new range?*/
                    low=15-i;
                }
                high=15-i;/*i is the highest value*/
                
            }
            else if (P==0){
                if (low!=-1){
                    /*if (first==1){
                        pos+=sprintf(decodeStr+pos,"%s",",");
                    }*/
                    if (low==high){
                        sprintf(buffer[count],"R%d",low);
                        count++;
                        /*pos+=sprintf(decodeStr+pos,"R%d",high);*/
                    }
                    else{
                        sprintf(buffer[count],"R%d-R%d",high,low);
                        count++;
                        /*pos+=sprintf(decodeStr+pos,"R%d-R%d",high,low);*/
                    }
                    
                    
                    low=-1;
                   high=-1;
                }

            }
            U=U<<1;
        
        }
        if (low!=-1){
            /*if (first==1){
                    pos+=sprintf(decodeStr+pos,"%s",",");
                }*/
            if (low==high){
                sprintf(buffer[count],"R%d",low);
                count++;
                /*pos+=sprintf(decodeStr+pos,"R%d",low);*/
            }
            else{
                sprintf(buffer[count],"R%d-R%d",high,low);
                count++;
                /*pos+=sprintf(decodeStr+pos,"R%d-R%d",low,high);*/
            }
        }
        for(i=count-1;i>0;i--)
        {
            if(first==1){
                pos+=sprintf(decodeStr+pos,"%s",",");
            }
            pos+=sprintf(decodeStr+pos,"%s",buffer[i]);
            first=1;
        }
        /*P=U>>31; */
        if (first==1){
            pos+=sprintf(decodeStr+pos,"%s",",");
        } 
        pos+=sprintf(decodeStr+pos,"%s",buffer[0]);    
        pos+=sprintf(decodeStr+pos,"%s","}");
       
    }

}

int getsuffix( int pos,char *decodeStr, unsigned int instr)
{
    unsigned int suffix,link;
    link=instr << 7;
    link=link>>31;
    if (link==1){
        pos+=sprintf(decodeStr+pos,"%s","L");
    }
    suffix=(instr & 0xF0000000) >> 28;
    switch (suffix){
        case (0x0):
            pos+=sprintf(decodeStr+pos,"%s","EQ");
            break;
        case (0x1):
            pos+=sprintf(decodeStr+pos,"%s","NE");
            break;
        case (0x2):
            pos+=sprintf(decodeStr+pos,"%s","CS");
            break;
        case (0x3):
            pos+=sprintf(decodeStr+pos,"%s","CC");
            break;
        case (0x4):
            pos+=sprintf(decodeStr+pos,"%s","MI");
            break;
        case (0x5):
            pos+=sprintf(decodeStr+pos,"%s","PL");
            break;
        case (0x6):
            pos+=sprintf(decodeStr+pos,"%s","VS");
            break;
        case (0x7):
            pos+=sprintf(decodeStr+pos,"%s","VC");
            break;
        case (0x8):
            pos+=sprintf(decodeStr+pos,"%s","HI");
            break;
        case (0x9):
            pos+=sprintf(decodeStr+pos,"%s","LS");
            break;
        case (0xA):
            pos+=sprintf(decodeStr+pos,"%s","GE");
            break;
        case (0xB):
            pos+=sprintf(decodeStr+pos,"%s","LT");
            break;
        case (0xC):
            pos+=sprintf(decodeStr+pos,"%s","GT");
            break;
        case (0xD):
            pos+=sprintf(decodeStr+pos,"%s","LE");
        break;
        case (0xE):
            break;
    }
    
    return pos;
}

int condtype(unsigned int instr)
{   /*swi=1,branch=2, processing=3,immediate=4,load/str=5, multiply=6*/
    unsigned int cond, penult;
    int type=0;
    cond=(instr & 0xFF000000) >> 24;
    /*printf("hello\n");*/

    if (cond==0xEF){/*swi: 1110*/
        type=1;
    }
    /*else if ((cond==0xEB)||(cond==0xEA)){branch 1010 or branch with link 1011
        type=2;
    }
    else if (cond==0xBA){BLT
        type=8;
    }
    else if (cond==0x1A){BNE
        type=7;
        
    }*/
    else if ((cond==0xE1)||(cond==0xE0)){/*operand 2 is register value 0000 or 0001*/
        cond=instr<<4;
        cond=cond>>26;
        penult=(instr & 0x000000F0);
        if ((cond==0)&&(penult==0x00000090))/*multiply*/
        {
            /*printf("Type 6");*/
            type=6;
        }
        else
        {
            type=3;
        }
    }
    else if ((cond==0xE3)||(cond==0xE2)){/*operand 2 is immediate value 0011 or 0010*/
        type=4;
        
    }
    else if ((cond==0xE7)||(cond==0xE6)||(cond==0xE5)||(cond==0xE4)){/*0111=7 0101=5 0110=6 0100=4LOAD/STORE*/
        type=5;
        
    }
    else if ((cond==0xE8)||(cond==0xE9)){/*LDMA,LDMIA,STMIB*/
        type=9;
        /*printf("type 9");*/
        
    }
    else{
        type=2;
    }
    /*printf("Type: %d\n",type);*/
    
    return type;
}


int getconditioncode(unsigned int instr)
{
    unsigned int setcondition;
    setcondition=instr  << 11;
    setcondition=setcondition >>31;
    return setcondition;
}

int getop1(char *decodeStr, unsigned int instr, int pos, int type)
{
    unsigned int op1;

    op1=instr  << 12;


    op1=op1 >>28;
    if (type==5){
        pos+=sprintf(decodeStr+pos,"%s","[");
        pos+=sprintf(decodeStr+pos,"%s","R");
        pos+=sprintf(decodeStr+pos,"%d",op1);
    }
    else{
        pos+=sprintf(decodeStr+pos,"%s","R");
        pos+=sprintf(decodeStr+pos,"%d,",op1);
    }
    /*if (type==5){
        pos+=sprintf(decodeStr+pos,"%s","]");
    }*/
    return pos;
}

int getop2(char *decodeStr, unsigned int instr, int pos, int type)
{
    unsigned int op2, shifttype,rotate,immediate,opcode,amount,reg,im_or_reg,shift;

    op2=instr  << 20;
    im_or_reg=op2 <<7;
    im_or_reg=im_or_reg>>31;
    shift=(op2 & 0x0F000000);
    shifttype=getshift(shift); 

    if (type==4){/*op2 is immediate value*/
        /*printf("first\n");*/
        opcode=instr  << 7;
        opcode=(opcode & 0xF0000000);
        opcode=opcode >>28;
        op2=op2>>20;
     
        rotate=(op2>>8)&0xF;
        immediate=op2&0xFF;
        /*immediate=immediate<<24;*/
        /*ret=24-rotate;*/
        rotate=rotate*2;
        
        /*printf("Rotate: %u Immediate: %d\n",rotate,immediate);*/
        immediate=Rotate(immediate,rotate);
        /*printf("Rotate: %u Immediate: %d\n",rotate,immediate);*/
        immediate&=0xFFFFFFFF;/*immediate>>24;*/
       /* printf("Rotate: %u Immediate: %d\n",rotate,immediate);*/
        pos+=sprintf(decodeStr+pos,"%s","#");
        pos+=sprintf(decodeStr+pos,"%d ",immediate);
    }
    if (type==3){/*register, shift reg value*/
        /*printf("sec\n");*/
        reg=(op2 & 0x00F00000);
        reg=reg<<8;
        reg=reg>>28;
        pos+=sprintf(decodeStr+pos,"%s","R");
        pos+=sprintf(decodeStr+pos,"%d",reg);
        amount=(op2 & 0xF0000000);
        amount=amount>>28;

        if (amount>0){
            if (im_or_reg==1&&shifttype!=0){
                pos=printshift(decodeStr,pos,shifttype); 
                pos+=sprintf(decodeStr+pos,"%s","R");
                pos+=sprintf(decodeStr+pos,"%d",amount); 
            }
            else if (im_or_reg==0&&shifttype!=0){
                amount=(op2 & 0xFF000000);
                amount=amount>>27;
                pos=printshift(decodeStr,pos,shifttype); 
                pos+=sprintf(decodeStr+pos,"%s","#");
                pos+=sprintf(decodeStr+pos,"%d",amount); 
            }
        }

       
    }
    

    return pos;
}



int printshift(char *decodeStr, int pos, int type)
{
    if (type==1){
          
            pos+=sprintf(decodeStr+pos,"%s"," LSL ");
        }
    else if(type==2){
            
            pos+=sprintf(decodeStr+pos,"%s"," LSR ");
        }
    else if(type==3){
            pos+=sprintf(decodeStr+pos,"%s"," ASR ");
        }
    else if(type==4){
          
            pos+=sprintf(decodeStr+pos,"%s"," ROR ");
        }

    return pos;
}
int getshift(unsigned int shift)
{
    int type=0;
    if (shift==0x01000000||shift==0x00000000){
        type=1;/*LSL*/
       
    }
    else if(shift==0x03000000||shift==0x02000000){
        type=2;/*LSR*/
        
    }
    else if(shift==0x05000000||shift==0x04000000){
        type=3;/*ASR*/
        
    }
    else if(shift==0x07000000||shift==0x06000000){
        type=4;/*ROR*/
        
    }
    
    return type;

}
int getdestination(char *decodeStr, unsigned int instr, int pos,int type)
{
    unsigned int destination;

    destination=instr  << 16;


    /*op1=(op1 & 0xF0000000);
    printf("%u\n",op1);*/
    destination=destination >>28;

    pos+=sprintf(decodeStr+pos,"%s","R");
    if (type!=6){
        pos+=sprintf(decodeStr+pos,"%d,",destination);
    }
    else{
        pos+=sprintf(decodeStr+pos,"%d",destination);
    }
    return pos;
}
int opcode(char *decodeStr, unsigned int instr, int pos){
    unsigned int opcode;
    /*printf("Initial: %u\n",instr);*/
    opcode=instr  << 7;
    /*printf("Opcode shift: %u\n",opcode);*/
    opcode=(opcode & 0xF0000000);
    /*printf("Opcode and: %u\n",opcode);*/
    opcode=opcode >>28;
    /*printf("Opcode: %u\n",opcode);*/
    if (opcode==0x0){
            pos+=sprintf(decodeStr+pos,"%s","AND ");
        }
    else if (opcode==0x1){
            pos+=sprintf(decodeStr+pos,"%s","EOR ");
        }
    else if (opcode==0x2){
            pos+=sprintf(decodeStr+pos,"%s","SUB ");
        }
    else if (opcode==0x3){
            pos+=sprintf(decodeStr+pos,"%s","RSB ");
        }
    else if (opcode==0x4){
            pos+=sprintf(decodeStr+pos,"%s","ADD ");
        }
    else if (opcode==0x5){
            pos+=sprintf(decodeStr+pos,"%s","ADC ");
        }
    else if (opcode==0x6){
            pos+=sprintf(decodeStr+pos,"%s","SBC ");
        }
    else if (opcode==0x7){
            pos+=sprintf(decodeStr+pos,"%s","RSC ");
        }
    else if (opcode==0x8){
            pos+=sprintf(decodeStr+pos,"%s","TST ");
        }
    else if (opcode==0x9){
            pos+=sprintf(decodeStr+pos,"%s","TEQ ");
        }
    else if (opcode==0xA){
            pos+=sprintf(decodeStr+pos,"%s","CMP ");
        }
    else if (opcode==0xB){
            pos+=sprintf(decodeStr+pos,"%s","CMN ");
        }
    else if (opcode==0xC){
            pos+=sprintf(decodeStr+pos,"%s","ORR ");
        }
    else if (opcode==0xD){
            pos+=sprintf(decodeStr+pos,"%s","MOV ");
            
        }
    else if (opcode==0xE){
            pos+=sprintf(decodeStr+pos,"%s","BIC ");
        }
    else if (opcode==0xF){
            pos+=sprintf(decodeStr+pos,"%s","MVN ");
            
        }
    return pos;
}

int appendresult(int pos, char * result, unsigned int temp, int last)
{
    char hex;
    if (temp==0x0&&last==0){
        return pos;
    }
    else if (temp>=10){
        temp=temp-10;
        hex='A'+temp;
        pos+=sprintf(result+pos,"%c",hex);
        return pos;

    }
    else{
        pos+=sprintf(result+pos,"%u",temp);
    }
    return pos;
}



int SignExtend(unsigned int x, int bits)
{
    int r;
    int m = 1U << (bits - 1);
    
    x = x & ((1U << bits) - 1);
    r = (x ^ m) - m;
    return r;
}
               
int Rotate(unsigned int rotatee, int amount)
{
    unsigned int mask, lo, hi;

    mask = (1 << amount) - 1;
    lo = rotatee & mask;
    hi = rotatee >> amount;

    rotatee = (lo << (32 - amount)) | hi;
    
    return rotatee;
}

               
        

