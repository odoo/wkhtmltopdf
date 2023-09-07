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

#include "converter.hh"
#include "imagesettings.hh"

namespace wkhtmltopdf {

class ImageConverterPrivate;

class ImageConverter : public Converter {
	Q_OBJECT
  public:
	ImageConverter(settings::ImageGlobal & settings, const QString * data = NULL);
	~ImageConverter();
	const QByteArray & output();

  private:
	ImageConverterPrivate * d;
	virtual ConverterPrivate & priv();
	friend class ImageConverterPrivate;
};

} // namespace wkhtmltopdf
