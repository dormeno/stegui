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

// PlayerPanel.h
// PlayerPanel header file

#ifndef PLAYERPANEL_H
#define PLAYERPANEL_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/fl_ask.H>
#include <FL/filename.H>
#include <iostream>
#include <string>
#include <pthread.h>
#include "pstreams/pstream.h"
#include "Player.h"

class PlayerPanel : public Fl_Group
{
public:
	PlayerPanel(int x, int y, int w, int h, pthread_mutex_t *mutex);
	~PlayerPanel();
	
	static const int BUTTONS_H = 30;
	static const int BUTTONS_W = 40;
	static const int NUM_BUTTONS = 4;

	void playSound();
	void stopSound();
	void setFilename(std::string f);
	std::string getFilename() const;
	
private:
	Fl_Button play;
	Fl_Button stop;
	std::string filename;
	bool paused;
	pthread_t thread;
	params par;
	int startW;

	static void play_cb(Fl_Widget *w, void *d);
	static void stop_cb(Fl_Widget *w, void *d);
};

#endif
