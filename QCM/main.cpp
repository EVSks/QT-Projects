#include "qcm.h"
#include "qcmdialog.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Examen examen = creer_examen();

    QCMDialog dialog(examen);

    dialog.show();

    return app.exec();
}



Examen creer_examen()
{
    QCM q;

    Examen _examen;

    q.question = QString("Laquelle des expressions suivantes est un prototype de  fonction ?");
    q.reponses.clear();
    q.reponses.push_back("int f(0);");
    q.reponses.push_back("int f(int 0);");
    q.reponses.push_back("int f(int i);");
    q.reponses.push_back("int f(i);");

    q.nb_reponses = 4;

    q.solution=3;
    q.point=1;
    _examen.push_back(q);

    q.question = QString("Qui pose des questions stupides ?");
    q.reponses.clear();
    q.reponses.push_back("le prof. de math");
    q.reponses.push_back("mon copain/ma copine");
    q.reponses.push_back("moi");
    q.reponses.push_back("le prof. d’info");
    q.reponses.push_back("personne, il n’y a pas de question stupide");
    q.reponses.push_back("les sondages");

    q.nb_reponses = 6;

    q.solution=6;
    q.point=1;
    _examen.push_back(q);

    /* etc ... */
return _examen;
}
