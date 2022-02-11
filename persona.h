#ifndef PERSONA_H
#define PERSONA_H

#include "sobject.h"

class Persona : public SObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER mName);
    Q_PROPERTY(QString patronym MEMBER mPatronym);
    Q_PROPERTY(QString family MEMBER mFamily);
    Q_PROPERTY(QString phone MEMBER mPhone);
    Q_PROPERTY(QString email MEMBER mEmail);
public:
    S_OBJECT(Persona)
    explicit Persona(QObject *parent = nullptr);
    QString family() const;
    QString name() const;
    QString patronym() const;
    QString phone() const;
    QString email() const;
    QString fullname() const;

public slots:
    void setFamily(const QString &f);
    void setName(const QString &n);
    void setPatronym(const QString &p);
    void setPhone(const QString &ph);
    void setEmail(const QString &e);
    void appendPhone(const QString &ph);
    void appendEmail(const QString &e);

private:
    QString mName;
    QString mPatronym;
    QString mFamily;
    QString mPhone;
    QString mEmail;
};

#endif // PERSONA_H
