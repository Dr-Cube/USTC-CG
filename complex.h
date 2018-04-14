#ifndef COMPLEX_H
#define COMPLEX_H

//构建复数类
class idComplex{
public:
    idComplex(double r,double i);
    idComplex();
    ~idComplex();
    idComplex SetValue(double re,double im);

    idComplex operator + (idComplex c);
    idComplex operator - (idComplex c);
    idComplex operator * (idComplex c);

    idComplex operator += ( idComplex c );
    idComplex operator -= ( idComplex c );
    idComplex operator *= ( idComplex c );
    double Operatmod();
    void DisplayComplex();
private:
    double  m_real;
    double  m_image;

};
#endif // COMPLEX_H
