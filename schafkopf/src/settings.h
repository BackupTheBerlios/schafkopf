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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <qobject.h>

class Results;
class QWidget;

/**
@author Dominik Seichter
*/
class Settings : public QObject
{
    Q_OBJECT
    public:
        static Settings* instance();
        
        const QString cardDeck() const;
        const QString cardBackground() const;
        
        const QStringList playerNames() const;

        void configureCardDecks( QWidget* parent = 0 );
        
        QValueList<int> splitterSizes( int width );
        void setSplitterSizes( QValueList<int> list );
        
        Results* results() const;
        
    signals:
        void cardChanged();
        
    private:
        enum { MONEY, POINTS };
        
        Settings(QObject *parent = 0, const char *name = 0);
        ~Settings();
        
        static Settings* m_instance;

};

#endif
