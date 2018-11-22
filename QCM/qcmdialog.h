#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QDebug>
#include "qcm.h"

#include <QtGui>
#include <QObject>
#include <QPushButton>
#include <QtWidgets>

#define EXAMEN_TAILLE 2

class QCMDialog : public QDialog
{

    Q_OBJECT

private:
    QLabel *question, *txt_affichage_question_score;
    QPushButton *bValider, *bContinuer, *bQuitter;

    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout, *rightLayout, *boxLayout, *inside_box;

    QGroupBox *group;
    QGroupBox *newBox, *newBox2;

    Examen examen;

public:
    int num_reponses;
    QCMDialog();
    QCMDialog(const Examen& examen, QDialog *parent = 0);
    ~QCMDialog();


private slots:
/* les slots validerClicked, continuerClicked et enableValiderButton */
    void validerClicked(int checked_ans, const Examen& examen);
    void continuerClicked(const Examen& examen);
    void enableValiderButton(bool checked);

    void quitterClicked();
};
#endif
