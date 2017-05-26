#include "net.h"

net::net( const std::vector<unsigned> &topology )
{
    unsigned numLayers = topology.size();
    for( unsigned layerNum = 0; layerNum < numLayers; ++layerNum )
    {
        m_layers.push_back( layer() );
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];
        //  We have made a new layer. Now we need to fill it with neurons, and
        //  add a bias neuron to the layer:

        for( unsigned neuronNum = 0; neuronNum <= topology[ layerNum ]; ++neuronNum )
        {
            m_layers.back().push_back( neuron( numOutputs, neuronNum ) );
            std::cout << "Made a neuron" << std::endl;
        }

        //  Force the bias node's output value to 1.0. It's the last neuron created above.
        m_layers.back().back().setOutputVal( 1.0 );
    }
}

void net::feedForward( const std::vector<double> &inputVals )
{
    assert( inputVals.size() == m_layers[0].size() - 1 );

    //  Assign {latch} the input values into the input neurons
    for( unsigned i = 0; i < inputVals.size(); ++i )
    {
        m_layers[0][i].setOutputVal( inputVals[i] );
    }

    //  Forward propagate
    for( unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
    {
        layer &prevLayer = m_layers[layerNum - 1];
        for( unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n )
        {
            m_layers[layerNum][n].feedForward( prevLayer );
        }
    }

}

void net::getErrorVals( const std::vector<double> &targetVals, std::vector<double> &errorVals ){
    layer &outputLayer = m_layers.back();
    for( unsigned n = 0; n < outputLayer.size() - 1; ++n)
    {
        errorVals[n] = targetVals[n] - outputLayer[n].getOutputVal();
    }
}

void net::backProp( const std::vector<double> &targetVals )
{
    //  Calculate overall net error (Root mean square of output neuron errors)
    layer &outputLayer = m_layers.back();
    m_error = 0.0;

    for( unsigned n = 0; n < outputLayer.size() - 1; ++n)
    {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta*delta;
    }
    m_error /= outputLayer.size() - 1;  //   Get average error squared
    m_error = sqrt(m_error);    //  RMS

    //  implement a recent average measurement:
    m_recentAverageError = ( m_recentAverageError * m_recentAverageSmoothingFactor + m_error ) / ( m_recentAverageSmoothingFactor + 1.0 );

    //  Calculate output layer gradients
    for( unsigned n = 0; n < outputLayer.size() - 1; ++n )
    {
        outputLayer[n].calculateOutputGradients( targetVals[n] );
    }

    //  Calculate gradients on hidden layers
    for( unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum )
    {
        layer &hiddenLayer = m_layers[ layerNum ];
        layer &nextLayer = m_layers[ layerNum + 1 ];

        for( unsigned n = 0; n < hiddenLayer.size(); ++n )
        {
            hiddenLayer[n].calculateHiddenGradients( nextLayer );
        }
    }

    //  For all layers from outputs to first hidden layer.
    //  update connection weights
    for( unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum )
    {
        layer &prevLayer = m_layers[layerNum - 1];
        layer &layer = m_layers[ layerNum ];

        for( unsigned n = 0; n < layer.size() - 1; ++n )
        {
            layer[n].updateInputWeights( prevLayer );
        }
    }

}

void net::updateWeights(){
    //  For all layers from outputs to first hidden layer.
    //  update connection weights
    for( unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum )
    {
        layer &prevLayer = m_layers[layerNum - 1];
        layer &layer = m_layers[ layerNum ];

        for( unsigned n = 0; n < layer.size() - 1; ++n )
        {
            layer[n].updateInputWeights( prevLayer );
        }
    }
}

void net::getResults( std::vector<double> &resultVals ) const
{
    resultVals.clear();
    for( unsigned n = 0; n < m_layers.back().size() - 1; ++n )
    {
        resultVals.push_back( m_layers.back()[n].getOutputVal() );
    }

}

double net::getRecentAverageError( void ) const
{
    return m_recentAverageError;
}

void net::showVectorVals(std::string label, std::vector<double> &v)
{
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }

    std::cout << std::endl;
}

void net::setNeuralNetworkParameters(double eta, double alpha){
    for( unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum )
    {
        layer &layer = m_layers[ layerNum ];

        for( unsigned n = 0; n < layer.size() - 1; ++n )
        {
            layer[n].setNeuronParameter(eta, alpha);
        }
    }
}

void net::resetGradiant(){
    //  For all layers from outputs to first hidden layer.
    //  reset all gradiants.
    for( unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum )
    {
        layer &layer = m_layers[ layerNum ];

        for( unsigned n = 0; n < layer.size() - 1; ++n )
        {
            layer[n].resetGradiant();
        }
    }
}





















