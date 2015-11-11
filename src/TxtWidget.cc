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

// TxtWidget.cc
// This subclass of CardWidget deals with displaying text files

#include "TxtWidget.h"

// TxtWidget constructor
TxtWidget::TxtWidget(int x, int y, int w, int h, std::string f)
	: CardWidget(x, y, w, h, f),
	editor(x, y, w, h),
	modified(false)
{
	tbuffer.loadfile(f.c_str());
	tbuffer.add_modify_callback(modify_cb, this);
	editor.buffer(tbuffer);
	editor.textfont(FL_COURIER);
	this->end();
}

// TxtWidget destructor
TxtWidget::~TxtWidget()
{
	tbuffer.remove_modify_callback(modify_cb, this);
}

// Save buffered file
void TxtWidget::saveFile()
{
	if (tbuffer.savefile(filename.c_str()))
		fl_alert("Unable to save there!");
	else
		modified = false;
}

// Save buffered file under a different name
void TxtWidget::saveFile(std::string newfile)
{
	FILE *test = fopen(newfile.c_str(), "r");
	if (test)
	{
		fclose(test);
		std::string question = "File ";
		question += newfile;
		question += " already exists. Overwrite?";
		int ans = fl_choice(question.c_str(), "Cancel", "Overwrite", NULL);
		if (ans)
		{
			if (tbuffer.savefile(newfile.c_str()))
				fl_alert("Unable to save there!");
			else
				modified = false;
		}
	}
	else
	{
		if (tbuffer.savefile(newfile.c_str()))
			fl_alert("Unable to save there!");
		else
			modified = false;
	}
}

// Check if buffered file was modified
bool TxtWidget::isModified() const
{
	return(modified);
}

// Set modified status of buffered file
void TxtWidget::setModified(bool b)
{
	modified = b;
}

// Callback for when buffered file is modified
void TxtWidget::modify_cb(int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg)
{
	TxtWidget *tw = (TxtWidget*)cbArg;
	
	if (!tw->isModified())
		tw->setModified(true);
}
