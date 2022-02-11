#ifndef LINKINGCONTEXT_H
#define LINKINGCONTEXT_H

#include "sdecl.h"
#include <QHash>

constexpr id_t kNotFound = 0;

class LinkingContext
{
public:
    LinkingContext();
    ~LinkingContext() = default;
    const QHash<id_t, SObject *> &dump() {
        return _idToObjectMap;
    }

    id_t getId(/*const*/ SObject* obj, bool createIfNotFound);
    SObject* getObject(id_t id);
    void add(id_t id, /*const*/SObject *obj);
    void removeObject(/*const*/SObject *obj);
    void removeId(id_t id);

protected:
    void doRemove(id_t id, /*const*/SObject *obj);

private:
    QHash<id_t, SObject *> _idToObjectMap;
    QHash<SObject *, id_t> _objectToIdMap;
    id_t _nextId;
};

#endif // LINKINGCONTEXT_H
