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

#include "converter_p.hh"
#include "imageconverter.hh"
#include "multipageloader.hh"

namespace wkhtmltopdf {

class ImageConverterPrivate : public ConverterPrivate {
	Q_OBJECT
  public:
	ImageConverterPrivate(ImageConverter & o, wkhtmltopdf::settings::ImageGlobal & s, const QString * data);

	wkhtmltopdf::settings::ImageGlobal settings;
	MultiPageLoader loader;

  private:
	QByteArray outputData;
	QString inputData;

	ImageConverter & out;
	void clearResources();

	LoaderObject * loaderObject;

  public slots:
	void pagesLoaded(bool ok);
	void beginConvert();

	friend class ImageConverter;

	virtual Converter & outer();
};

} // namespace wkhtmltopdf
