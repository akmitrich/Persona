#include "sobject.h"
#include <QMetaProperty>
#include <QVariant>

#include "smanager.h"
#include <QDebug>

SObject::SObject(QObject *parent) : QObject(parent)
{

}

class_id_t SObject::getClassId()
{
    auto meta_object = this->metaObject();
    return meta_object->className();
}

QString SObject::label() const
{
    return this->property("objectName").toString();
}

void SObject::setLabel(const QString &label)
{
    this->setProperty("objectName", label);
}

void SObject::serialize(QDataStream &out) const
{
    this->writeProperties(out);
    this->doWrite(out);
}

void SObject::deserialize(QDataStream &in)
{
    this->readProperties(in);
    this->doRead(in);
}

void SObject::dumpProperties() const
{
    auto meta_object = this->metaObject();
    auto property_count = meta_object->propertyCount();
    for (int i = 0; i < property_count; ++i) {
        auto property = meta_object->property(i);
        auto property_name = property.name();
        qDebug() << i + 1 << property_name << this->property(property_name);
    }
}

SManager *SObject::manager() const
{
    return qobject_cast<SManager *>(this->parent());
}

void SObject::writeProperties(QDataStream &out) const
{
    auto meta_object = this->metaObject();
    auto property_count = meta_object->propertyCount();
    for (int i = 0; i < property_count; ++i) {
        auto property = meta_object->property(i);
        auto value = this->property(property.name());
        out << value;
    }
}

void SObject::doWrite(QDataStream &out) const
{
    Q_UNUSED(out)
}

void SObject::readProperties(QDataStream &in)
{
    auto meta_object = this->metaObject();
    auto property_count = meta_object->propertyCount();
    for (int i = 0; i < property_count; ++i) {
        auto property = meta_object->property(i);
        QVariant value;
        in >> value;
        this->setProperty(property.name(), value);
    }
}

void SObject::doRead(QDataStream &in)
{
    Q_UNUSED(in);
}
