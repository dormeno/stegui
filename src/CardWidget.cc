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

// CardWidget.cc
// This implements a generic widget to be displayed in a SteGUI tab. Any 
// widget that deals with a particular data format to be displayed should 
// subclass CardWidget

#include "CardWidget.h"

// CardWidget constructor
CardWidget::CardWidget(int x, int y, int w, int h, std::string f)
	: Fl_Group(x, y, w, h, fl_filename_name(f.c_str())),
	scroll(x, y, w, h),
	ibox(FL_NO_BOX, x, y, w, h, NULL),
	filename(f)
{
	ibox.color(fl_darker(FL_WHITE));
        scroll.color(fl_darker(FL_WHITE));
        scroll.end();

	this->labelsize(12);
	this->resizable(ibox);
	this->selection_color(fl_darker(FL_GRAY));
	this->color(fl_darker(FL_WHITE));
}

// CardWidget destructor (everything is destroyed by FLTK)
CardWidget::~CardWidget()
{
}

// Set filename for this widget
void CardWidget::setFilename(std::string f)
{
	filename = f;
}

// Set description for this widget (will be shown in status bar)
void CardWidget::setDescription(std::string d)
{
	description = d;
}

// Get filename for this widget
std::string CardWidget::getFilename() const
{
	return(filename);
}

// Get description for this widget
std::string CardWidget::getDescription() const
{
	return(description);
}
