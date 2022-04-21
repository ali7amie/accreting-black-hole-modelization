#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"dvector.h"

 

dvector f(dvector u ){
    dvector y(2);
    y[0]=u[1];
    y[1]=3.0*u[0]*u[0]/2-u[0];
    return y;
   
}
dvector RK4 ( dvector y, double h) {
    dvector k1=h*f(y);
    dvector k2=h*f(y+0.5*k1);
    dvector k3=h*f(y+0.5*k2);
    dvector k4=h*f(y+k3);
    return y+(k1+2*k2+2*k3+k4)/6;
}
  int main(){
    //fichier de valeurs de u
    FILE *fp;
    fp=fopen("fichier1", "w");
   

   
    //déclaration de variable :
    double a,b;
    int n;
            //Saisir
              printf ("saisir les bornes theta0,thetaf le nombre de pas n  \n");
              scanf("%lf %lf %d ",&a,&b,&n);
    int i;
    double theta=a;
    double h=(b-a)/n;
    double x;
    double z;
   
    double uc=1.5;
   
    dvector y(2);
    //conditions initials
    y[0]=0.0;      
    y[1]=sqrt(4.0/27)*uc;
   
    for(i=1;i<=n;i++){
        y=RK4(y,h);
        x=cos(theta)/y[0];
        z=sin(theta)/y[0];
        theta+=h;
        fprintf(fp,"%lf\t %lf\t %lf\n",theta,x,z);
        }
   
       
  }
