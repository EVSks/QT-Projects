#include <QtGui>
#include "qcmdialog.h"

int current_question = 0, score = 0, n_reponse_cochee = 0;

QGroupBox *groupe(int _question, const Examen &examen);

QString question_score;

void reponseSelectionee(int i);

void afficherMessage(int valid_or_not);



QCMDialog::QCMDialog(const Examen& examen, QDialog *parent) : QDialog(parent)
{

    this->setWindowTitle(tr("QCM version 1"));
    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    this->setFixedSize(500, 200);

    this->question = new QLabel;
    question->setText(examen[current_question].question);
    question->setFixedWidth(400);

    question_score = QString("* Question %1 / %2 \n* Score %3 / %4")
            .arg(current_question + 1)
            .arg(examen.size())
            .arg(score)
            .arg(examen.size());

    this->txt_affichage_question_score = new QLabel(question_score);

    this->bValider = new QPushButton("Valider");
    bValider->setDefault(true);
    enableValiderButton(true);

    this->bContinuer = new QPushButton("Continuer");
    this->bQuitter = new QPushButton("Quitter");

    bValider->setFixedWidth(150);
    bContinuer->setFixedWidth(150);
    bQuitter->setFixedWidth(150);

    bContinuer->setEnabled(false);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QVBoxLayout *boxLayout = new QVBoxLayout;

    rightLayout->addWidget(bValider);
    rightLayout->addWidget(bContinuer);
    rightLayout->addWidget(bQuitter);
    rightLayout->addWidget(txt_affichage_question_score);

    this->newBox = groupe(0, examen);
    this->newBox2 = groupe(1, examen);
    newBox2->hide();

    leftLayout->addWidget(question);
    leftLayout->addWidget(newBox);
    leftLayout->addWidget(newBox2);
    leftLayout->addLayout(boxLayout);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);

    connect(this->bValider, bValider->clicked, [=]() { this->validerClicked(0, examen); } );
    connect(this->bContinuer, bContinuer->clicked, [=]() { continuerClicked(examen); } );
    connect(this->bQuitter, SIGNAL(clicked()), this, SLOT(quitterClicked()));\


}

QCMDialog::~QCMDialog()
{

}


QGroupBox *groupe(int _question, const Examen& examen)
{

    QGroupBox *box = new QGroupBox;
    QVBoxLayout *inside_box = new QVBoxLayout;

    QRadioButton *radio1 = new QRadioButton;
    QRadioButton *radio2 = new QRadioButton;
    QRadioButton *radio3 = new QRadioButton;
    QRadioButton *radio4 = new QRadioButton;
    QRadioButton *radio5 = new QRadioButton;
    QRadioButton *radio6 = new QRadioButton;

    if(_question == 0)
    {
        radio1->setText(examen[0].reponses.at(0));
        radio2->setText(examen[0].reponses.at(1));
        radio3->setText(examen[0].reponses.at(2));
        radio4->setText(examen[0].reponses.at(3));

        inside_box->addWidget(radio1);
        inside_box->addWidget(radio2);
        inside_box->addWidget(radio3);
        inside_box->addWidget(radio4);

        QObject::connect(radio1, &QRadioButton::clicked, [=]() { reponseSelectionee(1); });
        QObject::connect(radio2, &QRadioButton::clicked, [=]() { reponseSelectionee(2); });
        QObject::connect(radio3, &QRadioButton::clicked, [=]() { reponseSelectionee(3); });
        QObject::connect(radio4, &QRadioButton::clicked, [=]() { reponseSelectionee(4); });

    } else if(_question == 1)
    {
        radio1->setText(examen[1].reponses.at(0));
        radio2->setText(examen[1].reponses.at(1));
        radio3->setText(examen[1].reponses.at(2));
        radio4->setText(examen[1].reponses.at(3));
        radio5->setText(examen[1].reponses.at(4));
        radio6->setText(examen[1].reponses.at(5));

        inside_box->addWidget(radio1);
        inside_box->addWidget(radio2);
        inside_box->addWidget(radio3);
        inside_box->addWidget(radio4);
        inside_box->addWidget(radio5);
        inside_box->addWidget(radio6);

        QObject::connect(radio1, &QRadioButton::clicked, [=]() { reponseSelectionee(1); });
        QObject::connect(radio2, &QRadioButton::clicked, [=]() { reponseSelectionee(2); });
        QObject::connect(radio3, &QRadioButton::clicked, [=]() { reponseSelectionee(3); });
        QObject::connect(radio4, &QRadioButton::clicked, [=]() { reponseSelectionee(4); });
        QObject::connect(radio5, &QRadioButton::clicked, [=]() { reponseSelectionee(5); });
        QObject::connect(radio6, &QRadioButton::clicked, [=]() { reponseSelectionee(6); });
    }



    inside_box->addStretch(1);
    box->setLayout(inside_box);

    return box;
}


void reponseSelectionee(int i)
{
    qDebug() << "-  test Connect Radio -> reponseSelectionee() avec " << i;
    n_reponse_cochee = i;
}


void QCMDialog::validerClicked(int checked_n_reponse_cochee, const Examen& examen)
{
    qDebug() << "-  Test validerClicked() avec " << checked_n_reponse_cochee;

    if(n_reponse_cochee == 0)
    {

        afficherMessage(0);

        enableValiderButton(false);

        if(current_question == 0){
        newBox->setEnabled(false);
        }
        else {
        newBox2->setEnabled(false);
        }

    }
    else {


    if(current_question == 0 && n_reponse_cochee != 3)
    {
        qDebug() << "Mauvaise réponse";

        afficherMessage(-1);

        enableValiderButton(false);

        newBox->setEnabled(false);
    }
    else if (current_question == 0 && n_reponse_cochee == 3){
        qDebug() << "Bonne réponse";

        score++;

        QString nvx_score = QString("* Question %1 / %2 \n* Score %3 / %4")
                .arg(current_question + 1)
                .arg(examen.size())
                .arg(score)
                .arg(examen.size());

        question_score = nvx_score;
        txt_affichage_question_score->setText(nvx_score);

        afficherMessage(1);

        enableValiderButton(false);

        newBox->setEnabled(false);

    }

    if(current_question == 1 && n_reponse_cochee != 6)
    {
        qDebug() << "Mauvaise réponse";

        afficherMessage(-1);

        enableValiderButton(false);

        newBox2->setEnabled(false);
    }
    else if (current_question == 1 && n_reponse_cochee == 6) {
        qDebug() << "Bonne réponse";

        score++;

        QString nvx_score = QString("* Question %1 / %2 \n* Score %3 / %4")
                .arg(current_question + 1)
                .arg(examen.size())
                .arg(score)
                .arg(examen.size());

        question_score = nvx_score;
        txt_affichage_question_score->setText(nvx_score);

        afficherMessage(1);

        enableValiderButton(false);

        newBox2->setEnabled(false);


    }

        }

    n_reponse_cochee = 0;
    bContinuer->setEnabled(true);
}



void QCMDialog::continuerClicked(const Examen& examen)
{
    qDebug() << "-  Test continuerClicked()";

    if(current_question < 1) {
    Examen examen = creer_examen();

   current_question++;
   question->setText(examen[current_question].question);

   delete newBox;
   newBox2->show();

   QString nvx_score = QString("* Question %1 / %2 \n* Score %3 / %4")
           .arg(current_question + 1)
           .arg(examen.size())
           .arg(score)
           .arg(examen.size());

   txt_affichage_question_score->setText(nvx_score);

   enableValiderButton(true);

    } else {
        QString txt_fin_QCM = QString("-  Fin du QCM  -\nVotre score : %1 / %2")
                .arg(score)
                .arg(examen.size());;

        QMessageBox msg;
        msg.setWindowTitle("QCM");
        msg.setText(txt_fin_QCM);
        msg.exec();
        this->close();
    }
bContinuer->setEnabled(false);
}


void QCMDialog::enableValiderButton(bool checked)
{
    qDebug() << "-  Test enableValiderButton()";
    bValider->setEnabled(checked);
}

void QCMDialog::quitterClicked()
{
    qDebug() << "-  Test quitterClicked()";
    this->close();
}

void afficherMessage(int valid_or_not)
{

    QMessageBox Window;
    Window.setWindowTitle("QCM");
    Window.setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);

    switch(valid_or_not)
    {
    case 0:
        Window.setText("Aucune réponse");
        break;

    case 1:
        Window.setText("Bonne réponse");
        break;

    case -1:
        Window.setText("Mauvaise réponse");
        break;

    }

    Window.exec();
}
