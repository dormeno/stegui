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

// SteGUI.h
// main source header file

#ifndef STEGUI_H
#define STEGUI_H

#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_File_Icon.H>
#include <FL/fl_ask.H>
#include <FL/Enumerations.H>
#include <iostream>
#include "pstreams/pstream.h"
#include "StegWindow.h"
#include "Callback.h"

#define VERSION "0.0.2"

class SteGUI
{
public:
	int main(int argc, char **argv);
};

#endif
