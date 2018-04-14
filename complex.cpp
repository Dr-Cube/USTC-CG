#include "complex.h"
#include <math.h>

idComplex::idComplex(double r,double i){
    m_real=r;
    m_image=i;
}

idComplex::idComplex()
{
    m_real=0.0f;
    m_image=0.0f;
}

idComplex::~idComplex()
{

}

idComplex idComplex::SetValue(double re, double im)
{
    m_image=im;
    m_real=re;
    return *this;

}

idComplex idComplex::operator +(idComplex c)
{
    idComplex c1(0,0);
    c1.m_real=m_real+c.m_real;
    c1.m_image=m_image+c.m_image;
    return c1;
}

idComplex idComplex::operator -(idComplex c)
{
    idComplex c1(0,0);
    c1.m_real=m_real-c.m_real;
    c1.m_image=m_image-c.m_image;
    return c1;

}

idComplex idComplex::operator *(idComplex c)
{
    idComplex c1(0,0);
    c1.m_real=m_real*c.m_real-m_image*c.m_image;
    c1.m_image=m_image*c.m_real+m_real*c.m_image;
    return c1;
}
idComplex idComplex::operator += (idComplex c)
{
    m_real+=c.m_real;
    m_image+=c.m_image;
    return *this;
}

idComplex idComplex::operator -= (idComplex c)
{
    m_real-=c.m_real;
    m_image-=c.m_image;
    return *this;
}

idComplex idComplex::operator *= ( idComplex c )
{
    double a=m_real,b=m_image,m=c.m_real,n=c.m_image;
    m_real=a*m-b*n;
    m_image=b*m+a*n;
    return *this;
}

double idComplex::Operatmod()
{
    return sqrt(m_real*m_real+m_image*m_image);
}
