#ifndef MESURES_H
#define MESURES_H

#include <string>
#include <QDateTime>

using namespace std;

class Mesures
{
    float humidite;
    float temperature;
    QDateTime date;

public:

    Mesures();

    Mesures(float, float, QDateTime &);

    float get_humidite() const { return (humidite);}

    float get_temperature() const { return (temperature);}

    QDateTime get_date() const { return (date);}
};

Q_DECLARE_METATYPE( Mesures )

#endif // MESURES_H
