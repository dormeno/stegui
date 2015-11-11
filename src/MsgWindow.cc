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

// MsgWindow.cc
// This class implements a generic message window that can display any message 
// as a popup

#include "MsgWindow.h"

// Message Window constructor
MsgWindow::MsgWindow(int w, int h, std::string title, std::string text, std::string symbol)
	: Fl_Window(w, h, title.c_str())
{
	try {
		box = new Fl_Box(FL_NO_BOX, 60, 10, w-70, h-56, title.c_str());
		box->label(text.c_str());
		box->labelsize(12);
		box->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);

		icon = new Fl_Box(10, 10, 40, 40);
		icon->box(FL_THIN_UP_BOX);
		icon->labelfont(FL_TIMES_BOLD);
		icon->labelsize(34);
		icon->color(FL_WHITE);
		icon->labelcolor(FL_BLUE);
		icon->label(symbol.c_str());

		okButton = new Fl_Return_Button((w/2)-50, h-36, 100, 26, "OK");
		okButton->callback(okCallback, this);
		okButton->labelsize(12);
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to initialize message window components, aborting." << std::endl;
		exit(1);
	}
	
	this->end();
	this->callback(windowclose);
	this->show();
}

// Message window destructor (everything is destroyed by FLTK)
MsgWindow::~MsgWindow()
{
}

// Callback for OK button
void MsgWindow::okCallback(Fl_Widget *w, void *d)
{
	MsgWindow *window = (MsgWindow*)d;

	window->hide();
	Fl::delete_widget(window);
}

// Callback for window close events
void MsgWindow::windowclose(Fl_Widget *w, void *d)
{
	MsgWindow *window = (MsgWindow*)w;

	window->hide();
	Fl::delete_widget(window);
}
