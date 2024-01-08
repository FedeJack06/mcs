#ifndef _COMPLEX
#define _COMPLEX

#include <iostream>
#include <TVector2.h>
#include <string>
#include<cmath>

class Complex : public TVector2{
    public:
    using TVector2::TVector2;
    
    Complex(double re,double im):TVector2(re,im){
        m_re = re;
        m_im = im;
    };

    Complex(TVector2 k):TVector2(k.X(), k.Y()) {
        m_re = k.X();
        m_im = k.Y();
    };

    Complex coniugato(){
        Complex k(this->X(), 0-this->Y());
        return k;
    }

    Complex operator*(Complex z2){ 
        Complex res; 
        res.SetX((this->X())*z2.X()- (this->Y())*z2.Y()); 
        res.SetY((this->X())*z2.Y()+(this->Y())*z2.X()); 
        return res;
    }

    private:
        double m_re = 0;
        double m_im = 0;

};

std::ostream& operator<<(std::ostream& o, Complex z){
    // const char k = (char)z.Y();
    // const char *c = &k;
    // o << z.X() <<  "+(" << z.Y()  << ")i" << std::endl;
    o << (z.X()==0?"":std::to_string(z.X())) << (z.Y()<0?" - ":" + ") << (z.Y()==0?"":std::to_string(std::sqrt(std::pow(z.Y(),2)))) << (z.Y()==0?"":"j");
    return o;
    
};

#endif