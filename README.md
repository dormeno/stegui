**Wishlist Someone fork this And or Convert to Jpeg turbo** 
and or use it as a basis for another GUI , FORK ME PLEASE.... 
<p> <h2> Orginally on SF.net <h2> </p>
<p><br>This is SteGUI, a graphical front-end to Steghide.
Copyright (C) 2005,2007 by Nicola Cocchiaro <ncocchiaro [at] users.sf.net>
and released under the GNU/GPL license.
SteGUI can be found at http://www.sf.net/projects/stegui.
Steghide is Copyright (C) 2003 Stefan Hetzl</p>

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
<p class="footer"></p>

<p>
This project was born to complement the usage of 
<a href="http://steghide.sf.net">Steghide</a>, a command line 
<a href="http://en.wikipedia.org/wiki/Steganography">Steganography</a> 
program for Linux and Windows, by adding some features that could prove useful. 
The idea is that a Graphical User Interface might let users control Steghide 
in a more user-friendly way and also both display the images (in Windows BMP 
and JPG formats) and play the audio files (in Windows WAVE and Sun/NeXT AU) 
that it is able to hide data into. Using the GUI it would thus be possible to 
perform all the common command line operations, and also verify that the 
<em>embed</em> operations in images and audio files do not create variations 
that might give away the use of Steganography, which would render the whole 
effort useless. In the same way it would be possible to view or play hidden 
files that are extracted from a <em>stego file</em>, all from a single tool: 
this is exactly why SteGUI was created.
</p>

<p>
The rest of this website offers an introduction that explains some concepts 
behind Steganography in general, then shows how Steghide and SteGUI work. 
SteGUI was written in C++ with the help of the 
<a href="http://www.fltk.org">FLTK</a> and 
<a href="http://pstreams.sf.net">PStreams</a> libraries. Downloadable source 
code packages are available for download; binary packages will be available 
sometime in the future. SteGUI was written by Nicola Cocchiaro; Steghide was written by Stefan Hetzl. Both SteGUI and Steghide are released 
under the 
<a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License</a>.
</p>

<p>
Any help in the form of patches, documentation or comments is welcome, or you 
can 
<a href="http://sourceforge.net/donate/index.php?group_id=135970">donate</a> 
through SourceForge to show your appreciation for the work done to this project 
and encourage further development :)
</p>

<p>
Feel free to write, if you have any questions or comments, to:
</p>

<img src="images/ind3.png" alt="E-mail adress image">

<p class="footer"></p>

<h3>Table of contents</h3>
<ul id="index">
	<li><a href="intro.html">Introduction</a>
	<ul>
		<li><a href="intro.html#steg">Steganography</a></li>
		<li><a href="intro.html#soft">Steganography in software</a>
		<ul>
			<li><a href="intro.html#img">Digital images as cover files</a></li>
			<li><a href="intro.html#audio">Digital audio as cover files</a></li>
			<li><a href="intro.html#related">Related software</a></li>
		</ul>
		</li>
	</ul>
	</li>
	<li><a href="steghide.html">Steghide</a>
	<ul>
		<li><a href="steghide.html#funz">Steghide features</a>
		<ul>
			<li><a href="steghide.html#embed">Embed</a></li>
			<li><a href="steghide.html#extract">Extract</a></li>
			<li><a href="steghide.html#info">Information on files</a></li>
		</ul>
		</li>
		<li><a href="steghide.html#tecniche">Techniques employed</a></li>
	</ul>
	</li>
	<li><a href="frontend.html">SteGUI</a>
	<ul>
		<li><a href="frontend.html#lib">The libraries used</a></li>
		<li><a href="frontend.html#gui">Interfacing with Steghide</a>
		<ul>
			<li><a href="frontend.html#embed">Embed</a></li>
			<li><a href="frontend.html#extract">Extract</a></li>
			<li><a href="frontend.html#info">Information on files</a></li>
		</ul>
		</li>
	</ul>
	</li>
	<li><a href="download.html">Download</a>
	<ul>
		<li><a href="download.html#req">System requirements</a></li>
		<li><a href="download.html#pkg">Downloadable packages</a></li>
		<li><a href="download.html#link">Links</a>
		<ul>
			<li><a href="download.html#guilib">Libraries used by SteGUI</a></li>
			<li><a href="download.html#libsteg">Libraries used by Steghide</a></li>
			<li><a href="download.html#steg">Steganography</a></li>
		</ul>
		</li>
	</ul>
	</li>
</ul>

<div>
<a href="intro.html">Next</a> - Previous - <a href="index.html">Home</a><br/>

<a class="right" href="http://sourceforge.net"><img class="icon" src="http://sourceforge.net/sflogo.php?group_id=135970&amp;type=1" width="88" height="31" alt="SourceForge.net Logo" /></a>
<a class="right" href="http://sourceforge.net/donate/index.php?group_id=135970"><img class="icon" src="http://images.sourceforge.net/images/project-support.jpg" width="88" height="32" border="0" alt="Support This Project" /></a>
<a class="right" href="http://validator.w3.org/check?uri=referer"><img class="icon" src="http://www.w3.org/Icons/valid-xhtml11" alt="Valid XHTML 1.1" height="31" width="88" /></a>
<a class="right" href="http://jigsaw.w3.org/css-validator/check/referer"><img class="icon" src="http://jigsaw.w3.org/css-validator/images/vcss" alt="Valid CSS!" height="31" width="88" /></a>
</div>

<div>
<h5><em>&copy; 2005-2008 Nicola Cocchiaro</em></h5>
</div>
