#ifndef PCONTROLLER_H
#define PCONTROLLER_H

#include "sdecl.h"
class SManager;
class Prep;
class PController
{
public:
    static PController &get();
    ~PController();
    inline SManager *manager() const;
    QList<Prep *> importPreps(const QString &filename);
    QList<Prep *> allPreps() const;
    void load();
    void save() const;

private:
    PController();
    void registerClasses();
    Prep *createPrep(const QStringList &data);
    SManager *_manager;
};

inline SManager *PController::manager() const
{
    return _manager;
}

#endif // PCONTROLLER_H
