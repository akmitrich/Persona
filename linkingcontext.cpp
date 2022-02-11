#include "linkingcontext.h"


LinkingContext::LinkingContext() : _nextId{kNotFound}
{

}

id_t LinkingContext::getId(SObject *obj, bool createIfNotFound)
{
    Q_ASSERT(obj != nullptr);
    id_t result = _objectToIdMap.value(obj, kNotFound);
    if (result == kNotFound && createIfNotFound) {
        result = _nextId + 1;
        this->add(result, obj);
    }
    return result;
}

SObject *LinkingContext::getObject(id_t id)
{
    return _idToObjectMap.value(id, nullptr);
}

void LinkingContext::add(id_t id, SObject *obj)
{
    if (obj) {
        _idToObjectMap.insert(id, obj);
        _objectToIdMap.insert(obj, id);
        if (id > _nextId) {
            _nextId = id;
        }
    }
}

void LinkingContext::removeObject(SObject *obj)
{
    if (obj) {
        auto id = _objectToIdMap.value(obj, kNotFound);
        if (id != kNotFound) {
            this->doRemove(id, obj);
        }
    }
}

void LinkingContext::removeId(id_t id)
{
    auto obj = _idToObjectMap.value(id, nullptr);
    if (obj) {
        this->doRemove(id, obj);
    }
}

void LinkingContext::doRemove(id_t id, SObject *obj)
{
    _idToObjectMap.remove(id);
    _objectToIdMap.remove(obj);
}
