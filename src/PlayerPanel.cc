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

// PlayerPanel.cc
// This implements a very simple audio player widget to be displayed in a 
// SndWidget. It will play audio files by instancing a posix thread.

#include "PlayerPanel.h"

// Player panel constructor
PlayerPanel::PlayerPanel(int x, int y, int w, int h, pthread_mutex_t *mutex)
: Fl_Group(x, y, w, h, NULL),
	play(x+BUTTONS_W, y+5, BUTTONS_W, BUTTONS_H, "@>"),
	stop(x+2*BUTTONS_W, y+5, BUTTONS_W, BUTTONS_H, "@-2square"),
	filename(""),
	startW(w)
{

	play.tooltip("Play sound file");
	stop.tooltip("Stop playing sound file");

	play.callback(play_cb, this);
	stop.callback(stop_cb, this);

	play.deactivate();
	stop.deactivate();
	
	play.box(FL_PLASTIC_UP_BOX);
	stop.box(FL_PLASTIC_UP_BOX);
	play.labelsize(12);
	stop.labelsize(12);
	
	this->box(FL_PLASTIC_UP_BOX);
	this->color(fl_darker(FL_GRAY));
	this->resizable(NULL);
	this->end();

	par.mut = mutex;
	par.name = NULL;
}

// Player panel destructor
PlayerPanel::~PlayerPanel()
{
	stopSound();
}

// Callback for Play button
void PlayerPanel::play_cb(Fl_Widget *w, void *d)
{
	PlayerPanel *panel = (PlayerPanel*)d;
	if (!(panel->getFilename()).empty())
		panel->playSound();
}

// Callback for Stop button
void PlayerPanel::stop_cb(Fl_Widget *w, void *d)
{
	PlayerPanel *panel = (PlayerPanel*)d;
	if (!(panel->getFilename()).empty())
		panel->stopSound();
}

// Plays a sound with a worker thread
void PlayerPanel::playSound()
{
	int rc = pthread_create(&thread, NULL, playsound, (void*)&par);
	if (rc)
	{
		fl_alert("Unable to create thread for sound playback!");
	}
}

// Stops currently playing sound
void PlayerPanel::stopSound()
{
	if (pthread_mutex_trylock(par.mut) == EBUSY)
	{
		pthread_cancel(thread);
	}
	else
		pthread_mutex_unlock(par.mut);
}

// Sets audio filename
void PlayerPanel::setFilename(std::string f)
{
	filename = f;
	if (!filename.empty())
	{
		play.activate();
		stop.activate();
		par.name = filename.c_str();
		paused = false;
	}
	else
	{
		play.deactivate();
		stop.deactivate();
		par.name = NULL;
		paused = false;
	}
	redraw();
}

// Gets currently open filename
std::string PlayerPanel::getFilename() const
{
	return(filename);
}
