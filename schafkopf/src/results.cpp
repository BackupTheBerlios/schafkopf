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
#include "results.h"

#include "cardlist.h"
#include "gameinfo.h"
#include "player.h"

Results::Results()
{
    m_laufende = 0;
    m_gameinfo = NULL;
    m_parsed = false;
}

QString Results::result()
{
    parse();
    
    QString s;
    QString schneider = m_schneider ? " schneider" : QString::null;
    QString schwarz = m_schwarz ? " schwarz" : QString::null;
    
    if( m_points > 60 )
        s = m_gameinfo->spieler()->name() + QString(" gewinnt mit %1 Punkten%2.").arg( m_points ).arg( schneider + schwarz );
    else
        s = m_gameinfo->spieler()->name() + QString(" verliert mit %1 Punkten%2.").arg( m_points ).arg( schneider + schwarz );
    
    return s;
}

void Results::parse()
{
    if( m_parsed )
        return;
        
    CardList stiche( *(m_gameinfo->spieler()->stiche()) );
    if( m_gameinfo->mitspieler() )
        stiche.appendList( m_gameinfo->mitspieler()->stiche() );
    
    m_points = stiche.points();
    m_schwarz = ( stiche.isEmpty() || stiche.count() == 8 );
    m_schneider = (m_points < 31 || m_points > 90 );

    m_parsed = true;
}


