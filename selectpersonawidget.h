#ifndef SELECTPERSONAWIDGET_H
#define SELECTPERSONAWIDGET_H

#include <QListView>
class Persona;

class SelectPersonaWidget : public QListView
{
    Q_OBJECT
public:
    SelectPersonaWidget(const QList<Persona *> &personaList, QWidget *parent = nullptr);
    QList<Persona *> selectedPersona() const;
    QList<Persona *> allPersona() const;
};

#endif // SELECTPERSONAWIDGET_H
