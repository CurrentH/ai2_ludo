#include "dialog.h"
#include <QApplication>
#include "game.h"
#include <vector>
#include "ludo_player.h"
#include "ludo_player_theis.h"
#include "ludo_player_random.h"
#include "positions_and_dice.h"

Q_DECLARE_METATYPE( positions_and_dice )

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    qRegisterMetaType<positions_and_dice>();

    //instanciate the players here
    ludo_player_theis p1;
    //ludo_player p2;
    ludo_player_random p2, p3, p4;

    game g(false);
    g.setGameDelay(000); //if you want to see the game, set a delay

    p1.setGameBoard(&g);

    //Add a GUI <-- remove the '/' to uncomment block
    /*Dialog w;
    QObject::connect(&g,SIGNAL(update_graphics(std::vector<int>)),&w,SLOT(update_graphics(std::vector<int>)));
    QObject::connect(&g,SIGNAL(set_color(int)),                   &w,SLOT(get_color(int)));
    QObject::connect(&g,SIGNAL(set_dice_result(int)),             &w,SLOT(get_dice_result(int)));
    QObject::connect(&g,SIGNAL(declare_winner(int)),              &w,SLOT(get_winner()));
    QObject::connect(&g,SIGNAL(close()),&a,SLOT(quit()));
    w.show();
    /*/ //Or don't add the GUI
    QObject::connect(&g,SIGNAL(close()),&a,SLOT(quit()));
    //*/

    //set up for each player
    QObject::connect(&g, SIGNAL(player1_start(positions_and_dice)),&p1,SLOT(start_turn(positions_and_dice)));
    QObject::connect(&p1,SIGNAL(select_piece(int)),                &g, SLOT(movePiece(int)));
    QObject::connect(&g, SIGNAL(player1_end(std::vector<int>)),    &p1,SLOT(post_game_analysis(std::vector<int>)));
    QObject::connect(&p1,SIGNAL(turn_complete(bool)),              &g, SLOT(turnComplete(bool)));

    QObject::connect(&g, SIGNAL(player2_start(positions_and_dice)),&p2,SLOT(start_turn(positions_and_dice)));
    QObject::connect(&p2,SIGNAL(select_piece(int)),                &g, SLOT(movePiece(int)));
    QObject::connect(&g, SIGNAL(player2_end(std::vector<int>)),    &p2,SLOT(post_game_analysis(std::vector<int>)));
    QObject::connect(&p2,SIGNAL(turn_complete(bool)),              &g, SLOT(turnComplete(bool)));

    QObject::connect(&g, SIGNAL(player3_start(positions_and_dice)),&p3,SLOT(start_turn(positions_and_dice)));
    QObject::connect(&p3,SIGNAL(select_piece(int)),                &g, SLOT(movePiece(int)));
    QObject::connect(&g, SIGNAL(player3_end(std::vector<int>)),    &p3,SLOT(post_game_analysis(std::vector<int>)));
    QObject::connect(&p3,SIGNAL(turn_complete(bool)),              &g, SLOT(turnComplete(bool)));

    QObject::connect(&g, SIGNAL(player4_start(positions_and_dice)),&p4,SLOT(start_turn(positions_and_dice)));
    QObject::connect(&p4,SIGNAL(select_piece(int)),                &g, SLOT(movePiece(int)));
    QObject::connect(&g, SIGNAL(player4_end(std::vector<int>)),    &p4,SLOT(post_game_analysis(std::vector<int>)));
    QObject::connect(&p4,SIGNAL(turn_complete(bool)),              &g, SLOT(turnComplete(bool)));

    for(int e = 0; e < 5; e++)
    {
        for(int _eta = 0; _eta <= 100; _eta++)
        {
            double eta = _eta/100.0;
            for(int _alpha = 0; _alpha <= 100; _alpha++)
            {
                double alpha = _alpha/100.0;
                p1.setNeuralNetworkParameters(eta, alpha);

                for(int i = 0; i <= 100; ++i)
                {
                    p1.whichRound( i );
                    g.start();
                    a.exec();
                    while( a.closingDown() ){}

                    if( g.getWinnerThisTurn() == 0 ) {
                        p1.updateWeights();
                    }
                    if( i == 20000 ){
                        p1.useNeuralNetworkChoice();
                        g.resetStandings();
                    }

                    g.reset();
                    if( g.wait() ){}
                }

            }
            std::cout << std::endl;
        }
    }


    return 0;
}
