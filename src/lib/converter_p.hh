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
#include <QWebSettings>

#include "converter.hh"
#include "websettings.hh"

namespace wkhtmltopdf {

class ConverterPrivate : public QObject {
	Q_OBJECT
  public:
	void copyFile(QFile & src, QFile & dst);

	QList<QString> phaseDescriptions;
	int currentPhase;

	QString progressString;

  protected:
	bool error;
	virtual void clearResources() = 0;
	virtual Converter & outer() = 0;
	int errorCode;

	bool conversionDone;

	void updateWebSettings(QWebSettings * ws, const settings::Web & s) const;
  public slots:
	void fail();
	void loadProgress(int progress);

	virtual void beginConvert() = 0;
	void cancel();
	bool convert();
	void forwardError(QString error);
	void forwardWarning(QString warning);
	void forwardInfo(QString info);
	void forwardDebug(QString debug);

  private:
	friend class Converter;
};

} // namespace wkhtmltopdf
