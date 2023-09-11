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

#include <QAtomicInt>
#include <QFile>
#include <QMutex>
#include <QPainter>
#include <QPrinter>
#include <QRegExp>
#include <QWaitCondition>
#include <QWebElement>
#include <QWebPage>
#include <qnetworkreply.h>

#include <utility>

#include "converter_p.hh"
#include "multipageloader.hh"
#include "outline.hh"
#include "pdfconverter.hh"
#include "pdfsettings.hh"
#include "tempfile.hh"

namespace wkhtmltopdf {

class PageObject {
  public:
	static QMap<QWebPage *, PageObject *> webPageToObject;

	settings::PdfObject settings;
	LoaderObject * loaderObject;
	QWebPage * page;
	QString data;
	int number;

	QHash<QString, QWebElement> anchors;
	QVector<QPair<QWebElement, QString>> localLinks;
	QVector<QPair<QWebElement, QString>> externalLinks;
	// height length to reserve for header when printing page
	double headerReserveHeight;
	// height length to reserve for footer when printing page
	double footerReserveHeight;
	// webprinter instance
	QWebPrinter * web_printer;

	int firstPageNumber;
	QWebPage * header = nullptr;
	QWebPage * footer = nullptr;
	int pageCount;
	TempFile tocFile;

	void clear() {
		anchors.clear();
		localLinks.clear();
		externalLinks.clear();
		if (web_printer != 0)
			delete web_printer;
		web_printer = 0;

		delete std::exchange(footer, nullptr);
		delete std::exchange(header, nullptr);
		webPageToObject.remove(page);
		page = 0;
		tocFile.removeAll();
	}

	PageObject(const settings::PdfObject & set, const QString * d = NULL)
		: settings(set), loaderObject(0), page(0),
		  headerReserveHeight(0), footerReserveHeight(0), web_printer(0) {
		if (d) data = *d;
	};

	~PageObject() {
		clear();
	}
};

class PdfConverterPrivate : public ConverterPrivate {
	Q_OBJECT
  public:
	PdfConverterPrivate(settings::PdfGlobal & s, PdfConverter & o);
	~PdfConverterPrivate();

	settings::PdfGlobal & settings;

	MultiPageLoader pageLoader;

  private:
	PdfConverter & out;
	void clearResources();
	TempFile tempOut;
	QByteArray outputData;

	QList<PageObject> objects;
	QSize viewportSize;
	QPrinter * printer;
	QPainter * painter;
	QString lout;
	QString title;
	int currentObject;
	int actualPages;
	int pageCount;
	int tocPages;
	bool tocChanged;
	int actualPage;
	int pageNumber;
	int objectPage;

	QHash<int, QHash<QString, QWebElement>> pageAnchors;
	QHash<int, QVector<QPair<QWebElement, QString>>> pageLocalLinks;
	QHash<int, QVector<QPair<QWebElement, QString>>> pageExternalLinks;
	QHash<int, QVector<QWebElement>> pageFormElements;
	bool pageHasHeaderFooter;

	MultiPageLoader hfLoader;
	MultiPageLoader tocLoader1;
	MultiPageLoader tocLoader2;

	MultiPageLoader * tocLoader;
	MultiPageLoader * tocLoaderOld;

	QHash<QString, PageObject *> urlToPageObj;

	Outline * outline;
	void findLinks(QWebFrame * frame, QVector<QPair<QWebElement, QString>> & local, QVector<QPair<QWebElement, QString>> & external, QHash<QString, QWebElement> & anchors);
	void endPage(PageObject & object, bool hasHeaderFooter, int objectPage, int pageNumber);
	void fillParms(QHash<QString, QString> & parms, int page, const PageObject & object);
	QString hfreplace(const QString & q, const QHash<QString, QString> & parms);
	QWebPage * loadHeaderFooter(QString url, const QHash<QString, QString> & parms, const settings::PdfObject & ps);
	qreal calculateHeaderHeight(PageObject & object, QWebPage & header);

	QWebPage * currentHeader;
	QWebPage * currentFooter;
	QPrinter * createPrinter(const QString & tempFile);

	void handleTocPage(PageObject & obj);
	void preprocessPage(PageObject & obj);
	void spoolPage(int page);
	void spoolTo(int page);
	void handleHeader(QWebPage * frame, int page);
	void handleFooter(QWebPage * frame, int page);
	void beginPrintObject(PageObject & obj);
	void endPrintObject(PageObject & obj);

	void loadTocs();
	void loadHeaders();
  public slots:
	void pagesLoaded(bool ok);
	void tocLoaded(bool ok);
	void headersLoaded(bool ok);

	void printDocument();

	void beginConvert();

	friend class PdfConverter;

	virtual Converter & outer();
};

} // namespace wkhtmltopdf
