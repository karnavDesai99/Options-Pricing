#include<iostream>
#include<cstdlib>
#include<math.h>
#include<ctime>
using namespace std;

class BSMC
{
    float asset, strike, growth, vol, yrs;
    long steps, sims;
    double callPrice, putPrice;
public:
    BSMC(float,float,float,float,float,long,long);
    float getAsset();
    float getStrike();
    float getGrowth();
    float getVolatility();
    float getYears();
    long getSteps();
    long getSims();
    void logNormalRandomWalk();
    double getCallPrice();
    double getPutPrice();
    float generate_phi();
};

BSMC::BSMC(float ast,float strk,float grwth,float volt,float y,long stps,long s)
{
    asset=ast; strike=strk; growth=grwth; vol=volt;
    yrs=y; steps=stps; sims=s;
}

void BSMC::logNormalRandomWalk()
{
    srand(static_cast<unsigned>(time(0)));
    double callPayoff, putPayoff;
    double time_step=getYears()/getSteps();
    double sqrt_ts=sqrt(time_step);
    for(long i=1;i<=getSims();i++)
    {
        float ast=getAsset();
        for(int j=1;j<=getSteps();j++)
        {
            ast*=(1+getGrowth()*time_step+getVolatility()+sqrt_ts*(
                                generate_phi()+generate_phi()+generate_phi()+
                                generate_phi()+generate_phi()+generate_phi()+
                                generate_phi()+generate_phi()+generate_phi()+
                                generate_phi()+generate_phi()+generate_phi()-6 ));
        }
        if(ast>getStrike())
            callPayoff+=ast-getStrike();
        else if(ast<getStrike())
            putPayoff+=getStrike()-ast;
        callPrice=callPayoff/getSims();
        putPrice=putPayoff/getSims();
    }
    cout<<"Call option price: "<<getCallPrice()<<endl;
    cout<<"Put option price: "<<getPutPrice()<<endl;
    return;
}

float BSMC::generate_phi()
{
    return static_cast<float>(rand())/static_cast<float>(RAND_MAX);
}
float BSMC::getAsset() { return asset; }
float BSMC::getStrike() { return strike; }
float BSMC::getGrowth() { return growth; }
float BSMC::getVolatility() { return vol; }
float BSMC::getYears() { return yrs; }
long BSMC::getSteps() { return steps; }
long BSMC::getSims() { return sims; }
double BSMC::getCallPrice() { return callPrice; }
double BSMC::getPutPrice() { return putPrice; }


int main()
{
    float asset, strike, growth, vol, yrs;
    double steps, sims;
    cout<<"Enter price of underlying asset: "; cin>>asset;
    cout<<"Enter strike price: "; cin>>strike;
    cout<<"Enter growth (in decimal points): "; cin>>growth;
    cout<<"Enter volatility (in decimal points): "; cin>>vol;
    cout<<"Enter years: "; cin>>yrs;
    cout<<"Enter steps: "; cin>>steps;
    cout<<"Enter no. of simulations: "; cin>>sims;
    BSMC bsmc(asset,strike,growth,vol,yrs,steps,sims);
    bsmc.logNormalRandomWalk();
    cout<<endl;
    return 0;
}
