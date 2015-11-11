###############################################################################
##
##   This is SteGUI, a graphical front-end to Steghide.
##   SteGUI can be found at http://www.sf.net/projects/stegui.
##   Copyright (C) 2005,2007 by Nicola Cocchiaro <ncocchiaro@users.sf.net>
##
##   You will need Steghide to run SteGUI, you can get it at 
##   http://steghide.sf.net. Steghide is Copyright (C) 2003 Stefan Hetzl.
##
##   This program is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation; either version 2 of the License, or
##   (at your option) any later version.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public License
##   along with this program; if not, write to the Free Software
##   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
##
###############################################################################
## Process this file with automake to produce Makefile.in

CXXBASEFLAGS= -Wall -pedantic -g -ggdb -O3
CBASEFLAGS= -g -ggdb -O3

AM_CXXFLAGS=$(CXXBASEFLAGS)
AM_CFLAGS=$(CBASEFLAGS)
AM_LDFLAGS=
AM_CPPFLAGS=

## stegui target
bin_PROGRAMS=stegui
stegui_SOURCES=Callback.cc CardWidget.cc EmbedWindow.cc ExtractWindow.cc ImgWidget.cc MsgWindow.cc PlayerPanel.cc SndWidget.cc SteGUI.cc StegWindow.cc Support.cc TxtWidget.cc Player.c pstreams/pstream.h Callback.h CardWidget.h EmbedWindow.h ExtractWindow.h ImgWidget.h MsgWindow.h Player.h PlayerPanel.h SndWidget.h SteGUI.h StegWindow.h Support.h TxtWidget.h formats.h
stegui_CXXFLAGS=$(AM_CXXFLAGS)
stegui_CFLAGS=$(AM_CFLAGS)
stegui_LDFLAGS=$(AM_LDFLAGS)
stegui_CPPFLAGS=$(AM_CPPFLAGS)
