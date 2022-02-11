#include "smanager.h"
#include <QFile>
#include <QDataStream>

#include "creationregistry.h"
#include "linkingcontext.h"
#include "sobject.h"

#include <QDebug>


QDataStream &operator<<(QDataStream &out, const object_header_t& related)
{
    out << related.id << related.cls;
    return out;
}

QDataStream &operator>>(QDataStream &in, object_header_t &related)
{
    in >> related.id >> related.cls;
    return in;
}

SManager::SManager(const QString &key, QObject *parent):
    QObject(parent), _key{key}, _context{new LinkingContext}
{
    connect(this, &SManager::aboutToBeLoaded, this, &SManager::reset);
}

SManager::~SManager()
{
    delete _context;
}

QSet<SObject *> SManager::allObjects() const
{
    auto object_list = this->findChildren<SObject *>(QString(), Qt::FindDirectChildrenOnly);
    return {object_list.begin(), object_list.end()};
}

void SManager::serializeOneHelper(SObject *one, QDataStream &out)
{
    Q_ASSERT(one);
    auto id = _context->getId(one, false);
    if (id != kNotFound) {
        out << object_header_t{id, one->getClassId()};
    } else {
        throw QString("No such object %1").arg(reinterpret_cast<quint64>(one));
    }
}

void SManager::serializeEmpty(class_id_t cls, QDataStream &out)
{
    out << object_header_t{kNotFound, cls};
}

void SManager::deleteObject(SObject *obj)
{
    obj->deleteLater();
}

void SManager::save(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        this->serialize(out);
    } else {
        qDebug() << "Cannot save to" << filename << this->allObjects();
    }
}

void SManager::serialize(QDataStream &out)
{
    emit readyToSave();
    out << _key;
    for (const auto o : this->allObjects()) {
        auto id = _context->getId(o, false);
        if (id != kNotFound) {
            out << object_header_t{id, o->getClassId()};
            o->serialize(out);
        } else {
            qDebug() << "Error! No ID for object:" << o;
        }
    }
    emit hasBeenSaved();
}

void SManager::deserialize(QDataStream &in)
{
    QString key;
    in >> key;
    if (key == _key) {
        emit aboutToBeLoaded();
        while (!in.atEnd()) {
            object_header_t header;
            in >> header;
            if (auto o = this->getOrCreate(header)) {
                o->deserialize(in);
            }
        }
        emit hasBeenLoaded();
    } else {
        qDebug() << "Error with key:" << key;
    }
}

void SManager::load(const QString &filename)
{
    QFile file{filename};
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in{&file};
        this->deserialize(in);
    } else {
        qDebug() << "Unable to load" << filename;
    }
}

SObject *SManager::createNewInstance(class_id_t cls)
{
    auto result = CreationRegistry::get().create(cls);
    if (result) {
        result->setParent(this);
        connect(result, &SObject::destroyed, this, &SManager::onDestroyObject);
    }
    return result;
}

SObject *SManager::newObjectHelper(class_id_t cls)
{
    auto result = this->createNewInstance(cls);
    if (result) {
        _context->getId(result, true);
    }
    return result;
}

SObject *SManager::getOrCreate(const object_header_t &header)
{
    auto result = _context->getObject(header.id);
    if (result == nullptr) {
        if (header.id) {
            result = this->createNewInstance(header.cls);
            _context->add(header.id, result);
        }
    }
    return result;
}

SObject *SManager::deserializeOneHelper(QDataStream &in)
{
    object_header_t header;
    in >> header;
    return this->getOrCreate(header);
}

QList<SObject *> SManager::deserializeManyHelper(QDataStream &in)
{
    QList<SObject *> result;
    to_many_relationship_t data;
    in >> data;
    for (const auto &header : data) {
        if (auto o = this->getOrCreate(header)) {
            result.append(o);
        }
    }
    return result;
}

void SManager::serializeManyHelper(const to_many_relationship_t &relationship, QDataStream &out)
{
    out << relationship;
}

to_many_relationship_t SManager::prepareToManyRelationship(const QList<SObject *> &many)
{
    to_many_relationship_t result;
    for (auto o : many) {
        if (auto id = _context->getId(o, false)) {
            result << object_header_t{id, o->getClassId()};
        }
    }
    return  result;
}

void SManager::reset()
{
    for (auto o : this->allObjects()) {
        this->deleteObject(o);
    }
    delete _context;
    _context = new LinkingContext;
}

void SManager::onDestroyObject()
{
    auto sender_object = sender();
    auto o = static_cast<SObject *>(sender_object);
        //SObject destructor completes already, you lost RTTI and QMeta data
        //The only option is to apply static_cast
    _context->removeObject(o);
}

void SManager::registerClasses()
{
}
