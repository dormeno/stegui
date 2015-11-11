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

// SteGUI.cc
// main source file

#include "SteGUI.h"

// main function
int main(int argc, char **argv)
{
	try {
		// check if steghide is installed (trivial)
		redi::ipstream in("steghide --version", redi::pstream::pstderr);
		std::string str;
		std::getline(in.err(), str);
		if (!str.empty())
		{
			std::cerr << "Error: unable to find Steghide binary." << std::endl 
				<< "Please install Steghide (http://steghide.sf.net) and try again."
				<< std::endl;
			exit(1);
		}

		// set FLTK stuff and run program
		Fl::visual(FL_DOUBLE|FL_INDEX);
		Fl::scheme("none");
		Fl_File_Icon::load_system_icons();
		fl_message_font(FL_HELVETICA, 12);
		StegWindow window(800, 600, "SteGUI");
		window.show(argc, argv);

		return(Fl::run());
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Uncaught exception, aborting." << std::endl;
		exit(1);
	}
}
