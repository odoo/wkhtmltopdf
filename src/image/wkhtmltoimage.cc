// Copyright 2010-2020 wkhtmltopdf authors
// Copyright 2023-2024 Odoo S.A.
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

#include <QApplication>
#include <QWebFrame>
#include <imageconverter.hh>
#include <imagesettings.hh>
#include <utilities.hh>

#include "imagecommandlineparser.hh"
#include "progressfeedback.hh"

#if defined(Q_OS_UNIX)
#include <locale.h>
#endif

int main(int argc, char ** argv) {
#if defined(Q_OS_UNIX)
	setlocale(LC_ALL, "");
#endif
	// This will store all our settings
	wkhtmltopdf::settings::ImageGlobal settings;
	// Create a command line parser to parse commandline arguments
	ImageCommandLineParser parser(settings);
	// Parse the arguments
	parser.parseArguments(argc, (const char **)argv);

	bool use_graphics = true;
#if defined(Q_OS_UNIX) || defined(Q_OS_MAC)
	use_graphics = settings.useGraphics;
	if (!use_graphics) QApplication::setGraphicsSystem("raster");
#endif
	QApplication a(argc, argv, use_graphics);
	MyLooksStyle * style = new MyLooksStyle();
	a.setStyle(style);

	// Create the actual page converter to convert the pages
	wkhtmltopdf::ImageConverter converter(settings);
	QObject::connect(&converter, SIGNAL(checkboxSvgChanged(const QString &)), style, SLOT(setCheckboxSvg(const QString &)));
	QObject::connect(&converter, SIGNAL(checkboxCheckedSvgChanged(const QString &)), style, SLOT(setCheckboxCheckedSvg(const QString &)));
	QObject::connect(&converter, SIGNAL(radiobuttonSvgChanged(const QString &)), style, SLOT(setRadioButtonSvg(const QString &)));
	QObject::connect(&converter, SIGNAL(radiobuttonCheckedSvgChanged(const QString &)), style, SLOT(setRadioButtonCheckedSvg(const QString &)));

	wkhtmltopdf::ProgressFeedback feedback(settings.logLevel, converter);
	bool success = converter.convert();
	return handleError(success, converter.httpErrorCode());
}
