#include <iostream>
#include <math.h>
using namespace std;

double f(double x);
double df(double x);
double *createarray(int n);
double sepdif11(int i,int j,double *P, double*F, double *D);
double sepdif21(int i,int j,double *P, double*F, double *D);
double sepdif22(int i,int j,double *P, double*F, double *D);
double sepdif12(int i,int j,double *P, double*F, double *D);
double hermitint(double x, int n, double *P, double *F, double *D);

int main()
{
    double x;
    cin>>x;
    int n;
    cin>>n;
    double *P=createarray(n);
    double *F=createarray(n);
    double *D=createarray(n);
    for(int i=0;i<n;i++){
       // double a,b,c;
        // cin>>a>>b>>c;
        double a;
        cin>>a;
        P[i]=a;
        F[i]=f(a);
        D[i]=df(a);
    }
    cout<<endl;
    double k;
    k=hermitint(x,n,P,F,D);
    free(P);
            free(D);
            free(F);
    cout<<k;
    cout<<endl;
    cout<<f(x);
    return 0;
}

double f(double x){
    return x*x*x*x*x*x*x*x+9*x+1;
}

double df(double x){
    return 8*x*x*x*x*x*x*x+9;
}

double *createarray(int n){
    double *A=(double*)(malloc(n*sizeof(double)));
    return A;
}

double sepdif11(int i,int j,double *P, double*F, double *D){
    if(j-i==1){
        return (F[j]-F[i])/(P[j]-P[i]);
    }else{
        return (sepdif21(i+1,j,P,F,D)-sepdif12(i,j-1,P,F,D))/(P[j]-P[i]);
    }
}

double sepdif21(int i,int j,double *P, double*F, double *D){
    if(j-i==1){
        return (sepdif11(i,j,P,F,D)-D[i])/(P[j]-P[i]);
    }else{
        return (sepdif11(i,j,P,F,D)-sepdif22(i,j-1,P,F,D))/(P[j]-P[i]);
    }
}

double sepdif12(int i,int j,double *P, double*F, double *D){
    if(j-i==1){
        return (D[j]-sepdif11(i,j,P,F,D))/(P[j]-P[i]);
    }else{
        return (sepdif22(i+1,j,P,F,D)-sepdif11(i,j,P,F,D))/(P[j]-P[i]);
    }
}

double sepdif22(int i,int j,double *P, double*F, double *D){
    if(j-i==1){
        return (sepdif12(i,j,P,F,D)-sepdif21(i,j,P,F,D))/(P[j]-P[i]);
    }else{
        return (sepdif12(i,j,P,F,D)-sepdif21(i,j,P,F,D))/(P[j]-P[i]);
    }
}

double hermitint(double x, int n, double *P, double *F, double *D){
    double res,s1,s2,p1,p2;
    p1=1;
    p2=x-P[0];
    res=F[0]+D[0]*(x-P[0]);
    cout<<f(P[0])<<" "<<df(P[0])<<" "<<res<<endl;
    for(int i=1;i<n;i++){
            p2=p2*(x-P[i-1])*(x-P[i]);
            p1=p1*(x-P[i-1])*(x-P[i-1]);
            s1=sepdif21(0,i,P,F,D)*p1;
            s2=sepdif22(0,i,P,F,D)*p2;
            res=res+s1+s2;
            cout<<f(P[i])<<" "<<df(P[i])<<" "<<" "<<s1<<" "<<s2<<" "<<res<<endl;
    }
    return res;
}
