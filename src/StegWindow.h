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

// StegWindow.h
// StegWindow header file

#ifndef STEGWINDOW_H
#define STEGWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Group.H>
#include <FL/Enumerations.H>
#include <FL/filename.H>
#include <FL/Fl_Tabs.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <pthread.h>
#include "Support.h"
#include "ImgWidget.h"
#include "SndWidget.h"
#include "TxtWidget.h"

class StegWindow : public Fl_Double_Window
{
public:
	StegWindow(int w, int h, const char *t);
	~StegWindow();
	
	void load_bitmap(std::string filename, std::string desc);
	void load_jpeg(std::string filename, std::string desc);
	void load_sound(std::string filename, std::string desc);
	void load_text(std::string filename, std::string desc);
	void addOpenFile(CardWidget *cw, std::string filename);
	void close_file();
	std::string getOpenFilename() const;
	void setStatus(std::string s);
	void saveTextFile();
	void saveTextFile(std::string filename);
	void changeItemFlags(std::string item, int flags);
	void openFile(std::string filename);

	static void tabs_cb(Fl_Widget *w, void *d);

private:
	static const int MENU_HEIGHT = 30;
	static const int TABS_HEIGHT = 30;
	static const int STATUS_HEIGHT = 30;

	Fl_Menu_Bar* windowmenu;
	Fl_Tabs* tabs;
	Fl_Box* status;

	pthread_mutex_t mutex;
};

#endif
