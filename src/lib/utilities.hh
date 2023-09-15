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

#include <QFile>
#include <QFileInfo>
#include <QImageWriter>
#include <QPainter>
#include <QProxyStyle>
#include <QStyleOption>
#include <QSvgRenderer>
#include <QUrl>

/**
 * Custom simplistic style
 */
class MyLooksStyle : public QProxyStyle {
	Q_OBJECT
  public:
	typedef QProxyStyle parent_t;
	MyLooksStyle();
	void drawPrimitive(PrimitiveElement element, const QStyleOption * option, QPainter * painter, const QWidget * widget = 0) const;
	bool weAreDrawingForms;

	static QSvgRenderer * checkbox;
	static QSvgRenderer * checkbox_checked;
	static QSvgRenderer * radiobutton;
	static QSvgRenderer * radiobutton_checked;
  public slots:
	void producingForms(bool f);
	void setCheckboxSvg(const QString & path);
	void setCheckboxCheckedSvg(const QString & path);
	void setRadioButtonSvg(const QString & path);
	void setRadioButtonCheckedSvg(const QString & path);
};

int handleError(bool success, int errorCode);
