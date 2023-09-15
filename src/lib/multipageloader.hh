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
#include <QObject>
#include <QUrl>
#if QT_VERSION >= 0x050000
#include <QtWebKitWidgets>
#else
#include <QWebPage>
#endif
#include "loadsettings.hh"

namespace wkhtmltopdf {

class MyQWebPage;

class LoaderObject {
  public:
	QWebPage & page;
	bool skip;

	LoaderObject(QWebPage & page);
};

class MultiPageLoaderPrivate;
class MultiPageLoader : public QObject {
	Q_OBJECT
  public:
	MultiPageLoader(settings::LoadGlobal & s, int dpi, bool mainLoader = false);
	~MultiPageLoader();
	LoaderObject * addResource(const QString & url, const settings::LoadPage & settings, const QString * data = NULL);
	LoaderObject * addResource(const QUrl & url, const settings::LoadPage & settings);
	static QUrl guessUrlFromString(const QString & string);
	int httpErrorCode();
	static bool copyFile(QFile & src, QFile & dst);
  public slots:
	void load();
	void clearResources();
	void cancel();
  signals:
	void loadFinished(bool ok);
	void loadProgress(int progress);
	void loadStarted();
	void debug(QString text);
	void info(QString text);
	void warning(QString text);
	void error(QString text);

  private:
	MultiPageLoaderPrivate * d;
	friend class MultiPageLoaderPrivate;
	friend class MyQWebPage;
	friend class ResourceObject;
};

} // namespace wkhtmltopdf
