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

#include "humanplayer.h"

#include "cardlist.h"
#include "game.h"
#include "gamecanvas.h"
#include "gameinfo.h"
#include "selectgamedlg.h"
#include "timer.h"

#include <klocale.h>
#include <kmessagebox.h>

HumanPlayer::HumanPlayer(CardList *cards,Game* game)
 : QObject( 0, 0 ), Player(cards,game)
{
    m_allowed = NULL;
    m_card = NULL;
}

HumanPlayer::~HumanPlayer()
{
    delete m_allowed;
}

void HumanPlayer::klopfen()
{
}

void HumanPlayer::init()
{
	m_cards->sort((eval_func)m_game->evalCard, (void *)m_game->gameInfo());
	m_game->stateChanged();
}

Card *HumanPlayer::play()
{
   	m_allowed = allowedCards();
	m_card=NULL;
    connect( m_game->canvas(), SIGNAL(playCard(Card*)), this, SLOT(getCard(Card*)));
    ENTER_LOOP();
	delete m_allowed;
    m_allowed = NULL;
    disconnect(m_game->canvas(), SIGNAL(playCard(Card*)), this, SLOT(getCard(Card*)));
    return m_card;
}

GameInfo* HumanPlayer::game()
{
    int m = KMessageBox::questionYesNo( 0, i18n("Do you want to play?") );
    if( m == KMessageBox::Yes )
    {
        SelectGameDlg sgd( m_cards, 0, "sgd" );
        if( sgd.exec() == QDialog::Accepted )
        {
            return sgd.gameInfo();
        }
    } 
    return 0;
}

void HumanPlayer::getCard(Card* card)
{
    if(!m_game)
		return;
	if( m_allowed->containsRef( card ) )
    {
        m_card = card;
        EXIT_LOOP();
    } 
	else
	{
		m_game->canvas()->cardForbidden(card);
	}
}

void HumanPlayer::setCards( CardList *cards)
{
	Player::setCards(cards);
    m_cards->sort((eval_func)m_game->evalCard, (void *)m_game->gameInfo());
	m_game->stateChanged();
}


