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
#include "card.h"

#include <qpixmap.h>

#include <kapplication.h>
#include <kcarddialog.h>
#include <kconfig.h>

QPixmap* Card::m_background = 0;

Card::Card( const enum type t, const enum color c )
{
    m_pixmap = 0;
    m_card = t;
    m_color = c;
    
    switch( m_card ) {
        case ASS:
            m_points = 11; break;
        case ZEHN:
            m_points = 10; break;
        case KOENIG:
            m_points = 4; break;
        case OBER:
            m_points = 3; break;
        case UNTER:
            m_points = 2; break;
        case NEUN:
        case ACHT:
        case SIEBEN:
        default:
            m_points = 0;
            break;
    };
}


Card::~Card()
{
    delete m_pixmap;
}

QPixmap* Card::pixmap()
{
    if( !m_pixmap ) {
        QString dir = QString::null;
        QString deck = QString::null;
        
        Card::getDecks( dir, deck );
            
        m_pixmap = new QPixmap( KCardDialog::getCardPath( dir, m_card + m_color ) );
    }
    
    return m_pixmap;
}
        
QPixmap* Card::backgroundPixmap()
{
    if( !m_background ) {
        QString dir = QString::null;
        QString deck = QString::null;
        
        Card::getDecks( dir, deck );
        
        m_background = new QPixmap( deck );
    }
    
    return m_background;
}

void Card::getDecks( QString & dir, QString & deck )
{
    KConfig* config = kapp->config();
    config->setGroup("CardDeck");
    dir = config->readEntry("Cards", KCardDialog::getDefaultCardDir() );
    deck = config->readEntry("Deck", KCardDialog::getDefaultDeck() );    
}
