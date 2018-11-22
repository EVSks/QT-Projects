#ifndef QCM_H
#define QCM_H

#define NB_QUESTIONS_TOTAL 2

#include <QDebug>

#include <iostream>
#include <QString>
#include <vector>
using namespace std;

struct QCM
{
    QString question;
    vector<QString> reponses;
    unsigned int solution;
    unsigned int point;
    unsigned int nb_reponses;
};

typedef vector<QCM> Examen;

Examen creer_examen();


#endif // QCM_H
