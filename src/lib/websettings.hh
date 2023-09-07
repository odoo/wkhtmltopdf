#pragma once

// Copyright 2010-2020 wkhtmltopdf authors
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

#include <QNetworkProxy>
#include <QString>

namespace wkhtmltopdf {
namespace settings {

struct Web {
	//! Should we print background images
	bool background = true;

	//! Should we load images
	bool loadImages = true;

	//! Should we enable Javascript
	bool enableJavascript = true;

	//! Should the horrible intelligent shrinking feature be enabled?
	bool enableIntelligentShrinking = true;

	//! Minimum font size
	int minimumFontSize = -1;

	//! Encoding used to enterpit a document with do supplied encoding
	QString defaultEncoding = "";

	//! Stylesheet supplied by the user
	QString userStyleSheet = "";

	//! Should plugins be allowed
	bool enablePlugins = false;
}; // namespace settingsstruct Web

} // namespace settings
} // namespace wkhtmltopdf
