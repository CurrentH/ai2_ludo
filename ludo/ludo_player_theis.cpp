#include "ludo_player_theis.h"
#include <random>

ludo_player_theis::ludo_player_theis():
    pos_start_of_turn(16),pos_end_of_turn(16),dice_roll(0)
{
    std::vector<unsigned> topology {17,10,10,10,4};
    myNet = new net( topology );
}

void ludo_player_theis::setGameBoard( game* _g ){
    gameBoard = _g;
}

void ludo_player_theis::whichRound( int _round ){
    round = _round;
}

double ludo_player_theis::getNeuralNetworkError(){
    return myNet->getRecentAverageError();
}

void ludo_player_theis::updateWeights(){
    myNet->updateWeights();
}

void ludo_player_theis::getResult(){
    std::vector<double> resultVals {0, 0, 0, 0};
    myNet->getResults( resultVals );
    myNet->showVectorVals( std::string("Output: "), resultVals );
}

int ludo_player_theis::useNeuralNetwork(){
    //  Set input values
    std::vector<double> inputVals(gameBoard->player_positions.begin(), gameBoard->player_positions.end());
    inputVals.push_back( dice_roll );

    for(int i = 0; i < 16; i++){
        if( inputVals[i] >= 0 ){
            inputVals[i] /= 100;
        }
    }
    inputVals[16] -= 3;
    inputVals[16] /= 6;

    //  Input values into neural network
    myNet->feedForward( inputVals );

    //  If still training network
    if( !trainingOver ){
        //  Output target for neural network
        std::vector<double> targetVals {0, 0, 0, 0};
        int tmp = choosePawnNumber();
        if(tmp != -1){
            targetVals[tmp] = 1;
            myNet->backProp( targetVals );
            return tmp;
        }else{
            return -1;
        }
    }

    //  Else, get the values from the network.
    std::vector<double> resultVals {0, 0, 0, 0};
    myNet->getResults( resultVals );
    std::vector<double>::iterator result = std::max_element(resultVals.begin(), resultVals.end());
    return std::distance(resultVals.begin(), result);
}

int ludo_player_theis::choosePawnNumber(){

    //  Try to get out from home
    if(dice_roll == 6){
        for(int i = 0; i < 4; ++i){
            if(pos_start_of_turn[i] < 0){
                return i;
            }
        }
    }

    //  Move pawn into "goal zone"
    for(int i = 0; i < 4; ++i){
        if( pos_start_of_turn[i] > 0 && pos_start_of_turn[i] < 52 && pos_start_of_turn[i] != 99){
            if( dice_roll + pos_start_of_turn[i] >= 52 ){
                //return i;
            }
        }
    }

    //  Return opponent pawn to home
    for(int i = 0; i < 4; ++i){
        if( pos_start_of_turn[i] > 0 && pos_start_of_turn[i] < 52 && pos_start_of_turn[i] != 99){
            for(int j = 4; j < 16; ++j){
                if( dice_roll + gameBoard->player_positions[i] == gameBoard->player_positions[j] && gameBoard->player_positions[j]%13 != 0){
                    return i;
                }
            }
        }
    }

    //  If we can hit a star with the move
    for(int i = 0; i < 4; ++i){
        if( ((dice_roll + pos_start_of_turn[i] + 8)%13 == 0)
                && pos_start_of_turn[i] != 99)
        {
            return i;
        }
    }

    //  If we can hit a globe with the move
    for(int i = 0; i < 4; ++i){
        if( ((dice_roll + pos_start_of_turn[i] + 5)%13 == 0)
                && pos_start_of_turn[i] != 99)
        {
            return i;
        }
    }

    //  If nothing else, just more the first one
    for(int i = 0; i < 4; ++i){
        if(pos_start_of_turn[i]>=0 && pos_start_of_turn[i] != 99){
            return i;
        }
    }

    for(int i = 0; i < 4; ++i){ //maybe they are all locked in
        if(pos_start_of_turn[i]<0){
            return i;
        }
    }

    return -1;
}

int ludo_player_theis::make_decision(){
    return useNeuralNetwork();
    return choosePawnNumber();
}

void ludo_player_theis::start_turn(positions_and_dice relative){
    pos_start_of_turn = relative.pos;
    dice_roll = relative.dice;
    int decision = make_decision();
    emit select_piece(decision);
}

void ludo_player_theis::post_game_analysis(std::vector<int> relative_pos){
    pos_end_of_turn = relative_pos;
    bool game_complete = true;
    for(int i = 0; i < 4; ++i){
        if(pos_end_of_turn[i] < 99){
            game_complete = false;
        }
    }
    emit turn_complete(game_complete);
    myNet->resetGradiant();
}

void ludo_player_theis::useNeuralNetworkChoice( bool _flag ){
    trainingOver = _flag;
}
