#include "selectpersonawidget.h"
#include "personalistmodel.h"

SelectPersonaWidget::SelectPersonaWidget(const QList<Persona *> &personaList, QWidget *parent) : QListView(parent)
{
    this->setModel(new PersonaListModel(personaList));
    this->setSelectionMode(QListView::ExtendedSelection);
    auto one_size = this->visualRect(this->model()->index(0, 0, QModelIndex()));
    this->setMinimumHeight(24 * one_size.height());
    this->setMinimumWidth(one_size.width());
}

QList<Persona *> SelectPersonaWidget::selectedPersona() const
{
    QList<Persona *> result;
    auto selected_indexes = this->selectedIndexes();
    if (auto model = dynamic_cast<PersonaListModel *>(this->model())) {
        for (const auto &index : selected_indexes) {
            if (auto p = model->persona(index)) {
                result << p;
            }
        }
    }
    return result;
}

QList<Persona *> SelectPersonaWidget::allPersona() const
{
    QList<Persona *> result;
    if (auto model = dynamic_cast<PersonaListModel *>(this->model())) {
        result = model->personaList();
    }
    return result;
}
