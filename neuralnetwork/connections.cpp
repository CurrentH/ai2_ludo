#include "connections.h"

connections::connections()
{
    weight = randomWeight();
}

double connections::getDeltaWeight( void ) const
{
    return deltaWeight;
}

double connections::getWeight( void ) const
{
    return weight;
}

void connections::setDeltaWeight( double newDeltaWeight )
{
    deltaWeight = newDeltaWeight;
}

void connections::setWeight( void )
{
    weight += deltaWeight;
}

double connections::randomWeight( void )
{
    return rand() / double(RAND_MAX);
}
