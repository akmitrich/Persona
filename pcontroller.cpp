#include "pcontroller.h"
#include <QFile>
#include <QTextStream>
#include "smanager.h"
#include "creationregistry.h"
#include "prep.h"
#include <QDebug>

PController &PController::get()
{
    static PController instance;
    return instance;
}

PController::~PController()
{
    _manager->deleteLater();
}

QList<Prep *> PController::importPreps(const QString &filename)
{
    QFile file(filename);
    QList<Prep *> result;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream istream(&file);
        while (!istream.atEnd()) {
            auto line = istream.readLine();
            auto data = line.split("\t");
            if (auto p = this->createPrep(data)) {
                result << p;
            }
        }
    } else {
        qDebug() << "Fail" << file.errorString();
    }
    return result;
}

QList<Prep *> PController::allPreps() const
{
    QList<Prep *> result;
    if (auto manager = this->manager()) {
        result << manager->findChildren<Prep *>();
    }
    return result;
}

void PController::load()
{
    this->manager()->load("phys.dat");
}

void PController::save() const
{
    this->manager()->save("phys.dat");
}

PController::PController()
{
    _manager = new SManager("Persona");
    this->registerClasses();
}

void PController::registerClasses()
{
    CreationRegistry::get().registerClass<Prep>();
}

Prep *PController::createPrep(const QStringList &data)
{
    enum {number, family, name, patronym, occupancy, degree, title, job, occupancy2, start_date, stavka, birthdate, birthyear, age, phone1, phone2, mobile, email, minimum_size};
    if (data.size() < minimum_size) {
        return nullptr;
    }
    Prep *result{nullptr};
    bool ok;
    data.at(number).toInt(&ok);
    if (ok) {
        result = _manager->newObject<Prep>();
        result->setFamily(data.at(family));
        result->setName(data.at(name));
        result->setPatronym(data.at(patronym));
        result->appendPhone(data.at(phone1));
        result->appendPhone(data.at(phone2));
        result->appendPhone(data.at(mobile));
        result->appendEmail(data.at(email));
    }
    return result;
}
