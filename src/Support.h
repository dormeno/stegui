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

// Support.h
// Support methods header file

#ifndef SUPPORT_H
#define SUPPORT_H

#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <jpeglib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pstreams/pstream.h"
#include "MsgWindow.h"
#include "formats.h"

#define CHECK_READ(a) if(a<1)return("");

class Support
{
public:
	static std::string* run_command(const char *command);
	static std::string* run_command_err(const char *command);
	static void get_info(const char *filename);
	static std::string is_bitmap(std::string filename);
	static std::string is_jpeg(std::string filename);
	static std::string is_wave(std::string filename);
	static std::string is_au(std::string filename);

private:
	typedef struct
	{
		unsigned short type;
		unsigned long size;
		unsigned short res1;
		unsigned short res2;
		unsigned long offset;
	} bitmapheader;

	typedef struct
	{
		unsigned long size;
		signed long width;
		signed long height;
		unsigned short planes;
		unsigned short bitcount;
		unsigned long compression;
		unsigned long sizeimage;
		signed long xpelspermeter;
		signed long ypelspermeter;
		unsigned long clrused;
		unsigned long clrimportant;
	} bitmapinfoheader;
	
	typedef struct
	{
		unsigned long size;
		unsigned short width;
		unsigned short height;
		unsigned short planes;
		unsigned short bitcount;
	} bitmapcoreheader ;

	typedef struct
	{
		char magic[2];
	} jpegheader;
};

#endif
