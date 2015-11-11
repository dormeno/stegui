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

// TxtWidget.h
// TxtWidget header file

#ifndef TXTWIDGET_H
#define TXTWIDGET_H

#include <FL/filename.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/fl_ask.H>
#include <string>
#include <cstdio>
#include <pthread.h>
#include "CardWidget.h"

class TxtWidget : public CardWidget
{
public:
	TxtWidget(int x, int y, int w, int h, std::string f);
	~TxtWidget();

	void saveFile();
	void saveFile(std::string newfile);
	bool isModified() const;
	void setModified(bool b);
	
	static void modify_cb(int pos, int nInserted, int nDeleted, int nRestyled, const char* deletedText, void* cbArg);
		
private:
	Fl_Text_Editor editor;
	Fl_Text_Buffer tbuffer;
	bool modified;
};

#endif
