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

// ExtractWindow.cc
// This implements the window widget used to extract data from a file

#include "ExtractWindow.h"

// Extract window constructor
ExtractWindow::ExtractWindow(std::string currentFile, Fl_File_Chooser *s, Fl_File_Chooser *e)
	: Fl_Window(ExtractWindow::WIDTH, ExtractWindow::HEIGHT, "Choose extracting options")
{
	try {
		stegoChooser = s;
		extractChooser = e;

		// stego file widgets
		stegoFile = new Fl_File_Input(8, 25, 550, 35, "Stegofile to use as input:");
		if (!currentFile.empty())
			stegoFile->value(currentFile.c_str());
		stegoFile->align(FL_ALIGN_TOP_LEFT);
		stegoFile->labelsize(12);
		stegoFile->textsize(12);

		stegoChooser->callback(displayfile, (void*)stegoFile);

		stegoButton = new Fl_Button(565, 35, 25, 25);
		stegoButton->labelcolor(FL_YELLOW);
		stegoButton->callback((Fl_Callback*)pickfile, stegoChooser);
		stegoButton->tooltip("Choose input stego file");
		
		stegoIcon = Fl_File_Icon::find(".", Fl_File_Icon::DIRECTORY);
		stegoIcon->label(stegoButton);

		// extract file widgets
		extractFile = new Fl_File_Input(8, 85, 550, 35, "File to extract to:");
		if (!currentFile.empty())
			extractFile->value(displayDir(currentFile).c_str());
		extractFile->align(FL_ALIGN_TOP_LEFT);
		extractFile->labelsize(12);
		extractFile->textsize(12);

		extractChooser->callback(displayfile, (void*)extractFile);

		extractButton = new Fl_Button(565, 85, 25, 25);
		extractButton->labelcolor(FL_YELLOW);
		extractButton->callback((Fl_Callback*)pickfile, extractChooser);
		extractButton->tooltip("Choose file to extract");
		
		extractIcon = Fl_File_Icon::find(".", Fl_File_Icon::DIRECTORY);
		extractIcon->label(extractButton);

		// other options
		forceCheck = new Fl_Check_Button(18, 135, 170, 25, "Overwrite output file");
		forceCheck->value(0);
		forceCheck->tooltip("Overwrite output file if already existent");
		forceCheck->labelsize(12);
				
		// passphrase
		passphraseInput = new Fl_Secret_Input(8, 185, 550, 25, "Passphrase:");
		passphraseInput->align(FL_ALIGN_TOP_LEFT);
		passphraseInput->labelsize(12);
		passphraseInput->textsize(12);
		
		// bottom buttons
		okButton = new Fl_Return_Button(427, 220, 140, 25, "OK");
		okButton->callback((Fl_Callback*)okCallback, this);
		okButton->tooltip("Extract file");
		okButton->labelsize(12);
		
		cancelButton = new Fl_Button(252, 220, 140, 25, "Cancel");
		cancelButton->callback((Fl_Callback*)cancelCallback, this);
		cancelButton->tooltip("Cancel operation");
		cancelButton->labelsize(12);

		this->end();
		this->callback(closeWindow);
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to initialize extract window, aborting." << std::endl;
		exit(1);
	}
}

// Extract window destructor (everything is destroyed by FLTK)
ExtractWindow::~ExtractWindow()
{
}

// Get path substring for File_Input set value
std::string ExtractWindow::displayDir(std::string filename)
{
	unsigned int pos = filename.find_last_of('/');
	if (pos != std::string::npos)
	{
		std::string tmp = filename.substr(0, pos+1);
		return(tmp);
	}
	return(filename);
}

// Parse options from window widgets
std::string ExtractWindow::parseOptions()
{
	std::string command = "steghide --extract";
	std::string file = stegoFile->value();
	if (file.empty())
	{
		fl_alert("You must choose an input stegofile.");
		return("");
	}
	else if (file == "-")
	{
		fl_alert("Invalid stego file name \"-\". Cannot read from stdin.");
		return("");
	}
	file = extractFile->value();
	if (file.empty())
	{
		fl_alert("You must choose a file to extract.");
		return("");
	}
	else if (file == "-")
	{
		fl_alert("Invalid extract file name \"-\". Cannot write to stdout.");
		return("");
	}
	// check if extract file exists
	else if (!(int)forceCheck->value())
	{
		FILE *test = fopen(file.c_str(), "rb");
		if (test)
		{
			fclose(test);
			std::string question = "File ";
			question += file;
			question += " already exists. Overwrite?";
			int ans = fl_choice(question.c_str(), "Cancel", "Overwrite", NULL);
			if (ans)
				forceCheck->value(1);
			else
				return("");
		}
	}
	command += " -sf ";
	command += stegoFile->value();
	command += " -xf ";
	command += extractFile->value();
	command += " -p ";
	if (passphraseInput->value())
	{
		command += "\"";
		command += passphraseInput->value();
		command += "\"";
	}	
	else
		command += "\"\"";
	if ((int)forceCheck->value())
		command += " -f";

	return(command);
}

// Callbacks

// Callback for close window event
void ExtractWindow::closeWindow(Fl_Widget *w, void *d)
{
	ExtractWindow *window = (ExtractWindow*)w;
	Fl::delete_widget(window);
}

// Callback for showing file chooser
void ExtractWindow::pickfile(Fl_Widget *w, void *d)
{
	Fl_File_Chooser *chooser = (Fl_File_Chooser*)d;
	
	chooser->show();
	while (chooser->visible())
		Fl::wait();
}

// Callback for chosen file display
void ExtractWindow::displayfile(Fl_File_Chooser *chooser, void *d)
{
	Fl_File_Input *input = (Fl_File_Input*)d;

	input->value(chooser->value());
}

// Callback for OK button
void ExtractWindow::okCallback(Fl_Widget *w, void *d)
{
	ExtractWindow *window = (ExtractWindow*)d;

	window->hide();
	std::string command = window->parseOptions();
	if (command.empty())
	{
		window->show();
		return;
	}
	// if we have a valid command line, pass it to steghide
	else
	{
		//std::cout << command << std::endl;
		std::string *str = Support::run_command_err(command.c_str());
		if (!str->empty())
		{
			try {
				MsgWindow *msg = new MsgWindow(600, 100, "Steghide message", *str, "!");
				while (msg->visible())
					Fl::wait();
			}
			catch (std::exception &e) {
				std::cerr << "Exception thrown: " << e.what() << std::endl;
				std::cerr << "Unable to initialize message window, aborting." << std::endl;
				exit(1);
			}
		}
		delete str;
		Fl::delete_widget(window);
	}
}

// Callback for Cancel button
void ExtractWindow::cancelCallback (Fl_Widget *w, void *d)
{
	ExtractWindow *window = (ExtractWindow*)d;

	window->hide();
	Fl::delete_widget(window);
}
