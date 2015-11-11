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

// Callback.h
// StegWindow event callbacks header file

#ifndef CALLBACK_H
#define CALLBACK_H

#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Enumerations.H>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "pstreams/pstream.h"
#include "SteGUI.h"
#include "StegWindow.h"
#include "Support.h"
#include "EmbedWindow.h"
#include "ExtractWindow.h"
#include "MsgWindow.h"

class Callback
{
public:
	// only static callbacks
	static void about_cb(Fl_Widget *w, void *d);
	static void license_cb(Fl_Widget *w, void *d);
	static void quit_cb(Fl_Widget *w, void *d);
	static void open_cb(Fl_Widget *w, void *d);
	static void info_cb(Fl_Widget *w, void *d);
	static void info_any_cb(Fl_Widget *w, void *d);
	static void encinfo_cb(Fl_Widget *w, void *d);
	static void close_cb(Fl_Widget *w, void *d);
	static void win_close_cb(Fl_Widget *w, void *d);
	static void embed_cb(Fl_Widget *w, void *d);
	static void extract_cb(Fl_Widget *w, void *d);
	static void save_cb(Fl_Widget *w, void *d);
	static void saveas_cb(Fl_Widget *w, void *d);
	static void reload_cb(Fl_Widget *w, void *d);
	static void notheme_cb(Fl_Widget *w, void *d);
	static void pltheme_cb(Fl_Widget *w, void *d);

private:
};

#endif
