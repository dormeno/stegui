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

// Support.cc
// Support methods to run commands through Steghide and identify data formats

#include "Support.h"

// Run command through Steghide using Pstreams
std::string* Support::run_command(const char *command)
{
	try {
		redi::ipstream in(command);
		std::string *str = new std::string();

		char ch;
		while (in.get(ch))
		{
			if (ch == '@')
				*str += "[at]";
			else
				*str += ch;
		}
		return str;
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to run steghide command, aborting." << std::endl;
		exit(1);
	}
}

// Run command through Steghide reading from stderr
std::string* Support::run_command_err(const char *command)
{
	try {
		redi::rpstream in(command, redi::pstreams::pstderr);
		std::string *str = new std::string();

		char ch;
		while (in.err().get(ch))
			*str += ch;
		return str;
	}
	catch (std::exception &e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		std::cerr << "Unable to run steghide command, aborting." << std::endl;
		exit(1);
	}
}

// Common method to get info on files
void Support::get_info(const char *filename)
{
	// ask user if they want embedded info
	int ans = fl_choice("Do you want to supply a passphrase to get info on hidden data?\n(I will use an empty passphrase by default)", "No, try with an empty passphrase", "Yes, let me supply a passphrase", NULL);
	const char *passphrase = NULL;

	std::string command("steghide --info ");
	command += filename;

	// ask user for passphrase if necessary
	if (!ans)
		command += " -p \"\"";
	else
	{
		passphrase = fl_password("Enter passphrase:");
		if (passphrase)
		{
			command += " -p \"";
			command += passphrase;
			command += "\"";
		}
		else
			command += " -p \"\"";
	}

	// run info command through Steghide
	redi::ipstream in(command, redi::pstreams::pstderr);
	std::string str;
	int i = 0;
	std::string strtmp;

	// show stderr popup
	while (std::getline(in.err(), strtmp))
	{
		str += strtmp;
		str += "\n";
		i++;
	}
	if (!str.empty())
	{
		try {
			MsgWindow *msg = new MsgWindow(550, 70 + (i*20), "Steghide message", str, "!");
			while (msg->visible())
				Fl::wait();
		}
		catch (std::exception &e) {
			std::cerr << "Exception thrown: " << e.what() << std::endl;
			std::cerr << "Unable to initialize message window, aborting." << std::endl;
			exit(1);
		}
	}

	in.clear();
	str.clear();
	i = 0;
	strtmp.clear();
	
	// show stdout popup
	while (std::getline(in.out(), strtmp))
	{
		str += strtmp;
		str += "\n";
		i++;
	}
	if (!str.empty())
	{
		try {
			MsgWindow *msg = new MsgWindow(360, 60 + (i*20), "Steghide output", str, "i");
			while (msg->visible())
				Fl::wait();
		}
		catch (std::exception &e) {
			std::cerr << "Exception thrown: " << e.what() << std::endl;
			std::cerr << "Unable to initialize message window, aborting." << std::endl;
			exit(1);
		}
	}
	in.clear();
}

// Check if file is a Windows or OS/2 BMP file
std::string Support::is_bitmap(std::string newfile)
{
	FILE *fp;
	bitmapheader header;
	bitmapinfoheader infoheader;
	int err;
	
	if ((fp = fopen(newfile.c_str(), "rb")) == NULL)
		return("");
	
	err = fread(&header.type, sizeof(short), 1, fp);
	CHECK_READ(err);
	header.type = LE_SHORT(header.type);
	
	if (header.type != 19778)
	{
		fclose(fp);
		return ("");
	}

	err = fread(&header.size, sizeof(long), 1, fp);
	CHECK_READ(err);
	header.size = LE_INT(header.size);
	err = fread(&header.res1, sizeof(short), 1, fp);
	CHECK_READ(err);
	header.res1 = LE_SHORT(header.res1);
	err = fread(&header.res2, sizeof(short), 1, fp);
	CHECK_READ(err);
	header.res2 = LE_SHORT(header.res2);
	err = fread(&header.offset, sizeof(long), 1, fp);
	CHECK_READ(err);
	header.offset = LE_INT(header.offset);
	
	err = fread(&infoheader.size, sizeof(long), 1, fp);
	CHECK_READ(err);
	infoheader.size = LE_INT(infoheader.size);
	err = fread(&infoheader.width, sizeof(long), 1, fp);
	CHECK_READ(err);
	infoheader.width = LE_INT(infoheader.width);
	err = fread(&infoheader.height, sizeof(long), 1, fp);
	CHECK_READ(err);
	infoheader.height = LE_INT(infoheader.height);
	err = fread(&infoheader.planes, sizeof(short), 1, fp);
	CHECK_READ(err);
	infoheader.planes = LE_SHORT(infoheader.planes);
	err = fread(&infoheader.bitcount, sizeof(short), 1, fp);
	CHECK_READ(err);
	infoheader.bitcount = LE_SHORT(infoheader.bitcount);

	// Windows BMP
	if (infoheader.size == 40)
	{
		err = fread(&infoheader.compression, sizeof(long), 1, fp);
		CHECK_READ(err);
		infoheader.compression = LE_INT(infoheader.compression);
		err = fread(&infoheader.sizeimage, sizeof(long), 1, fp);
		CHECK_READ(err);
		infoheader.sizeimage = LE_INT(infoheader.sizeimage);
		err = fread(&infoheader.xpelspermeter, sizeof(long), 1, fp);
		CHECK_READ(err);
		infoheader.xpelspermeter = LE_INT(infoheader.xpelspermeter);
		err = fread(&infoheader.ypelspermeter, sizeof(long), 1, fp);
		CHECK_READ(err);
		infoheader.ypelspermeter = LE_INT(infoheader.xpelspermeter);
		err = fread(&infoheader.clrused, sizeof(long), 1, fp);
		CHECK_READ(err);
		infoheader.clrused = LE_INT(infoheader.clrused);
		err = fread(&infoheader.clrimportant, sizeof(long), 1, fp);
		CHECK_READ(err);
		infoheader.clrimportant = LE_INT(infoheader.clrimportant);
	}
	
	std::stringstream desc;
	
	if (infoheader.size == 12)
		desc << "File type: OS/2 BMP - Size: ";
	else if (infoheader.size == 40)
		desc << "File type: Windows BMP - Size: ";
	else
		desc << "File type: BMP - Size: ";
	
	desc << header.size << " bytes - Image res: " << infoheader.width
		<< "x" << infoheader.height << ", " << infoheader.bitcount << " bits per pixel";
	
	fclose(fp);
	return(desc.str());
}

// Check if file is a JPEG file
// uses Libjpeg, see http://www.ijg.org/
std::string Support::is_jpeg(std::string newfile)
{
	FILE *fp;
	jpegheader header;

	if ((fp = fopen(newfile.c_str(), "rb")) == NULL)
		return("");
	
	if (fread(&header, sizeof(jpegheader), 1, fp) < 1)
	{
		fclose(fp);
		return ("");
	}

	if (!(((header.magic[0] & 0xFF) == 0xFF) && ((header.magic[1] & 0xFF) == 0xD8)))
	{
		fclose(fp);
		return ("");
	}
	
	struct stat statres;
	if (stat(newfile.c_str(), &statres) < 0)
	{
		fclose(fp);
		return("");
	}
	
	rewind(fp);

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, TRUE);
	      
	std::stringstream desc;
	desc << "File type: JPEG - Size: " << statres.st_size << " bytes - Image res: "
		<< cinfo.image_width << "x" << cinfo.image_height
		<< " - " << cinfo.num_components << " color components, ";
	
	switch(cinfo.jpeg_color_space)
	{
		case JCS_GRAYSCALE:
			desc << "monochrome ";
			break;
		case JCS_RGB:
			desc << "RGB ";
			break;
		case JCS_YCbCr:
			desc << "Y/Cb/Cr (YUV) ";
			break;
		case JCS_CMYK:
			desc << "CMYK ";
			break;
		case JCS_YCCK:
			desc << "Y/Cb/Cr/K ";
			break;
		case JCS_UNKNOWN:
		default:
			desc << "unspecified ";
			break;
	}
	desc << "color space";
	
	jpeg_destroy_decompress(&cinfo);
	fclose(fp);
	return(desc.str());
}

// Check if file is a WAVE file
std::string Support::is_wave(std::string newfile)
{
	FILE *fp;
	WaveHeader hdr;
	WaveFmtBody fbd;
	WaveChunkHeader chk;
	int err;

	if ((fp = fopen(newfile.c_str(), "rb")) == NULL)
		return("");
	
	err = fread(&hdr.magic, sizeof(int), 1, fp);
	CHECK_READ(err);
	
	if (hdr.magic != WAV_RIFF)
	{
		fclose(fp);
		return ("");
	}
	
	err = fread(&hdr.length, sizeof(int), 1, fp);
	CHECK_READ(err);
	hdr.length = LE_INT(hdr.length);
	err = fread(&hdr.type, sizeof(int), 1, fp);
	CHECK_READ(err);

	if (hdr.type != WAV_WAVE)
	{
		fclose(fp);
		return ("");
	}
	
	err = fread(&chk.type, sizeof(int), 1, fp);
	CHECK_READ(err);
	
	if (chk.type != WAV_FMT)
	{
		fclose(fp);
		return ("");
	}
	
	err = fread(&chk.length, sizeof(int), 1, fp);
	CHECK_READ(err);
	chk.length = LE_INT(chk.length);
	
	err = fread(&fbd.format, sizeof(short), 1, fp);
	CHECK_READ(err);
	fbd.format = LE_SHORT(fbd.format);
	err = fread(&fbd.modus, sizeof(short), 1, fp);
	CHECK_READ(err);
	fbd.modus = LE_SHORT(fbd.modus);
	err = fread(&fbd.sample_fq, sizeof(int), 1, fp);
	CHECK_READ(err);
	fbd.sample_fq = LE_INT(fbd.sample_fq);
	err = fread(&fbd.byte_p_sec, sizeof(int), 1, fp);
	CHECK_READ(err);
	fbd.byte_p_sec = LE_INT(fbd.byte_p_sec);
	err = fread(&fbd.byte_p_spl, sizeof(short), 1, fp);
	CHECK_READ(err);
	fbd.byte_p_spl = LE_SHORT(fbd.byte_p_spl);
	err = fread(&fbd.bit_p_spl, sizeof(short), 1, fp);
	CHECK_READ(err);
	fbd.bit_p_spl = LE_SHORT(fbd.bit_p_spl);

	std::stringstream desc;
	desc << "File type: Windows WAVE - Size: " << hdr.length+2*sizeof(int) << " bytes - "
		<< fbd.sample_fq << " Hz, " << fbd.bit_p_spl << " bit ";
	if (fbd.modus == 1)
		desc << "mono ";
	else if (fbd.modus == 2)
		desc << "stereo ";
	desc << "sound";
		
	fclose(fp);
	return(desc.str());
}

// Check if file is an AU file
std::string Support::is_au(std::string newfile)
{
	FILE *fp;
	AuHeader hdr;
	int err;

	if ((fp = fopen(newfile.c_str(), "rb")) == NULL)
		return("");

	err = fread(&hdr.magic, sizeof(u_int), 1, fp);
	CHECK_READ(err);

	if (hdr.magic != AU_MAGIC)
	{
		fclose(fp);
		return ("");
	}
	
	err = fread(&hdr.hdr_size, sizeof(u_int), 1, fp);
	CHECK_READ(err);
	hdr.hdr_size = BE_INT(hdr.hdr_size);
	err = fread(&hdr.data_size, sizeof(u_int), 1, fp);
	CHECK_READ(err);
	hdr.data_size = BE_INT(hdr.data_size);
	err = fread(&hdr.encoding, sizeof(u_int), 1, fp);
	CHECK_READ(err);
	hdr.encoding = BE_INT(hdr.encoding);
	err = fread(&hdr.sample_rate, sizeof(u_int), 1, fp);
	CHECK_READ(err);
	hdr.sample_rate = BE_INT(hdr.sample_rate);
	err = fread(&hdr.channels, sizeof(u_int), 1, fp);
	CHECK_READ(err);
	hdr.channels = BE_INT(hdr.channels);

	std::stringstream desc;
	desc << "File type: Sun/NeXT AU - Size: " << hdr.hdr_size+hdr.data_size//+sizeof(hdr.magic)
		<< " bytes - ";
	switch(hdr.encoding)
	{
		case AU_FMT_ULAW:
			desc << "Mu-law ";
			break;

		case AU_FMT_LIN8:
			desc << "Linear 8 bit ";
			break;

		case AU_FMT_LIN16:
			desc << "Linear 16 bit ";
			break;
	}
	desc << "encoding, " << hdr.sample_rate << " Hz ";
	if (hdr.channels == 1)
		desc << "mono ";
	else if (hdr.channels == 2)
		desc << "stereo ";
	desc << "sound";

	fclose(fp);
	return(desc.str());
}
