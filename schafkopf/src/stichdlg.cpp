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
#include "stichdlg.h"

#include "card.h"
#include "cardlist.h"
#include "player.h"

#include <qlabel.h>
#include <qlayout.h>

#include <klocale.h>

StichDlg::StichDlg(Game* g,QWidget *parent, const char *name)
    : KDialogBase( KDialogBase::Plain, i18n("Last Trick"),
      KDialogBase::Close, KDialogBase::Close, parent,name, false),
      m_game( g)
{
    QGridLayout* layout = new QGridLayout( plainPage(), 4, 2 );
    trick = new QLabel( plainPage() );
    layout->addMultiCellWidget( trick, 0, 0, 0, 3);
    
    for( unsigned int i = 0; i < PLAYERS; i++ ) {
        cards[i] = new QLabel( plainPage() );
        layout->addWidget( cards[i], 1, i );
        
        players[i] = new QLabel( plainPage() );
        layout->addWidget( players[i], 2, i );
    }
    
    changed( m_game->findIndex( 0 )->id() );
    
    // close if there is no active game
    connect( m_game, SIGNAL( destroyed() ), this, SLOT( deleteLater() ));
    connect( m_game, SIGNAL( playerMadeStich(unsigned int)), this, SLOT(changed(unsigned int)));
}


StichDlg::~StichDlg()
{
}

void StichDlg::changed( unsigned int id )
{
    Player* player = m_game->findId( id );
    CardList* stich = player->stiche();
    
    if( stich && stich->count() )
        trick->setText( i18n("Trick was made by: <b>") + player->name() + "</b>" );
    else
        trick->setText( i18n("No trick was made.") );
        
    for( unsigned int i = 0; i < PLAYERS; i++ )
    {
        if( stich )
        {
            if( stich->count() > i ) 
                cards[i]->setPixmap( *(stich->at( stich->count() - PLAYERS + i )->pixmap()) );
            else
                cards[i]->setPixmap( *Card::backgroundPixmap() );

            if( stich->count() > i )
                players[i]->setText( "<qt><b>"+stich->at( stich->count() - PLAYERS + i )->owner()->name()+"</b></qt>" );
            else
                players[i]->setText( m_game->findIndex(i)->name() );
        }
    }
}

#include "stichdlg.moc"
