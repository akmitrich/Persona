#ifndef SMANAGER_H
#define SMANAGER_H

#include <QObject>
#include <QSet>
#include "sdecl.h"

struct object_header_t {
    object_header_t() {}
    object_header_t(id_t i, const class_id_t &c) : id{i}, cls{c} {}
    id_t id;
    class_id_t cls;
};

using to_many_relationship_t = QList<object_header_t>;
class LinkingContext;

class SManager : public QObject
{
    Q_OBJECT
public:

    explicit SManager(const QString &key, QObject *parent = nullptr);
    ~SManager();

    QSet<SObject *> allObjects() const;
    template<class T>
    T *newObject();
    void deleteObject(SObject *obj);

    template<class T>
    void serializeOne(T *one, QDataStream &out);
    template<class T>
    void serializeMany(const QList<T *> &many, QDataStream &out);
    template<class T>
    void serializeMany(const QSet<T *> &many, QDataStream &out);
    template<class T>
    T *deserializeOne(QDataStream &in);
    template<class T>
    QList<T *> deserializeList(QDataStream &in);
    template<class T>
    QSet<T *> deserializeSet(QDataStream &in);

signals:
    void readyToSave();
    void hasBeenSaved();
    void aboutToBeLoaded();
    void hasBeenLoaded();

public slots:
    virtual void registerClasses();
    void serialize(QDataStream &out);
    void deserialize(QDataStream &in);
    void save(const QString &filename);
    void load(const QString &filename);
    void reset();

protected:
    inline LinkingContext *context() const;
    SObject *getOrCreate(const object_header_t &header);

private:
    SObject *createNewInstance(class_id_t cls);
    SObject *newObjectHelper(class_id_t cls);
    SObject *deserializeOneHelper(QDataStream &in);
    QList<SObject *> deserializeManyHelper(QDataStream &in);
    void serializeOneHelper(SObject *one, QDataStream &out);
    void serializeEmpty(class_id_t cls, QDataStream &out);
    void serializeManyHelper(const to_many_relationship_t &relationship, QDataStream &out);
    to_many_relationship_t prepareToManyRelationship(const QList<SObject *> &many);

private slots:
    void onDestroyObject();

private:
    QString _key;
    LinkingContext *_context;
};

LinkingContext *SManager::context() const
{
    return _context;
}

template<class T>
void SManager::serializeOne(T *one, QDataStream &out)
{
    if (one) {
        this->serializeOneHelper(one, out);
    } else {
        this->serializeEmpty(T::kClassId(), out);
    }
}

template<class T>
QSet<T *> SManager::deserializeSet(QDataStream &in)
{
    auto list = this->deserializeList<T>(in);
    return QSet<T *>(list.begin(), list.end());
}

template<class T>
QList<T *> SManager::deserializeList(QDataStream &in)
{
    QList<T *> result;
    for (auto o : this->deserializeManyHelper(in)) {
        if (auto t = qobject_cast<T *>(o)) {
            result << t;
        }
    }
    return result;
}

template<class T>
void SManager::serializeMany(const QSet<T *> &many, QDataStream &out)
{
    auto to_list = QList<T *>(many.begin(), many.end());
    this->serializeMany(to_list, out);
}

template<class T>
void SManager::serializeMany(const QList<T *> &many, QDataStream &out)
{
    QList<SObject *> to_list{many.begin(), many.end()};
    this->serializeManyHelper(this->prepareToManyRelationship(to_list), out);
}

template<class T>
T *SManager::deserializeOne(QDataStream &in)
{
    return qobject_cast<T *>(this->deserializeOneHelper(in));
}

template<class T>
T *SManager::newObject()
{
    return qobject_cast<T *>(this->newObjectHelper(T::kClassId()));
}

#endif // SMANAGER_H
