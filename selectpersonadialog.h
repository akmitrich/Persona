#ifndef SELECTPERSONADIALOG_H
#define SELECTPERSONADIALOG_H

#include <QDialog>
class SelectPersonaWidget;
class Persona;

class SelectPersonaDialog : public QDialog
{
    Q_OBJECT
public:
    static QList<Persona *> selectPersonaToImport(const QList<Persona *> &personaList, QWidget *parent = nullptr);
    explicit SelectPersonaDialog(const QList<Persona *> &personaList, QWidget *parent = nullptr);
    ~SelectPersonaDialog();
    QList<Persona *> selectedPersona() const;

private:
    SelectPersonaWidget *mView;
};

#endif // SELECTPERSONADIALOG_H
