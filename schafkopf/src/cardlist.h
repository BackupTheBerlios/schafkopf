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

#ifndef CARDLIST_H
#define CARDLIST_H

#include <qptrlist.h>

#include <card.h>

#define CARD_CNT 32
/**
 * By default CardList does not delete its children
 * on destruction!
 * @author Dominik Seichter
 */
 
class CardList : public QPtrList<Card>
{
    public:
        CardList();

        /** initialize this card list with a default card
          * deck of 32 cards.
          * The CardList does now own all elements, i.e. they
          * are delete on destruction.
          */
        void init();
        void randomize();        
        int points();
};

#endif
