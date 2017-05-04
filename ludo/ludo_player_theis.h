#ifndef LUDO_PLAYER_THEIS_H
#define LUDO_PLAYER_THEIS_H
#include <QObject>
#include <iostream>

#include "game.h"
#include "positions_and_dice.h"
#include "../neuralnetwork/net.h"

class ludo_player_theis : public QObject
{
    Q_OBJECT
    //  methods
    private:
        std::vector<int> pos_start_of_turn;
        std::vector<int> pos_end_of_turn;
        int dice_roll;
        int make_decision();
        int useNeuralNetwork();
        int choosePawnNumber();

    //  methods
    public:
        ludo_player_theis();
        void whichRound( int round );
        void setGameBoard(game*);

    //  attributes
    private:
        game* gameBoard = NULL;
        net* myNet = NULL;
        int round = 0;

        bool flag = false;

    //  attributes
    public:

    signals:
        void select_piece(int);
        void turn_complete(bool);

    public slots:
        void start_turn(positions_and_dice relative);
        void post_game_analysis(std::vector<int> relative_pos);

};

#endif // LUDO_PLAYER_THEIS_H
