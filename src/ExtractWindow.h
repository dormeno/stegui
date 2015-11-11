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

// ExtractWindow.h
// ExtractWindow widget header file

#ifndef EXTRACTWINDOW_H
#define EXTRACTWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Icon.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Secret_Input.H>
#include <string>
#include <iostream>
#include <cstdio>
#include "MsgWindow.h"
#include "Support.h"

class ExtractWindow : public Fl_Window
{
public:
	ExtractWindow(std::string currentFile, Fl_File_Chooser *s, Fl_File_Chooser *e);
	~ExtractWindow();
	
	std::string displayDir(std::string filename);
	std::string parseOptions();

	// Callbacks
	static void closeWindow(Fl_Widget *w, void *d);
	static void pickfile(Fl_Widget *w, void *d);
	static void displayfile(Fl_File_Chooser *w, void *d);
	static void okCallback(Fl_Widget *w, void *d);
	static void cancelCallback(Fl_Widget *w, void *d);

private:
	static const int WIDTH = 600;
	static const int HEIGHT = 260;
	
	Fl_File_Chooser *stegoChooser, *extractChooser;
	Fl_File_Input *stegoFile, *extractFile;
	Fl_Button *stegoButton, *extractButton;
	Fl_File_Icon *stegoIcon, *extractIcon;
	Fl_Check_Button *forceCheck;
	Fl_Return_Button *okButton;
	Fl_Button *cancelButton;
	Fl_Secret_Input *passphraseInput;

};

#endif
