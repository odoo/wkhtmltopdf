#pragma once

// Copyright 2010-2020 wkhtmltopdf authors
// Copyright 2023 Odoo S.A.
//
// This file is part of wkhtmltopdf.
//
// wkhtmltopdf is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// wkhtmltopdf is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with wkhtmltopdf.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdio>

#include "commandlineparserbase.hh"
#include <imagesettings.hh>

/*! \brief The class is responsible for parsing command line information
 */
class ImageCommandLineParser : public CommandLineParserBase {
  public:
	const static int global = 1;
	wkhtmltopdf::settings::ImageGlobal & settings;

	// arguments.cc
	ImageCommandLineParser(wkhtmltopdf::settings::ImageGlobal & settings);
	~ImageCommandLineParser(){};
	// docparts.cc
	void outputManName(Outputter * o) const;
	void outputSynopsis(Outputter * o) const;
	void outputDescripton(Outputter * o) const;
	void outputArgsFromStdin(Outputter * o) const;
	void outputNotPatched(Outputter * o, bool sure) const;
	void outputPageBreakDoc(Outputter * o) const;
	void outputContact(Outputter * o) const;
	void outputDocStart(Outputter * o) const;
	void outputCompilation(Outputter * o) const;
	void outputInstallation(Outputter * o) const;
	void outputExamples(Outputter * o) const;

	// commandlineparser.cc
	virtual void usage(FILE * fd, bool extended) const;
	virtual void manpage(FILE * fd) const;
	virtual void readme(FILE * fd, bool html) const;
	virtual QString appName() const { return "wkhtmltoimage"; }

	// void loadDefaults();
	void parseArguments(int argc, const char ** argv, bool final = false);
};
