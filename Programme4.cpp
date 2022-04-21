#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"dvector.h"

double angd(double a,double i){
  double ci=cos(i)*cos(i);
  double ca=cos(a)*cos(a);
  return acos((-sin(a)*cos(i))/sqrt(1-ci*ca));
}

dvector f(dvector u ){
    dvector U(2);
    U[0]=u[1];
    U[1]=3*u[0]*u[0]/2-u[0];
    return U;
    
}
dvector RK4 ( dvector U, double h) {
    dvector k1=h*f(U);
    dvector k2=h*f(U+0.5*k1);
    dvector k3=h*f(U+0.5*k2);
    dvector k4=h*f(U+k3);
    return U+(k1+2*k2+2*k3+k4)/6;
}
double calculaterayon(dvector U,double alpha,double j,double uc,double h){
    U[0]=0.0;
    U[1]=sqrt(U[0]*U[0]*U[0]-U[0]*U[0]+(4.0/27)*uc*uc);
    double theta=0;
    //printf("%lf \n",angd(alpha,j));
    while (theta<=angd(alpha,j)){ 
                   U=RK4(U,h);
                   theta+=h;
              }
    return 1./U[0];
    
} 



  int main(){
    //fichier de valeurs de u
    FILE *fp;
    fp=fopen("fichier1", "w");
    
    FILE *fp2;
    fp2=fopen("fichier2", "w");

    FILE *fp3;
    fp3=fopen("fichier3", "w");
    
    FILE *fp4;
    fp4=fopen("fichier4", "w");
    
    //déclaration de variable :
    double xy0,xyf;
    int n;
    double j;
            //Saisir :
              printf ("saisir les bornes xy0,xyf ,le nombre de pas n,j inclinaison de disque d'accrétion \n");
              scanf("%lf %lf %d %lf",&xy0,&xyf,&n,&j);
    double h=(xyf-xy0)/n;
    double bc=1;
    double b;
    double x;
    double xQ;
    double z;
    double y;
    double Fe;
    double Fobs;
    double alpha;
    double r;
    double r2;
    double rs=0.385;
    dvector U(2);
    
    for(x=0;x<=xyf;x+=h){//boucle sur x avec optimisation on ne calcule que pour la moitie du plan
        for(y=xy0;y<=xyf;y+=h){//boucle sur y
            alpha=atan2(y,x);
            b=sqrt(x*x+y*y);
            r=calculaterayon(U,alpha,j,bc/b,h);
            r2=b/sin(angd(alpha,j));
            xQ=r/(3.*rs);
            
            z=-1+(1./sqrt(1-1./(2*xQ)))*(1+sqrt(2.*xQ*2.*xQ*2.*xQ)*(b/bc)*cos(j)*cos(alpha));
            
            Fe=(1./(xQ*xQ*xQ-xQ*xQ/2.))*(1-1.0/sqrt(xQ)+log((sqrt(2.*xQ)+sqrt(2)-1)/(sqrt(2.0*xQ)-sqrt(2)+1))*sqrt(1./(8*xQ)));
            
            Fobs=Fe/((1+z)*(1+z)*(1+z)*(1+z));
            
            fprintf(fp,"%lf \t %lf \t %lf \t %lf \n",x,y,r,alpha);
            fprintf(fp2,"%lf \t %lf \t %lf \t %lf \n",x,y,r2,alpha); 
            fprintf(fp3,"%lf \t %lf \t %lf \t %lf \n",x,y,z,alpha);
            fprintf(fp4,"%lf \t %lf \t %lg \t %lf \n",x,y,Fobs,alpha); 
        }
        
        fprintf(fp,"\n");
        fprintf(fp2,"\n");
        fprintf(fp3,"\n");
        fprintf(fp4,"\n");
        
    }
   
  }
  

