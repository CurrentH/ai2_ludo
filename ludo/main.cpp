#include "dialog.h"
#include <QApplication>
#include "game.h"
#include <vector>
#include "ludo_player.h"
#include "ludo_player_theis.h"
#include "ludo_player_random.h"
#include "positions_and_dice.h"

#include <fstream>

Q_DECLARE_METATYPE( positions_and_dice )

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    qRegisterMetaType<positions_and_dice>();

    for(int _e = 7; _e <= 10; _e++)
    {
        std::string outer = std::to_string(_e);

        for(int _eta = 1; _eta <= 5; _eta++)
        {
            std::string middle = std::to_string(_eta);
            double eta = 0.05 + 0.01*_eta;

            for(int _alpha = 1; _alpha <= 1; _alpha++)
            {
                std::string inner = std::to_string(_alpha);
                double alpha = 0.1;

                //  Set filename and open file
                std::string filename = "testoutput/file_var_" + outer + "_" + middle + "_" + inner +".csv";
                std::cout << filename << std::endl;
                std::fstream fs;
                fs.open(filename, std::fstream::out | std::fstream::app);

                //  Make game
                game g(false);
                g.setGameDelay(000); //if you want to see the game, set a delay

                //  Make players
                ludo_player_theis p1;
                p1.setGameBoard(&g);
                p1.setNeuralNetworkParameters(eta, alpha);
                ludo_player_random p2, p3, p4;

                //  Qt stuff
                QObject::connect(&g,SIGNAL(close()),&a,SLOT(quit()));

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

                for(int i = 0; i <= 30000; ++i)
                {
                    p1.whichRound( i );
                    g.start();
                    a.exec();
                    while( a.closingDown() ){}

                    if( g.getWinnerThisTurn() == 0 ) {
                        p1.updateWeights();
                    }
                    if( i == 20000 ){
                        p1.useNeuralNetworkChoice( true );
                        g.resetStandings();
                    }

                    if( i %100 == 0 ){
                        //  Print to file   // på 0-1000 kommer der 11 udskrivninger.
                        if( fs.is_open() ){
                            fs << i << "," << (g.getStandingPlayer0()) << "," << p1.getNeuralNetworkError() << std::endl;
                        }else{
                            std::cout << "ERROR IN OPENING FILE AND PRINTING OUTPUT" << std::endl;
                            std::cout << filename << std::endl;
                            std::cout << "round,score,error" << std::endl;
                            std::cout << i << "," << g.getStandingPlayer0() << "," << p1.getNeuralNetworkError() << std::endl;
                        }
                    }
                    if( i%1000 == 0 ){
                        std::cout << i << " of 30000 \t score: " << g.getStandingPlayer0() << std::endl;
                    }

                    g.reset();
                    if( g.wait() ){}
                }
                fs.close();

                //  Collect data, and ready file
                std::cout << std::endl;

                //  Reset standing, and do it again.
                g.resetStandings();

            }
        }
    }


    return 0;
}
