#ifndef A_H
#define A_H

#include <QObject>
#include <QtTest/QtTest>

class A : public QObject
{
    Q_OBJECT
private slots:
    void lev1();
    void lev2();
};

#endif // A_H
