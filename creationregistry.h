#ifndef CREATIONREGISTRY_H
#define CREATIONREGISTRY_H

#include <QHash>
#include "sdecl.h"

using base_class_t = SObject;
typedef base_class_t *(*create_func_t) ();
using func_map_t = QHash<class_id_t, create_func_t>;

class CreationRegistry
{
public:
    static CreationRegistry &get();
    void registerFunc(const class_id_t &cls, create_func_t func);
    template<class T>
    void registerClass() {
        this->registerFunc(T::kClassId(), T::createInstance);
    }
    SObject *create(const class_id_t &cls);
    template<class T>
    T *create() {
        return dynamic_cast<T *>(this->create(T::kClassId()));
    }

private:
    CreationRegistry() {}

//public:
    func_map_t _reg;
};

#endif // CREATIONREGISTRY_H
