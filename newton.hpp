#ifndef NEWTON_H
#define NEWTON_H

#include <QObject>
#include <QString>
#include <QStringList>

#include "Interval.h"
#include "Number.h"
typedef int (*myFuncDef)(int, int);
typedef ean::Number<long double> (*nPointer)(ean::Number<long double>);
typedef ean::Interval (*iPointer)(ean::Interval);

class Newton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(QString x2 READ x2 WRITE setX2 NOTIFY x2Changed)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QStringList types READ types NOTIFY typesChanged)
    Q_PROPERTY(QString mit READ mit WRITE setMit NOTIFY mitChanged)
    Q_PROPERTY(QString eps READ eps WRITE setEps NOTIFY epsChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(QString mfunction READ mfunction WRITE setMfunction NOTIFY mfunctionChanged)
    Q_PROPERTY(QString mdfunction READ mdfunction WRITE setMdfunction NOTIFY mdfunctionChanged)

public:
    Newton();
    ~Newton();

    QString x();
    void setX(const QString &t);

    QString x2();
    void setX2(const QString &t);

    QString type();
    void setType(const QString &t);

    QStringList types();

    QString mit();
    void setMit(const QString &t);

    QString eps();
    void setEps(const QString &t);

    QString filename();
    void setFilename(const QString &f);

    QString mfunction();
    void setMfunction(const QString &p);

    QString mdfunction();
    void setMdfunction(const QString &p);


template <typename T,typename T2>
T calculate(T2 function,T2 dfunction,T x,int mit,long double eps,int & i,int &state,T &fx);

    //long double calculate(MyPrototype funtion,MyPrototype dfuntion,long double x,int mit,long double eps,int & i,int &state,long double & fx);

    //long double calculateInterval(MyPrototype function,MyPrototype dfunction,ean::Interval x,int mit,double eps,int & i,int &state,double &fx,double &fx2);
public slots:
    void generateResult(QString x,QString mit,QString eps);

signals:
    void xChanged();
    void x2Changed();
    void typeChanged();
    void typesChanged();
    void mitChanged();
    void epsChanged();
    void filenameChanged();
    void mfunctionChanged();
    void mdfunctionChanged();
    void resultGenerated(bool success,QString state,QString result,QString width,QString fx,QString i);

private:
    QString _x;
    QString _x2;
    QString _type;
    QStringList _types;
    QString _mit;
    QString _eps;
    QString _filename;
    QString _mfunction;
    QString _mdfunction;
};
#endif

