#include <random>
#include <iostream>
#include <fstream>

double force(double x){
  const double sigma=0.4;
  const double k=1/(sigma*sigma);
  const double e1=std::exp(-0.5*k*x*x);
  const double e2=std::exp(-0.5*k*(x-3)*(x-3));
  return -(k*x*e1+k*(x-3)*e2)/(e1+e2);
}

int main(){
  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0,1.0);

  const double dt=0.01;
  const double D=1;
  const double T=1;


  const double xref=1;
  const int stride=100;
  const int nsteps=10000000;


  {
    const double kappa=0.1;
    const double tau=100.0;
    double lambda=0;
    double x=3;
    std::ofstream of("out");
    for(unsigned i=0;i<nsteps;i++){
      auto f=force(x)+lambda*T;
      x+=D/T*f*dt+std::sqrt(2*D*dt)*distribution(generator);
      lambda+= kappa*dt/(1+i*dt/tau) * (xref-x);
      if(i%stride==0) of<<i*dt<<" "<<x<<" "<<lambda<<"\n";
    }
  }

  return 0;
}
