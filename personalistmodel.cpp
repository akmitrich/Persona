#include "personalistmodel.h"
#include "persona.h"

PersonaListModel::PersonaListModel(const list_t &personaList, QObject *parent)
    : QAbstractListModel{parent}
{
    mPersonaList = personaList;
}


int PersonaListModel::rowCount(const QModelIndex &) const
{
    return mPersonaList.size();
}

QVariant PersonaListModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    if (role == Qt::DisplayRole) {
        auto row = index.row();
        auto persona = mPersonaList.at(row);
        result.setValue(persona->fullname());
    }
    return result;
}

Persona *PersonaListModel::persona(const QModelIndex &index) const
{
    auto row = index.row();
    return mPersonaList.at(row);
}
