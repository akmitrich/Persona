#include "creationregistry.h"
#include <QDebug>

CreationRegistry &CreationRegistry::get()
{
    static CreationRegistry instance;
    return instance;
}

void CreationRegistry::registerFunc(const class_id_t &cls, create_func_t func)
{
    Q_ASSERT(_reg.value(cls, nullptr) == nullptr);
    _reg.insert(cls, func);
}

SObject *CreationRegistry::create(const class_id_t &cls)
{
    SObject *result{nullptr};
    if (auto func = _reg.value(cls, nullptr)) {
        result = func();
    }
    return result;
}
