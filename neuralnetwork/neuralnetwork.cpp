#include "net.h"

void neuralnetwork()
{
    std::vector<unsigned> topology {2,4,1};

    net myNet( topology );

    int trainingPass = 1;

    std::vector<double> inputVals;
    std::vector<double> targetVals;
	std::vector<double> resultVals;

    while ( true )
    {
        //  TODO:   Get the input values
        //trainData.getNextInputs( inputVals );
        assert( inputVals.size() == topology.front() );
        myNet.feedForward( inputVals );

        //  TODO:   Get the target values
        //trainData.getTargetOutputs( targetVals );
        assert( targetVals.size() == topology.back() );
        myNet.backProp( targetVals );

		if( trainingPass%10000 == 0 )
		{
			std::cout << std::endl << "Pass " << trainingPass << std::endl;
			// Report how well the training is working, average over recent samples:
			std::cout << "Net recent average error: " << myNet.getRecentAverageError() << std::endl;
		}

/*
        // Collect the net's actual output results:
        myNet.getResults( resultVals );
        showVectorVals( "Outputs:", resultVals );

        // Train the net what the outputs should have been:
        trainData.getTargetOutputs( targetVals );
        showVectorVals( "Targets:", targetVals );
        assert( targetVals.size() == topology.back() );

        myNet.backProp( targetVals );

        // Report how well the training is working, average over recent samples:
        std::cout << "Net recent average error: " << myNet.getRecentAverageError() << std::endl;
*/

        trainingPass++;
    }

    std::cout << std::endl << "Done at " << trainingPass << std::endl;
    std::cout << "Net average error: " << myNet.getRecentAverageError() << std::endl;
}
