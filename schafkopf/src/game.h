/***************************************************************************
 *   Copyright (C) 2004 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef GAME_H
#define GAME_H

#include "schafkopfdef.h"

#include "cardlist.h"
#include "gameinfo.h"

#include <qobject.h>

class Player;
class GameCanvas;

/**
@author Dominik Seichter
*/
class Game : public QObject
{
    Q_OBJECT
    public:
        Game(QObject *parent = 0, const char *name = 0);
        ~Game();
        void gameLoop();
		CardList *currStich();
		inline CardList *allCards() { return &m_allcards; }
        inline CardList *playedCards() { return &m_playedcards; }
		GameInfo *gameInfo();
        
        void setCanvas( GameCanvas* c );
        GameCanvas* canvas() const { return m_canvas; }
        
        Player* findId( unsigned int id ) const;
        Player* findIndex( unsigned int index ) const;
		bool isTerminated() const { return terminated; }
		int highestCard( CardList* list = 0 );
		bool isHigher( Card* card, Card* high );

        /** returns how many players have doubled
          */
        int timesDoubled();
        int timesThrownTogether();

    signals:        
        void gameStarted();
        void gameEnded();
    
        void playerPlayedCard( unsigned int player, Card* );
        void playerMadeStich( unsigned int player );
        void playerResult( const QString & name, const QString & result );
        
        void signalSetupGameInfo();
        void signalDoubled();
        
    public slots:
        void endGame(void);

    private slots:
        /** set the results of all players to 0. This is necessary
          * if for example the class for the results calculation was changed
          * or when a new game is started.
          */
        void resetGameResults();

        /** Called on initialization and when the user changed the names 
          * of the players to represent the changes in the UI
          */
        void updatePlayerNames();

    private:
		/** give cards to the player and begin a new gameinfo
		 */
		void start();
        /** Display the results of the game (winner/loser)
          * to the user. Called after each game.
          */
        void gameResults();
		
        /** find a player who wants to playerPlayedCard 
          * and setup m_gameinfo according to this
          * returns true on succes
          * and false when no one wants to playerPlayedCard
          * and a new game should be started
          */
       bool setupGameInfo(Player *players[]);
       
       /** internal helper function for setupGameInfo().
         * handles all cases when no player wants to play.
         * It forces players in certain cases to play according
         * to the users settings.
         */
       bool setupGameInfoForced();
        
    private:
        bool terminated;
        Player *m_players[PLAYERS];
        CardList m_allcards;
        CardList m_playedcards;
        CardList m_currstich;
        GameInfo m_gameinfo;
        int m_laufende;
        int m_timesThrownTogether;
                
        GameCanvas *m_canvas;
        
};

#endif
