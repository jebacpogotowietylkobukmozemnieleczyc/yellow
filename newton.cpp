#include <QFile>
#include <QProcess>
#include "Newton.hpp"
#include "Number.h"
#include <iostream>
#include <QLibrary>
#include "conversion.h"
//test funtion
template <typename T>
T fun(T x)
{
    T m(2);
    return x*x-m;
}
template <typename T>
T dfun(T x)
{
    T m(2);
    return m*x;
}

template <typename T>
T fun2(T x)
{
    T m(0.5);
    return x.sin().get()*(m+x.sin().get())-m;
}
template <typename T>
T dfun2(T x)
{
    T m(2);
    T m2(0.5);
    return (x*m).sin().get()+m2*x.cos().get();
}

Newton::Newton()
    : _type("zmiennopozycyjna"), _types{"zmiennopozycyjna", "przedziałowa"}
{
}

Newton::~Newton()
{
}

QString Newton::type()
{
    return _type;
}

void Newton::setType(const QString &t)
{
    // Check for valid type.
    if (!_types.contains(t))
        return;

    if (t != _type) {
        _type = t;
        emit typeChanged();
    }
}

QStringList Newton::types()
{
    return _types;
}


QString Newton::x()
{
    return _x;
}

void Newton::setX(const QString &t)
{

    if (t != _x) {
        _x = t;
        emit xChanged();
    }
}

QString Newton::x2()
{
    return _x2;
}

void Newton::setX2(const QString &t)
{

    if (t != _x2) {
        _x2 = t;
        emit x2Changed();
    }
}


QString Newton::mit()
{
    return _mit;
}

void Newton::setMit(const QString &t)
{

    if (t != _mit) {
        _mit = t;
        emit mitChanged();
    }
}



QString Newton::eps()
{
    return _eps;
}

void Newton::setEps(const QString &t)
{

    if (t != _eps) {
        _eps = t;
        emit epsChanged();
    }
}

QString Newton::filename()
{
    return _filename;
}

void Newton::setFilename(const QString &f)
{
    if (f != _filename) {
        _filename = f;
        emit filenameChanged();
    }
}


QString Newton::mfunction()
{
    return _mfunction;
}

void Newton::setMfunction(const QString &p)
{
    if (p != _mfunction) {
        _mfunction = p;
        emit mfunctionChanged();
    }
}

QString Newton::mdfunction()
{
    return _mdfunction;
}

void Newton::setMdfunction(const QString &p)
{
    if (p != _mdfunction) {
        _mdfunction = p;
        emit mdfunctionChanged();
    }
}
template <typename T,typename T2>
T Newton::calculate(T2 function,T2 dfunction,T x,int mit,long double eps,int & i,int &state,T &fx){
state = 3;
for(i=1;i<=mit;i++){
    T df = dfunction(x);
    T zero(0);
    if(df==zero){
        state = 2;
        return zero;
    }
    fx = function(x);
    T nx=x-fx/df;
    T rx = nx -x;
    T test = rx.abs()/ std::max( nx.abs(),x.abs(), [](const T& a,const T& b){return a<b;});
    if(nx==zero || x==zero ||  test<eps ){
        state = 0;
        return nx;
    }
    x = nx;
}
return x;
}

/*
long double Newton::calculateInterval(MyPrototype function,MyPrototype dfunction,ean::Interval x,int mit,double eps,int & i,int &state,double &fx,double &fx2){
if(mit<0){
    state=1;
    return 0;
}

state = 3;
for(i=1;i<=mit;i++){
    double df = dfunction(x);

    if(df==0){
        state = 2;
        return 0;
    }
    fx = function(x);
    double nx=x-fx/df;
    double test = fabs(nx-x)/ std::max( fabs(nx),fabs(x) );

    if(nx==0 || x==0 ||  test<eps ){
        state = 0;
        return nx;
    }
    x = nx;
}
return x;
}


*/
/*
std::string showLD(long double val) {
    constexpr int BUFS = 64;
    char buf[BUFS];

    snprintf(buf, BUFS, "%.32LE", val);
    return std::string(buf);
}

long double readLD(std::string val) {
    long double buf;
    scanf(val.c_str(),"%Le",&buf);
    return buf;
}


        std::string ku_to_string(long double value)
        {
            std::ostringstream oss;
            oss << std::setprecision(32) << value;
            return oss.str();
        }
        */
void Newton::generateResult(QString x,QString mit,QString eps)
{
    //sprawdzanie poprawności danych
        std::cout << "lol" << std::endl;
        //pola puste
        if (_x.isEmpty() || _filename.isEmpty()|| _mfunction.isEmpty() || _mfunction.isEmpty() || _eps.isEmpty() || _mit.isEmpty() ) {
            emit resultGenerated(true,"4","0","0","0","0");
            return;
        }


    //deklaracja zmiennych
       int i=0;
       int state = 0;
       int imit = std::stoi(mit.toStdString());
       double deps = std::stod(eps.toStdString());
       QString qfx;
       QString qwidth;


        if (imit <1) {
            emit resultGenerated(true,"1","0","0","0","0");
            return;
        }
       //kalkulejt

           if(_type=="przedziałowa"){
    // wczytanie dll
       iPointer ip = &fun2<ean::Interval>;
       iPointer dip = &dfun2<ean::Interval>;
        if (ip==0 || dip ==0) {
            emit resultGenerated(true,"5","0","0","0","0");
            return;
        }
       ean::Interval fx(0);
                ean::Interval * interval ;
               if(_x2.isEmpty()){
                   ean::Interval ival(_x.toStdString());
                   interval = &ival;
               }
               else{
                   ean::Interval ival(IntervalArithmetic::LeftRead(_x.toStdString()),IntervalArithmetic::RightRead(_x2.toStdString()));
                   interval = &ival;
               }
                //*interval = ip(*interval);
                *interval  = calculate(ip,dip,*interval,imit,deps,i,state,fx);
                x = QString::fromStdString(interval->to_string());
                qfx = QString::fromStdString(fx.to_string());
                qwidth = QString::fromStdString(showLD<long double>(fx.getWidth()));
                if(*interval<deps)std::cout << "wietnam goodmorning";
           }
           else{
    // wczytanie dll
       nPointer np = &fun2<ean::Number<long double>>;
       nPointer dnp = &dfun2<ean::Number<long double>>;
       ean::Number<long double> fx(0);
        if (np==0 || dnp ==0) {
            emit resultGenerated(true,"5","0","0","0","0");
            return;
        }
                ean::Number<long double> number(x.toStdString());
                //number = np(number);
                number = calculate(np,dnp,number,imit,deps,i,state,fx);
                x = QString::fromStdString(number.to_string());
                qfx = QString::fromStdString(fx.to_string());
                qwidth = "0";
                if(number<deps)std::cout << "wietnam goodmorning";
           }

    //conversion
      QString qi = QString::fromStdString(showLD<int>(i));
      mit = QString::fromStdString(showLD<int>(imit));
      QString qstate = QString::fromStdString(showLD<int>(state));

     emit resultGenerated(true,qstate,x,qwidth,qfx,qi);
}

