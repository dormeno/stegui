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
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([SteGUI], [0.0.2], [ncocchiaro@users.sourceforge.net])
AM_INIT_AUTOMAKE([-Wall -Werror foreign dist-bzip2])
AC_CONFIG_SRCDIR([src/Callback.cc])
AM_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CXXCPP
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_CC_C_O
AM_PROG_CC_C_O

# Checks for libraries.
AC_CHECK_LIB([asound], [snd_pcm_open],, AC_MSG_ERROR([libasound missing]))
#AC_CHECK_LIB([m], [main])
AC_CHECK_LIB([pthread], [pthread_create],, AC_MSG_ERROR([libpthread missing]))
AC_CHECK_LIB([fltk], [fl_display],, AC_MSG_ERROR([libfltk missing]))
AC_CHECK_LIB([fltk_images], [main],, AC_MSG_ERROR([libfltk_images missing]))

# Checks for header files.
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([fcntl.h limits.h malloc.h stdlib.h string.h sys/time.h unistd.h alsa/asoundlib.h],, AC_MSG_ERROR([required header file missing]))

# Checks for typedefs, structures, and compiler characteristics.
#AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_CHECK_FUNCS([dup2 gettimeofday memmove])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
