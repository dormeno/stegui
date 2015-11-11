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

// EmbedWindow.cc
// This implements the window widget used to embed data in a file

#include "EmbedWindow.h"

// Menu items for encryption modes
Fl_Menu_Item EmbedWindow::encryptModeMenuItems[] = {

	{ "cbc", 0, EmbedWindow::setEncMode, 0, 0 },
	{ "cfb", 0, EmbedWindow::setEncMode, 0, 0 },
	{ "ctr", 0, EmbedWindow::setEncMode, 0, 0 },
	{ "ecb", 0, EmbedWindow::setEncMode, 0, 0 },
	{ "ncfb", 0, EmbedWindow::setEncMode, 0, 0 },
	{ "nofb", 0, EmbedWindow::setEncMode, 0, 0 },
	{ "ofb", 0, EmbedWindow::setEncMode, 0, 0 },
	{ 0 }
};

// Menu items for stream encryption modes
Fl_Menu_Item EmbedWindow::encryptStreamModeItems[] = {
	
	{ "stream", 0, EmbedWindow::setEncMode, 0, 0 },
	{ 0 }
};

// Menu items for compression modes
Fl_Menu_Item EmbedWindow::compressMenuItems[] = {

	{ "1", 0, EmbedWindow::setCompression, 0, 0 },
	{ "2", 0, EmbedWindow::setCompression, 0, 0 },
	{ "3", 0, EmbedWindow::setCompression, 0, 0 },
	{ "4", 0, EmbedWindow::setCompression, 0, 0 },
	{ "5", 0, EmbedWindow::setCompression, 0, 0 },
	{ "6", 0, EmbedWindow::setCompression, 0, 0 },
	{ "7", 0, EmbedWindow::setCompression, 0, 0 },
	{ "8", 0, EmbedWindow::setCompression, 0, 0 },
	{ "9", 0, EmbedWindow::setCompression, 0, 0 },
	{ 0 }
};
	
// Embed window constructor (takes pre-built File_Choosers
EmbedWindow::EmbedWindow(std::string currentFile, Fl_File_Chooser *e, Fl_File_Chooser *c, Fl_File_Chooser *s)
	: Fl_Window(EmbedWindow::WIDTH, EmbedWindow::HEIGHT, "Choose embedding options")
{
	try {
		embedChooser = e;
		coverChooser = c;
		stegoChooser = s;

		// embed file widgets
		embedFile = new Fl_File_Input(8, 25, 550, 35, "File to embed in cover file:");
		embedFile->align(FL_ALIGN_TOP_LEFT);
		embedFile->labelsize(12);
		embedFile->textsize(12);

		embedChooser->callback(displayfile, (void*)embedFile);

		embedButton = new Fl_Button(565, 35, 25, 25);
		embedButton->labelcolor(FL_YELLOW);
		embedButton->callback((Fl_Callback*)pickfile, embedChooser);
		embedButton->tooltip("Choose file to embed");
		
		embedIcon = Fl_File_Icon::find(".", Fl_File_Icon::DIRECTORY);
		embedIcon->label(embedButton);

		// cover file widgets
		coverFile = new Fl_File_Input(8, 85, 550, 35, "File to use as cover:");
		if (!currentFile.empty())
			coverFile->value(currentFile.c_str());
		coverFile->align(FL_ALIGN_TOP_LEFT);
		coverFile->labelsize(12);
		coverFile->textsize(12);

		coverChooser->callback(displayfile, (void*)coverFile);

		coverButton = new Fl_Button(565, 95, 25, 25);
		coverButton->labelcolor(FL_YELLOW);
		coverButton->callback((Fl_Callback*)pickfile, coverChooser);
		coverButton->tooltip("Choose cover file");
		
		coverIcon = Fl_File_Icon::find(".", Fl_File_Icon::DIRECTORY);
		coverIcon->label(coverButton);
		
		// stego file widgets
		stegoFile = new Fl_File_Input(8, 145, 550, 35, "File to use as output stegofile:");
		if (!currentFile.empty())
			stegoFile->value(displayDir(currentFile).c_str());
		stegoFile->align(FL_ALIGN_TOP_LEFT);
		stegoFile->labelsize(12);
		stegoFile->textsize(12);

		stegoChooser->callback(displayfile, (void*)stegoFile);

		stegoButton = new Fl_Button(565, 155, 25, 25);
		stegoButton->labelcolor(FL_YELLOW);
		stegoButton->callback((Fl_Callback*)pickfile, stegoChooser);
		stegoButton->tooltip("Choose output stegofile");
		
		stegoIcon = Fl_File_Icon::find(".", Fl_File_Icon::DIRECTORY);
		stegoIcon->label(stegoButton);

		// encryption options
		encryptCheck = new Fl_Check_Button(18, 195, 130, 25, "Use encryption");
		encryptCheck->value(1);
		encryptCheck->callback(encryptCallback, this);
		encryptCheck->tooltip("Choose whether to encrypt embedded data");
		encryptCheck->labelsize(12);

		encryptModeMenu = new Fl_Menu_Button(378, 195, 180, 25, "Encryption mode");
		encryptModeMenu->textsize(12);
		encryptModeMenu->labelsize(12);
		
		// Menu items for encryption algorithms
		Fl_Menu_Item encryptMenuItems[] = {

			{ "cast-128", 0, setEncryption, encryptModeMenu, 0 },
			{ "gost", 0, setEncryption, encryptModeMenu, 0 },
			{ "rijndael-128", 0, setEncryption, encryptModeMenu, 0 },
			{ "twofish", 0, setEncryption, encryptModeMenu, 0 },
			{ "arcfour", 0, setEncryption, encryptModeMenu, 0 },
			{ "cast-256", 0, setEncryption, encryptModeMenu, 0 },
			{ "loki97", 0, setEncryption, encryptModeMenu, 0 },
			{ "rijndael-192", 0, setEncryption, encryptModeMenu, 0 },
			{ "saferplus", 0, setEncryption, encryptModeMenu, 0 },
			{ "wake", 0, setEncryption, encryptModeMenu, 0 },
			{ "des", 0, setEncryption, encryptModeMenu, 0 },
			{ "rijndael-256", 0, setEncryption, encryptModeMenu, 0 },
			{ "serpent", 0, setEncryption, encryptModeMenu, 0 },
			{ "xtea", 0, setEncryption, encryptModeMenu, 0 },
			{ "blowfish", 0, setEncryption, encryptModeMenu, 0 },
			{ "enigma", 0, setEncryption, encryptModeMenu, 0 },
			{ "rc2", 0, setEncryption, encryptModeMenu, 0 },
			{ "tripledes", 0, setEncryption, encryptModeMenu, 0 },
			{ 0 }
		};
		
		encryptModeMenu->copy(EmbedWindow::encryptModeMenuItems);
		encryptModeMenu->tooltip("Choose encryption mode");
		const Fl_Menu_Item *defaultEncMode = encryptModeMenu->find_item("cbc");
		if (defaultEncMode)
		{
			encryptModeMenu->value(defaultEncMode);
			encryptModeMenu->label(defaultEncMode->label());
		}
		
		encryptMenu = new Fl_Menu_Button(168, 195, 190, 25, "Encryption algorithm");
		encryptMenu->copy(encryptMenuItems);
		const Fl_Menu_Item *defaultEnc = encryptMenu->find_item("rijndael-128");
		if (defaultEnc)
		{
			encryptMenu->value(defaultEnc);
			encryptMenu->label(defaultEnc->label());
		}
		encryptMenu->tooltip("Choose encryption algorithm to use");
		encryptMenu->textsize(12);
		encryptMenu->labelsize(12);

		// compression options
		compressCheck = new Fl_Check_Button(18, 235, 150, 25, "Use compression");
		compressCheck->value(1);
		compressCheck->callback(compressCallback, this);
		compressCheck->tooltip("Choose wether to compress embedded data");
		compressCheck->labelsize(12);

		compBox = new Fl_Box(260, 235, 200, 25, "Compression level (1 fast, 9 best):");
		compBox->labelsize(12);

		compressMenu = new Fl_Menu_Button(488, 235, 70, 25, "Compression level");
		compressMenu->copy(EmbedWindow::compressMenuItems);
		const Fl_Menu_Item *defaultComp = compressMenu->find_item("9");
		if (defaultEnc)
		{
			compressMenu->value(defaultComp);
			compressMenu->label(defaultComp->label());
		}
		compressMenu->tooltip("Choose compression level");
		compressMenu->textsize(12);
		compressMenu->labelsize(12);
		
		// other options
		filenameCheck = new Fl_Check_Button(18, 275, 150, 25, "Embed file name");
		filenameCheck->value(1);
		filenameCheck->tooltip("Choose whether to embed filename");
		filenameCheck->labelsize(12);

		checksumCheck = new Fl_Check_Button(188, 275, 180, 25, "Embed file checksum");
		checksumCheck->value(1);
		checksumCheck->tooltip("Choose whether to embed file checksum");
		checksumCheck->labelsize(12);

		forceCheck = new Fl_Check_Button(388, 275, 170, 25, "Overwrite output file");
		forceCheck->value(0);
		forceCheck->tooltip("Overwrite output file if already existent");
		forceCheck->labelsize(12);
				
		// passphrase
		passphraseInput = new Fl_Secret_Input(8, 325, 550, 25, "Passphrase:");
		passphraseInput->align(FL_ALIGN_TOP_LEFT);
		passphraseInput->labelsize(12);
		passphraseInput->textsize(12);
		
		// bottom buttons
		okButton = new Fl_Return_Button(427, 360, 140, 25, "OK");
		okButton->callback((Fl_Callback*)okCallback, this);
		okButton->tooltip("Embed file");
		okButton->labelsize(12);
		
		cancelButton = new Fl_Button(252, 360, 140, 25, "Cancel");
		cancelButton->callback((Fl_Callback*)cancelCallback, this);
		cancelButton->tooltip("Cancel operation");
		cancelButton->labelsize(12);

		this->end();
		this->callback(closeWindow);
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to initialize embed window, aborting." << std::endl;
		exit(1);
	}
}

// Embed window destructor (everything destroyed by FLTK)
EmbedWindow::~EmbedWindow()
{
}

// Toggle encryption use
void EmbedWindow::toggleEncryption(bool state)
{
	if (state)
	{
		encryptMenu->activate();
		encryptModeMenu->activate();
	}
	else
	{
		encryptMenu->deactivate();
		encryptModeMenu->deactivate();
	}
}

// Toggle compression use
void EmbedWindow::toggleCompression(bool state)
{
	if (state)
		compressMenu->activate();
	else
		compressMenu->deactivate();
}

// Get path substring for File_Input set value
std::string EmbedWindow::displayDir(std::string filename)
{
	unsigned int pos = filename.find_last_of('/');
	if (pos != std::string::npos)
	{
		std::string tmp = filename.substr(0, pos+1);
		return(tmp);
	}
	return(filename);
}

// Parse options from window widgets and build command line for steghide
std::string EmbedWindow::parseOptions()
{
	std::string command = "steghide --embed";
	std::string file = embedFile->value();
	if (file.empty())
	{
		fl_alert("You must choose a file to embed.");
		return("");
	}
	else if (file == "-")
	{
		fl_alert("Invalid embed file name \"-\". Cannot read from stdin.");
		return("");
	}
	file = coverFile->value();
	if (file.empty())
	{
		fl_alert("You must choose a cover file.");
		return("");
	}
	else if (file == "-")
	{
		fl_alert("Invalid cover file name \"-\". Cannot read from stdin.");
		return("");
	}
	file = stegoFile->value();
	if (file.empty())
	{
		fl_alert("You must choose an output file.");
		return("");
	}
	else if (file == "-")
	{
		fl_alert("Invalid stego file name \"-\". Cannot write to stdout.");
		return("");
	}
	// check if stego file exists
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
	command += " -ef ";
	command += embedFile->value();
	command += " -cf ";
	command += coverFile->value();
	command += " -sf ";
	command += stegoFile->value();
	command += " -p ";
	if (passphraseInput->value())
	{
		command += "\"";
		command += passphraseInput->value();
		command += "\"";
	}	
	else
		command += "\"\"";
	command += " -e ";
	if ((int)encryptCheck->value())
	{
		command += encryptMenu->mvalue()->label();
		command += " ";
		command += encryptModeMenu->mvalue()->label();
	}
	else
		command += "none";
	if ((int)compressCheck->value())
	{
		command += " -z ";
		command += compressMenu->label();
	}
	else
		command += " -Z";
	if (!(int)filenameCheck->value())
		command += " -K";
	if (!(int)checksumCheck->value())
		command += " -N";
	if ((int)forceCheck->value())
		command += " -f";

	return(command);
}

// Callbacks

// Callback for close window event
void EmbedWindow::closeWindow(Fl_Widget *w, void *d)
{
	EmbedWindow *window = (EmbedWindow*)w;
	Fl::delete_widget(window);
}

// Callback for file chosen callback
void EmbedWindow::pickfile(Fl_Widget *w, void *d)
{
	Fl_File_Chooser *chooser = (Fl_File_Chooser*)d;
	
	chooser->show();
	while (chooser->visible())
		Fl::wait();
}

// Callback for File_Input set value
void EmbedWindow::displayfile(Fl_File_Chooser *chooser, void *d)
{
	Fl_File_Input *input = (Fl_File_Input*)d;

	input->value(chooser->value());
	input->set_changed();
}

// Callback for encryptCheck
void EmbedWindow::encryptCallback(Fl_Widget *w, void *d)
{
	Fl_Check_Button *check = (Fl_Check_Button*)w;
	EmbedWindow *window = (EmbedWindow*)d;

	if ((int)(check->value()))
		window->toggleEncryption(true);
	else
		window->toggleEncryption(false);
}

// Callback for encryptionMenu
void EmbedWindow::setEncryption(Fl_Widget *w, void *d)
{
	Fl_Menu_Button *encMenu = (Fl_Menu_Button*)w;
	Fl_Menu_Button *encMode = (Fl_Menu_Button*)d;

	// change encryption mode menu according to encryption algorithm
	encMenu->label(encMenu->mvalue()->label());
	int index = (int)(encMenu->mvalue()-encMenu->menu());
	if ((index == 4) || (index == 9) || (index == 15))
	{
		encMode->copy(EmbedWindow::encryptStreamModeItems);
		const Fl_Menu_Item *defaultEnc = encMode->find_item("stream");
		if (defaultEnc)
		{
			encMode->value(defaultEnc);
			encMode->label(defaultEnc->label());
		}
	}
	else
	{
		encMode->copy(EmbedWindow::encryptModeMenuItems);
		const Fl_Menu_Item *defaultEnc = encMode->find_item("cbc");
		if (defaultEnc)
		{
			encMode->value(defaultEnc);
			encMode->label(defaultEnc->label());
		}
	}
}

// Callback for encryptionModeMenu
void EmbedWindow::setEncMode(Fl_Widget *w, void *d)
{
	Fl_Menu_Button *menu = (Fl_Menu_Button*)w;

	menu->label(menu->mvalue()->label());
}

// Callback for compression toggle
void EmbedWindow::compressCallback(Fl_Widget *w, void *d)
{
	Fl_Check_Button *check = (Fl_Check_Button*)w;
	EmbedWindow *window = (EmbedWindow*)d;

	if ((int)(check->value()))
		window->toggleCompression(true);
	else
		window->toggleCompression(false);
}

// Callback for compression mode menu
void EmbedWindow::setCompression(Fl_Widget *w, void *d)
{
	Fl_Menu_Button *compMenu = (Fl_Menu_Button*)w;

	compMenu->label(compMenu->mvalue()->label());
	compMenu->value(compMenu->mvalue());
}

// Callback for OK button
void EmbedWindow::okCallback(Fl_Widget *w, void *d)
{
	EmbedWindow *window = (EmbedWindow*)d;

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
		window->hide();
		Fl::delete_widget(window);
	}
}

// Callback for Cancel button
void EmbedWindow::cancelCallback (Fl_Widget *w, void *d)
{
	EmbedWindow *window = (EmbedWindow*)d;

	window->hide();
	Fl::delete_widget(window);
}
