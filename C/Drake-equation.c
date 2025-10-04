#include <stdio.h> /* importing library to be able to use printf */

int drake_equation(double R, double fp, int ne, double fl, double fi, double fc, int L);
int main(int argc, char **argv)
{
  int N;
  double R;
  double fp;
  int ne;
  double fl;
  double fi;
  double fc;
  int L;
  
  /*set 1*/
  R=1.0;
  fp=0.2;
  ne=1;
  fl=1.0;
  fi=1.0;
  fc=0.345;
  L=1000;
  N=drake_equation(R,fp,ne,fl,fi,fc,L);/*set 1*/
  printf("N=%d R*=%.2f fp=%.2f ne=%d fl=%.2f fi=%.2f fc=%.2f L=%d\n",N,R,fp,ne,fl,fi,fc,L);
  
  /*set 2 */
  R=1.0;
  fp=0.322;
  ne=5;
  fl=1.0;
  fi=1.0;
  fc=0.2;
  L=1000000000;
  N=drake_equation(R,fp,ne,fl,fi,fc,L);/*set 1*/
  printf("N=%d R*=%.2f fp=%.2f ne=%d fl=%.2f fi=%.2f fc=%.2f L=%d\n",N,R,fp,ne,fl,fi,fc,L);

  
  /*set 3*/
  R=1.5;
  fp=1.0;
  ne=3;
  fl=1.0;
  fi=0.003;
  fc=0.007;
  L=30500;
  N=drake_equation(R,fp,ne,fl,fi,fc,L);/*set 1*/
  printf("N=%d R*=%.2f fp=%.2f ne=%d fl=%.2f fi=%.2f fc=%.2f L=%d\n",N,R,fp,ne,fl,fi,fc,L);

  /*set 4*/
  R=3.0;
  fp=1.0;
  ne=5;
  fl=1.0;
  fi=1.0;
  fc=0.2;
  L=10000000;
  N=drake_equation(R,fp,ne,fl,fi,fc,L);/*set 1*/
  printf("N=%d R*=%.2f fp=%.2f ne=%d fl=%.2f fi=%.2f fc=%.2f L=%d\n",N,R,fp,ne,fl,fi,fc,L);
  
 

  return 0;
}

int drake_equation(double R, double fp, int ne, double fl, double fi, double fc, int L)
{
  int N;
  N=(R*fp*ne*fl*fi*fc*L);
  /*printf("\nN=%d R*=%.2f fp=%.2f ne=%d fl=%.2f fi=%.2f fc=%.2f L=%d\n",N,R,fp,ne,fl,fi,fc,L);*/
  return N;
}


