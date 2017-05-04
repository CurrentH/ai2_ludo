#include "traningdata.h"

trainingData::trainingData( const std::string filename )
{
    m_trainingDataFile.open( filename.c_str() );
}

bool trainingData::isEof( void )
{
    return m_trainingDataFile.eof();
}

void trainingData::getTopology( std::vector<unsigned> &topology )
{
    std::string line;
    std::string label;
/*
    getline( m_trainingDataFile, line );
    std::stringstream ss( line );
    ss >> label;

    if ( this->isEof() || label.compare("topology:") != 0 )
    {
        abort();
    }

    while ( !ss.eof() )
    {
        unsigned n;
        ss >> n;
        topology.push_back(n);
    }
*/
	topology.push_back(2);
	topology.push_back(2);
    topology.push_back(1);

    //	0.000117293 2	(.5 .1)
    //	0.000181584 5
    //	0.000199707 2
    //	0.00040973  2 2 2 2 2
}

unsigned trainingData::getNextInputs( std::vector<double> &inputVals )
{
    inputVals.clear();

    std::string line;
    getline( m_trainingDataFile, line );
    std::stringstream ss(line);

    std::string label;
    ss >> label;
    if ( label.compare("in:") == 0 )
    {
        double oneValue;
        while (ss >> oneValue)
        {
            inputVals.push_back( oneValue );
        }
    }

    return inputVals.size();
}

unsigned trainingData::getTargetOutputs( std::vector<double> &targetOutputVals )
{
    targetOutputVals.clear();

    std::string line;
    getline(m_trainingDataFile, line);
    std::stringstream ss(line);

    std::string label;
    ss >> label;
    if ( label.compare("out:") == 0 )
    {
        double oneValue;
        while (ss >> oneValue)
        {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals.size();
}
