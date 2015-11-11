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

// Callback.cc
// code for StegWindow event callbacks

#include "Callback.h"

// Callback for the "About..." menu item
// Show About message
void Callback::about_cb(Fl_Widget *w, void *d)
{
	// build popup string for message
	std::string popup("This is SteGUI, a graphical front-end to Steghide.\n\nSteGUI is Copyright (C) 2005,2007 Nicola Cocchiaro\n\nThis system is running ");
	std::string *ans = Support::run_command("steghide --version");
	if (ans)
		popup += *ans;
	else
		popup += "an unknown version of steghide";
	popup += "and SteGUI version ";
	popup += VERSION;
	// show message
	try {
		MsgWindow *msg = new MsgWindow(410, 180, "About this program", popup, "i");

		while (msg->visible())
			Fl::wait();
		delete ans;
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to initialize message window, aborting." << std::endl;
		exit(1);
	}
}

// Callback for the "Steghide License..." menu item
// Show Steghide license
void Callback::license_cb(Fl_Widget *w, void *d)
{
	Fl_Menu_Bar *menu = (Fl_Menu_Bar *)w;
	const Fl_Menu_Item *menuitem = menu->find_item("&About/Steghide &License");
	if (menuitem)
	{
		// get steghide license output and build message
		std::string *answer = Support::run_command("steghide --license");
		try {
			MsgWindow *msg = new MsgWindow(550, 315, "Steghide license", *answer, "i");
			while (msg->visible())
				Fl::wait();
			delete answer;
		}
		catch (std::exception &e) {
			std::cerr << "Exception thrown: " << e.what() << std::endl;
			std::cerr << "Unable to initialize message window, aborting." << std::endl;
			exit(1);
		}
	}
	else
		std::cerr << "Unable to find license menu item" << std::endl;
}

// Callback for the "Quit" menu item
// Quit the program after asking for confirmation
void Callback::quit_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow *)d;
	if (fl_choice("Are you sure you want to quit?", "Cancel", "Quit", NULL))
	{
		window->hide();
		exit(0);
	}
	return;
}

// Callback for the "Open File..." menu item
// Choose a file to open and open it
void Callback::open_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow *)d;
	
	Fl_File_Chooser *chooser = new Fl_File_Chooser(".", "Image files (*.{bmp,jpg,jpeg})\tAudio files (*.{wav,au})\tText files (*.txt)", Fl_File_Chooser::SINGLE, "Choose file to open:");
	chooser->textsize(12);
	chooser->show();
	
	while (chooser->visible())
		Fl::wait();
	
	const char* newfile = chooser->value();
		
	if (newfile)
	{
		std::string filename(newfile);

		window->openFile(filename);
	}

	delete chooser;
}

// Callback for the "Get open file info" menu item
// Get info on open file
void Callback::info_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow*)d;
	std::string filename = window->getOpenFilename();
	if (filename.c_str())
		Support::get_info(filename.c_str());
}

// Callback for the "Get info" menu item
// Get info on chosen file
void Callback::info_any_cb(Fl_Widget *w, void *d)
{
	Fl_File_Chooser *chooser = new Fl_File_Chooser(".", "Image files (*.{bmp,jpg,jpeg})\tAudio files (*.{wav,au})", Fl_File_Chooser::SINGLE, "Choose file to open:");
	chooser->textsize(12);
	chooser->show();
	
	while (chooser->visible())
		Fl::wait();
	
	const char* newfile = chooser->value();
	
	if (newfile)
		Support::get_info(newfile);

	delete chooser;
}

// Callback for the "Supported encryption..." menu item
// Show steghide encinfo command output
void Callback::encinfo_cb(Fl_Widget *w, void *d)
{
	std::string *str = Support::run_command("steghide --encinfo");
	try {
		MsgWindow *msg = new MsgWindow(360, 370, "Supported encryption algorithms and modes", *str, "i");
		while (msg->visible())
			Fl::wait();
		delete str;
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to initialize message window, aborting." << std::endl;
		exit(1);
	}
}

// Callback for the "Close file" menu item
// Close open file
void Callback::close_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow *)d;
	window->close_file();
	window->redraw();
}

// Callback for window closing events
// Close window and quit
void Callback::win_close_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow *)w;
	window->hide();
	exit(0);
}

// Callback for the "Embed..." menu item
// Show embed dialog window to run steghide embed command
void Callback::embed_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow *)d;
	std::string currentFile = window->getOpenFilename();
	
	try {
		// create file choosers
		Fl_File_Chooser *embedChooser = new Fl_File_Chooser(".", "Image files (*.{bmp,jpg,jpeg})\tAudio files (*.{wav,au})\tText files (*.txt)", Fl_File_Chooser::SINGLE, "Choose file to embed:");
		Fl_File_Chooser *coverChooser = new Fl_File_Chooser(".", "Image files (*.{bmp,jpg,jpeg})\tAudio files (*.{wav,au})", Fl_File_Chooser::SINGLE, "Choose file to use as cover:");
		Fl_File_Chooser *stegoChooser = new Fl_File_Chooser(".", "Image files (*.{bmp,jpg,jpeg})\tAudio files (*.{wav,au})", Fl_File_Chooser::SINGLE, "Choose output stegofile:");
	
		embedChooser->textsize(12);
		coverChooser->textsize(12);
		stegoChooser->textsize(12);
		
		// create embed dialog and show it
		EmbedWindow *dialog = new EmbedWindow(currentFile, embedChooser, coverChooser, stegoChooser);

		dialog->show();
		while (dialog->visible())
			Fl::wait();

		delete embedChooser;
		delete coverChooser;
		delete stegoChooser;
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to pre-initialize embed window, aborting." << std::endl;
		exit(1);
	}
}

// Callback for the "Extract..." menu item
// Show extract dialog window to run steghide extract command
void Callback::extract_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow *)d;
	std::string currentFile = window->getOpenFilename();
	
	try {
		// create file choosers
		Fl_File_Chooser *stegoChooser = new Fl_File_Chooser(".", "Image files (*.{bmp,jpg,jpeg})\tAudio files (*.{wav,au})", Fl_File_Chooser::SINGLE, "Choose input stegofile:");
		Fl_File_Chooser *extractChooser = new Fl_File_Chooser(".", "Image files (*.{bmp,jpg,jpeg})\tAudio files (*.{wav,au})\tText files (*.txt)", Fl_File_Chooser::SINGLE, "Choose name of file to extract to:");

		stegoChooser->textsize(12);
		extractChooser->textsize(12);
		
		// create dialog and show it
		ExtractWindow *dialog = new ExtractWindow(currentFile, stegoChooser, extractChooser);

		dialog->show();
		while (dialog->visible())
			Fl::wait();

		delete stegoChooser;
		delete extractChooser;
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to pre-initialize extract window, aborting." << std::endl;
		exit(1);
	}
}

// Callback for the "Save file" menu item
// Save current file
void Callback::save_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow*)d;

	window->saveTextFile();
}

// Callback for the "Save as..." menu item
// Save current file under a different name
void Callback::saveas_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow*)d;
	
	std::string filename(fl_input("Save file as:"));
	window->saveTextFile(filename);
}

// Callback for the "Reload file" menu item
// Reload current file
void Callback::reload_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow*)d;

	std::string filename = window->getOpenFilename();
	window->close_file();
	window->openFile(filename);
}

// Callback for the "No theme" menu item
// Switch to FLTK basic theme
void Callback::notheme_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow*)d;
	
	Fl::scheme("none");
	window->box(FL_FLAT_BOX);
}

// Callback for the "Plastic theme" menu item
// Switch to FLTK Plastic theme
void Callback::pltheme_cb(Fl_Widget *w, void *d)
{
	StegWindow *window = (StegWindow*)d;
	
	Fl::scheme("plastic");
	window->box(FL_PLASTIC_DOWN_BOX);
}
