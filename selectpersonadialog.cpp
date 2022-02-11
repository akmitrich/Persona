#include "selectpersonadialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include "selectpersonawidget.h"
#include "persona.h"
#include <QDebug>

QList<Persona *> SelectPersonaDialog::selectPersonaToImport(const QList<Persona *> &personaList, QWidget *parent)
{
    QList<Persona *> result;
    SelectPersonaDialog dialog(personaList, parent);
    auto code = dialog.exec();
    if (code == SelectPersonaDialog::Accepted) {
        result = dialog.selectedPersona();
    }
    return result;
}

SelectPersonaDialog::SelectPersonaDialog(const QList<Persona *> &personaList, QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("Выберите персон"));
    auto layout = new QVBoxLayout(this);
    mView = new SelectPersonaWidget(personaList);
    layout->addWidget(mView);
    auto button_box = new QDialogButtonBox;
    layout->addWidget(button_box);
    button_box->addButton(tr("Добавить выбранных"), QDialogButtonBox::AcceptRole);
    button_box->addButton(QDialogButtonBox::Cancel);
    connect(button_box, &QDialogButtonBox::accepted, this, &SelectPersonaDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &SelectPersonaDialog::reject);
}

SelectPersonaDialog::~SelectPersonaDialog()
{
    if (this->result() == SelectPersonaDialog::Accepted) {
        auto selected = mView->selectedPersona();
        for (auto p : mView->allPersona()) {
            if (!selected.contains(p)) {
                p->deleteLater();
            }
        }
    } else {
        for (auto p : mView->allPersona()) {
            p->deleteLater();
        }
    }
}

QList<Persona *> SelectPersonaDialog::selectedPersona() const
{
    return mView->selectedPersona();
}
