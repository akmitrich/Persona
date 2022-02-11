#ifndef PERSONALISTMODEL_H
#define PERSONALISTMODEL_H

#include <QAbstractListModel>
class Persona;
using list_t = QList<Persona *>;

class PersonaListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PersonaListModel(const list_t &personaList, QObject *parent = nullptr);
    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Persona *persona(const QModelIndex &index) const;
    list_t personaList() const { return mPersonaList; }

private:
    list_t mPersonaList;

    // QAbstractItemModel interface
};

#endif // PERSONALISTMODEL_H
