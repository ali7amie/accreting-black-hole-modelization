#include <stdio.h>
#include<math.h>
#include<stdlib.h>


double f(double u){
    double uc;
  return 4*uc/27-u*u+u*u*u ;
}

int main() {
  FILE *fp;
  fp=fopen("fichier","w");
  int n;
  double uc;
  printf("saisir uc:");
  scanf("%lf",&uc);
  printf("saisir nombre de point n:");
  scanf("%lf",&n);
  int i;
  for (i=0;i<n;i++){
    fprintf(fp,"%d \t %lf\n",i,f(i)); 
  }
}

