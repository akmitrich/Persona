#include "persona.h"
#include <QVariant>

Persona::Persona(QObject *parent)
    : SObject{parent}
{

}

QString Persona::family() const
{
    return this->property("family").toString();
}

QString Persona::name() const
{
    return this->property("name").toString();
}

QString Persona::patronym() const
{
    return this->property("patronym").toString();
}

QString Persona::birthDate() const
{

}

QString Persona::phone() const
{
    return this->property("phone").toString();
}

QString Persona::email() const
{
    return this->property("email").toString();
}

QString Persona::fullname() const
{
    QStringList result;
    result << this->family() << this->name() << this->patronym();
    return result.join(" ");
}

void Persona::setFamily(const QString &f)
{
    this->setProperty("family", f);
}

void Persona::setName(const QString &n)
{
    this->setProperty("name", n);
}

void Persona::setPatronym(const QString &p)
{
    this->setProperty("patronym", p);
}

void Persona::setPhone(const QString &ph)
{
    this->setProperty("phone", ph);
}

void Persona::setEmail(const QString &e)
{
    this->setProperty("email", e);
}

void Persona::appendPhone(const QString &ph)
{
    auto phone = this->phone();
    if (!phone.isEmpty()) {
        phone.append(tr("; "));
    }
    phone.append(ph);
    this->setPhone(phone);
}

void Persona::appendEmail(const QString &e)
{
    auto email = this->email();
    if (!email.isEmpty()) {
        email.append(tr("; "));
    }
    email.append(e);
    this->setEmail(email);
}
