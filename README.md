This is SteGUI, a graphical front-end to Steghide.
Copyright (C) 2005,2007 by Nicola Cocchiaro <ncocchiaro [at] users.sf.net>
and released under the GNU/GPL license.
SteGUI can be found at http://www.sf.net/projects/stegui.
Steghide is Copyright (C) 2003 Stefan Hetzl

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

--------------------------------------------------------------------------------

SteGUI README file
Get SteGUI at http://stegui.sf.net and Steghide at http://steghide.sf.net


Basic instruction for compiling and running SteGUI

SteGUI runs on GNU/Linux systems only for the moment (due to Pstreams and ALSA 
support).
Before you compile SteGUI you will need to have installed the development 
headers for:

- FLTK >= 1.1.6
- ALSA
- Libjpeg

and Steghide >= 0.5.1 installed.

To compile SteGUI type:

$ make all

After that you can run SteGUI with:

$ bin/steGUI

Enjoy!
