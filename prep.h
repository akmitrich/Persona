#ifndef PREP_H
#define PREP_H

#include "persona.h"

class Prep : public Persona
{
    Q_OBJECT
public:
    S_OBJECT(Prep);
    explicit Prep(QObject *parent = nullptr);
};

#endif // PREP_H
