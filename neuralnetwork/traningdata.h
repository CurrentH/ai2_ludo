#ifndef TRANINGDATA_H
#define TRANINGDATA_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>

class trainingData
{
    public:
        //  Public methods
        trainingData( const std::string filename );
        bool isEof( void );
        void getTopology( std::vector<unsigned> &topology );

        // Returns the number of input values read from the file:
        unsigned getNextInputs( std::vector<double> &inputVals );
        unsigned getTargetOutputs( std::vector<double> &targetOutputVals );

    public:
		//  Public attributes

    private:
		//  Private methods

    private:
        //  Private attributes
        std::ifstream m_trainingDataFile;
};

#endif // TRANINGDATA_H
