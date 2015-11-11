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

// CardWidget.h
// Generic displayable widget header file

#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/filename.H>
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <string>

class CardWidget : public Fl_Group
{
public:	
	CardWidget(int x, int y, int w, int h, std::string f);
	~CardWidget();
	
	void setFilename(std::string f);
	void setDescription(std::string d);
	std::string getFilename() const;
	std::string getDescription() const;
	
protected:
	Fl_Scroll scroll;
	Fl_Box ibox;
	std::string filename;
	std::string description;
};

#endif
