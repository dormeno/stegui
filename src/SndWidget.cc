/*
 *   This is SteGUI, a graphical front-end to Steghide.
 *   Copyright (C) 2005,2007 Nicola Cocchiaro <ncocchiaro@users.sf.net>
 *   SteGUI can be found at http://www.sf.net/projects/stegui.
 *
 *   You will need Steghide to run SteGUI, you can get it at 
 *   http://steghide.sf.net. Steghide is Copyright (C) 2003 Stefan Hetzl.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

// SndWidget.cc
// This subclass of CardWidget deals with (currently WAVE and AU) audio data 
// formats to display a PlayerPanel that will play the sounds

#include "SndWidget.h"

// SndWidget constructor
SndWidget::SndWidget(int x, int y, int w, int h, std::string f, pthread_mutex_t *mutex)
	: CardWidget(x, y, w, h, f),
	panel(x, y+1, PlayerPanel::BUTTONS_W*PlayerPanel::NUM_BUTTONS, PlayerPanel::BUTTONS_H + 10, mutex)
{
	panel.setFilename(f);
	panel.show();
	this->resizable(NULL);
	this->end();
}

// SndWidget destructor (everything is destroyed by FLTK)
SndWidget::~SndWidget()
{
}
