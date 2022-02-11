#ifndef SOBJECT_H
#define SOBJECT_H

#include <QObject>
#include "sdecl.h"

#define S_OBJECT(cls)\
    static class_id_t kClassId() {return #cls;}\
    static SObject *createInstance() {\
        return new cls;\
    }

class SManager;

class SObject : public QObject
{
    Q_OBJECT
public:
    S_OBJECT(SObject)
    explicit SObject(QObject *parent = nullptr);
    ~SObject() = default;
    class_id_t getClassId();
    QString label() const;

public slots:
    virtual void setLabel(const QString &label);
    void serialize(QDataStream &out) const;
    void deserialize(QDataStream &in);
    virtual void dumpProperties() const;

protected:
    SManager *manager() const;
    virtual void writeProperties(QDataStream &out) const;
    virtual void doWrite(QDataStream &out) const;
    virtual void readProperties(QDataStream &in);
    virtual void doRead(QDataStream &in);
};

#endif // SOBJECT_H
