#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include <assert.h>
#include <math.h>

#include "connections.h"

class neuron
{
    typedef std::vector<neuron> layer;

    public:
        //  Public methods
            neuron( unsigned numOutputs, unsigned myIndex );
            void setOutputVal( double val );
            double getOutputVal( void ) const;
            void feedForward( const layer &prevLayer );
            void calculateOutputGradients( double targetVal );
            void calculateHiddenGradients( const layer &nextLayer );
            void updateInputWeights( layer &prevLayer );

            void resetGradiant();
            void setNeuronParameter(double _eta, double _alpha){
                eta = _eta; alpha = _alpha;
                std::cout << eta << "\t" << alpha << std::endl; }

    public:
		//  Public attributes

    private:
        //  Private methods
            static double transferFunction( double x );
            static double transferFunctionDerivative( double x );
            double sumDOW( const layer &nextLayer ) const;

    private:
        //  Private attributes
            double eta = 0.01;      //  [0.0..1.0] overall net training rate
            double alpha = 0.4;    //  [0.0..n] multiplier of last weight change (momentum)
            double m_gradient;
            double m_outputVal;
            unsigned m_myIndex;
            std::vector< connections > m_outputWeights;
};

#endif // NEURON_H

//  Few rules
//0.01,0.3 - 35%
//0.007,0.4 - 45%
//0.01,0.4 - 46%
//  All rules
//0.01,0.5 - 43%
//0.01,0.4 - 40%
