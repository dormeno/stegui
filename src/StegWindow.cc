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

// StegWindow.cc
// Main window implementation for SteGUI

#include "StegWindow.h"
#include "Callback.h"

// Main window constructor
StegWindow::StegWindow(int w, int h, const char *t) 
	: Fl_Double_Window(w, h, t)
{
	// main menu items
	Fl_Menu_Item menuitems[] = {

		{ "&File", 0, 0, 0, FL_SUBMENU },
		{ "&Open file...", FL_ALT + 'o', (Fl_Callback *)Callback::open_cb, this },
		{ "&Save file", FL_ALT + 's', (Fl_Callback *)Callback::save_cb, this, FL_MENU_INACTIVE },
		{ "Sa&ve as...", FL_ALT + 'v', (Fl_Callback *)Callback::saveas_cb, this, FL_MENU_INACTIVE },
		{ "&Reload file", FL_ALT + 'r', (Fl_Callback *)Callback::reload_cb, this, FL_MENU_INACTIVE },
		{ "&Close file", FL_ALT + 'c', (Fl_Callback *)Callback::close_cb, this, FL_MENU_INACTIVE },
		{ "&Quit", FL_ALT + 'q', (Fl_Callback *)Callback::quit_cb, this },
		{ 0 },
		
		{ "&Actions", 0, 0, 0, FL_SUBMENU },
		{ "E&mbed...", FL_ALT + 'm', (Fl_Callback *)Callback::embed_cb, this },
		{ "E&xtract...", FL_ALT + 'x', (Fl_Callback *)Callback::extract_cb, this, FL_MENU_DIVIDER },
		{ "No &theme", FL_ALT + 't', (Fl_Callback *)Callback::notheme_cb, this, FL_MENU_RADIO|FL_MENU_VALUE },
		{ "&Plastic theme", FL_ALT + 'p', (Fl_Callback *)Callback::pltheme_cb, this, FL_MENU_RADIO },
		{ 0 },

		{ "&Info", 0, 0, 0, FL_SUBMENU },
		{ "Get open file &info...", FL_ALT + 'i', (Fl_Callback *)Callback::info_cb, this, FL_MENU_INACTIVE },
		{ "&Get info...", FL_ALT + 'g', (Fl_Callback *)Callback::info_any_cb, this },
		{ "Supported &encryption...", FL_ALT + 'e', (Fl_Callback *)Callback::encinfo_cb, this },
		{ 0 },

		{ "&About", 0, 0, 0, FL_SUBMENU },
		{ "&About this program", FL_ALT + 'a', (Fl_Callback *)Callback::about_cb, this },
		{ "Steghide &License", FL_ALT + 'l', (Fl_Callback *)Callback::license_cb, this },
		{ 0 },

		{ 0 }
	};

	try {
		// create widgets
		windowmenu = new Fl_Menu_Bar(0, 0, w, MENU_HEIGHT);
		windowmenu->labelsize(12);
		windowmenu->textsize(12);
		windowmenu->copy(menuitems);

		tabs = new Fl_Tabs(0, MENU_HEIGHT, w, h - MENU_HEIGHT - STATUS_HEIGHT);
		tabs->callback(tabs_cb, this);
		tabs->end();

		status = new Fl_Box(FL_DOWN_BOX, 0, h - STATUS_HEIGHT, w, STATUS_HEIGHT, NULL);
		status->label("No open files");
		status->labelsize(12);
		status->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT);
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to initialize main window, aborting." << std::endl;
		exit(1);
	}
	
	pthread_mutex_init(&mutex, NULL);
	
	this->box(FL_FLAT_BOX);
	this->color(fl_darker(FL_WHITE));
	this->callback((Fl_Callback *)Callback::win_close_cb);
	this->resizable(tabs);
	this->end();
}

// Main window destructor
StegWindow::~StegWindow()
{
	Fl::delete_widget(windowmenu);
	pthread_mutex_destroy(&mutex);
}

// Loads a bitmap image file and displays it
void StegWindow::load_bitmap(std::string filename, std::string desc)
{
	try {
		Fl_BMP_Image *img = new Fl_BMP_Image(filename.c_str());

		status->label(desc.c_str());

		ImgWidget *imgw = new ImgWidget(0, MENU_HEIGHT+TABS_HEIGHT+1, this->w(), this->h() - MENU_HEIGHT - TABS_HEIGHT - STATUS_HEIGHT, filename, img);
		imgw->setDescription(desc);
		addOpenFile(imgw, filename);
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to display bitmap image, aborting." << std::endl;
		exit(1);
	}
}

// Loads a jpeg image file and displays it
void StegWindow::load_jpeg(std::string filename, std::string desc)
{
	try {
		Fl_JPEG_Image *img = new Fl_JPEG_Image(filename.c_str());

		status->label(desc.c_str());

		ImgWidget *imgw = new ImgWidget(0, MENU_HEIGHT+TABS_HEIGHT+1, this->w(), this->h() - MENU_HEIGHT - TABS_HEIGHT - STATUS_HEIGHT, filename, img);
		imgw->setDescription(desc);
		addOpenFile(imgw, filename);
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to display jpeg image, aborting." << std::endl;
		exit(1);
	}
}

// Loads a sound file
void StegWindow::load_sound(std::string filename, std::string desc)
{
	try {
		status->label(desc.c_str());

		SndWidget *sndw = new SndWidget(0, MENU_HEIGHT+TABS_HEIGHT+1, this->w(), this->h() - MENU_HEIGHT - TABS_HEIGHT - STATUS_HEIGHT, filename, &mutex);
		sndw->setDescription(desc);
		addOpenFile(sndw, filename);
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to open sound file, aborting." << std::endl;
		exit(1);
	}
}

// Loads a text file
void StegWindow::load_text(std::string filename, std::string desc)
{
	try {
		status->label(desc.c_str());

		TxtWidget *txtw = new TxtWidget(0, MENU_HEIGHT+TABS_HEIGHT+1, this->w(), this->h() - MENU_HEIGHT - TABS_HEIGHT - STATUS_HEIGHT, filename);
		txtw->setDescription(desc);
		addOpenFile(txtw, filename);
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to open text file, aborting." << std::endl;
		exit(1);
	}
}

// Add an open file to the tabs widget and set menu items appropriately
void StegWindow::addOpenFile(CardWidget *cw, std::string newfile)
{
	// only do this if there are no other open files
	// tabs.children() is still 0 in this case
	if (tabs->children() == 0)
	{
		changeItemFlags("&Info/Get open file &info...", 0);
		changeItemFlags("&File/&Reload file", 0);
		changeItemFlags("&File/&Close file", 0);
	}
	
	// put new item in open files structure
	tabs->add(cw);
	tabs->value(cw);
	
	std::string type = cw->getDescription();
	if (type.find("File type: Text") == 0)
	{
		changeItemFlags("&File/&Save file", 0);
		changeItemFlags("&File/Sa&ve as...", 0);
	}

	// set window title
	std::string title = "SteGUI - ";
	title += newfile;
	this->label(title.c_str());
	
	redraw();
}

// Closes file and display next image in queue
void StegWindow::close_file()
{
	CardWidget *cw = (CardWidget*)(tabs->value());
	if (cw)
	{
		// check if file has to be saved
		std::string type = cw->getDescription();
		if (type.find("File type: Text") == 0)
		{
			TxtWidget *tw = (TxtWidget*)cw;
			if (tw->isModified())
			{
				std::string popup = "File ";
				popup += tw->getFilename();
				popup += " has been modified, save?";
				int ans = fl_choice(popup.c_str(), "No", "Save", "Save as...");
				if (ans == 1)
					tw->saveFile();
				else if (ans == 2)
				{
					std::string filename(fl_input("Save file as:"));
					tw->saveFile(filename);
				}
			}
		}

		// remove file from tabs
		tabs->remove(*cw);
		Fl::delete_widget(cw);
		
		// if there are no more open files, set menu items appropriately
		if (tabs->children() == 0)
		{	
			changeItemFlags("&Info/Get open file &info...", FL_MENU_INACTIVE);
			changeItemFlags("&File/&Reload file", FL_MENU_INACTIVE);
			changeItemFlags("&File/&Close file", FL_MENU_INACTIVE);

			std::string title = "SteGUI";
			this->label(title.c_str());
			status->label("No open files");
			
			changeItemFlags("&File/&Save file", FL_MENU_INACTIVE);
			changeItemFlags("&File/Sa&ve as...", FL_MENU_INACTIVE);
		}
		else
		{
			std::string title = "SteGUI - ";
			title += ((CardWidget*)(tabs->value()))->getFilename().c_str();
			this->label(title.c_str());
			
			CardWidget *cw = (CardWidget*)(tabs->value());
			std::string type = cw->getDescription();
			status->label(type.c_str());
			
			if (type.find("File type: Text") == 0)
			{
				changeItemFlags("&File/&Save file", 0);
				changeItemFlags("&File/Sa&ve as...", 0);
			}
			else
			{
				changeItemFlags("&File/&Save file", FL_MENU_INACTIVE);
				changeItemFlags("&File/Sa&ve as...", FL_MENU_INACTIVE);
			}
		}
	}
}

// Return active open filename
std::string StegWindow::getOpenFilename() const
{
	CardWidget *cw = (CardWidget*)(tabs->value());
	if (cw)
		return(cw->getFilename());
	else
		return("");
}

// Set status bar label
void StegWindow::setStatus(std::string s)
{
	status->label(s.c_str());
}

// Callback for tabs
// Show image for clicked tab and change menu items
void StegWindow::tabs_cb(Fl_Widget *w, void *d)
{
	Fl_Tabs *tabs = (Fl_Tabs*)w;
	StegWindow *window = (StegWindow*)d;

	CardWidget *cw = (CardWidget*)(tabs->value());
	std::string title = "SteGUI - ";
	title += cw->getFilename();
	window->label(title.c_str());
	
	std::string type = cw->getDescription();
	if (type.find("File type: Text") == 0)
	{
		window->changeItemFlags("&File/&Save file", 0);
		window->changeItemFlags("&File/Sa&ve as...", 0);
	}	
	else
	{
		window->changeItemFlags("&File/&Save file", FL_MENU_INACTIVE);
		window->changeItemFlags("&File/Sa&ve as...", FL_MENU_INACTIVE);
	}
	
	window->setStatus(type);
}

// Save a text file
void StegWindow::saveTextFile()
{
	if (tabs->children() > 0)
	{
		TxtWidget *tw = (TxtWidget*)(tabs->value());
		tw->saveFile();
	}
}

// Save a text file under a different name
void StegWindow::saveTextFile(std::string filename)
{
	if (tabs->children() > 0)
	{
		TxtWidget *tw = (TxtWidget*)(tabs->value());
		tw->saveFile(filename);
	}
}

// Change menu items flags
void StegWindow::changeItemFlags(std::string item, int flags)
{
	const Fl_Menu_Item *probe = windowmenu->find_item(item.c_str());
	if (probe)
		windowmenu->mode((int)(probe-windowmenu->menu()), flags);
}

// Open a file by checking what type it is
void StegWindow::openFile(std::string filename)
{
	std::string desc;

	// find out what kind of file we're trying to open
	desc = Support::is_bitmap(filename);
	if (!desc.empty())
	{
		load_bitmap(filename, desc);
		return;
	}

	desc = Support::is_jpeg(filename);
	if (!desc.empty())
	{
		load_jpeg(filename, desc);
		return;
	}

	desc = Support::is_wave(filename);
	if (!desc.empty())
	{
		load_sound(filename, desc);
		return;
	}

	desc = Support::is_au(filename);
	if (!desc.empty())
	{
		load_sound(filename, desc);
		return;
	}

	struct stat statres;
	if (stat(filename.c_str(), &statres) < 0)
	{
		fl_alert("Error: unable to open file!");
		return;
	}
	
	std::stringstream str;
	str << "File type: Text - Size: " << statres.st_size << " bytes";
	desc = str.str();
	load_text(filename, desc);

	//fl_alert("Wrong file type selected, malformed file or unable to determine file type.\nSteghide may only open Bitmap, JPEG, Wave, and Au files.");
}
