#include "neuron.h"

neuron::neuron( unsigned numOutputs, unsigned myIndex )
{
    for( unsigned c = 0; c < numOutputs; ++c )
    {
        m_outputWeights.push_back( connections() );
    }

    m_myIndex = myIndex;
}

void neuron::feedForward( const layer &prevLayer )
{
    double sum = 0.0;

    //  Sum the previous layer's output (which are this neurons inputs)
    //  Include the bias node from the previous layer here too.

    for( unsigned n = 0; n < prevLayer.size(); ++n )
    {
        sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].getWeight();
    }

    m_outputVal = neuron::transferFunction( sum );
}

void neuron::setOutputVal( double val )
{
    m_outputVal = val;
}

double neuron::getOutputVal( void ) const
{
    return m_outputVal;
}

void neuron::calculateOutputGradients( double targetVal )
{
    double delta = targetVal - m_outputVal;
    m_gradient += delta * transferFunctionDerivative( m_outputVal );
}

void neuron::calculateHiddenGradients( const layer &nextLayer )
{
    double dow = sumDOW( nextLayer );
    m_gradient += dow * transferFunctionDerivative( m_outputVal );
}

void neuron::updateInputWeights( layer &prevLayer )
{
    //  The weights to be updated are in the Connection container
    //  in the neurons in the preceding layer

    for( unsigned n = 0; n < prevLayer.size(); ++n )
    {
        neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_outputWeights[ m_myIndex ].getDeltaWeight();
        double newDeltaWeight =
                //  Individual input. Magnified by the gradient and the train rate:
                eta * neuron.getOutputVal() * m_gradient
                //  Also add momentum, which is a fraction of the previous delta weight
                + alpha * oldDeltaWeight;
        neuron.m_outputWeights[ m_myIndex ].setDeltaWeight( newDeltaWeight );
        neuron.m_outputWeights[ m_myIndex ].setWeight();
    }
}

double neuron::transferFunction( double x )
{
    //  tanh - output range [ -1.0 .. 1.0 ]
    return tanh( x );
}

double neuron::transferFunctionDerivative( double x )
{
    //  tanh derivative
    return 1 - x*x;
}

double neuron::sumDOW( const layer &nextLayer ) const
{
    double sum = 0.0;

    //  Sum our contributions of the errors at the nodes we feed
    for( unsigned n = 0; n < nextLayer.size() - 1; ++n )
    {
        sum += m_outputWeights[n].getWeight() * nextLayer[n].m_gradient;
    }

    return sum;
}

void neuron::resetGradiant(){
    m_gradient = 0;
}




