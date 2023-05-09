#include "mesures.h"

#include <iostream>

Mesures::Mesures()
{
}


Mesures::Mesures(float h, float t, QDateTime &d): humidite(h), temperature(t), date(d)
{
}

