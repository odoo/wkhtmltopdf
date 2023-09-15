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

#include "logging.hh"
#include <QMap>
#include <QString>
namespace wkhtmltopdf::settings {

// Centralized name-to-enum value mapping
QMap<QString, LogLevel> logLevelMap() {
	QMap<QString, LogLevel> res;
	res["none"] = None;
	res["error"] = Error;
	res["warn"] = Warn;
	res["info"] = Info;
	res["debug"] = Debug;
	return res;
}

QMap<QString, LogLevel> logLevels = logLevelMap();

LogLevel strToLogLevel(const char * s, bool * ok) {
	for (QMap<QString, LogLevel>::const_iterator i = logLevels.begin(); i != logLevels.end(); ++i) {
		if (i.key().compare(s, Qt::CaseInsensitive) != 0) continue;
		if (ok) *ok = true;
		return i.value();
	}
	if (ok) *ok = false;
	return Info;
}

QString logLevelToStr(const LogLevel & l, bool * ok) {
	for (QMap<QString, LogLevel>::const_iterator i = logLevels.begin(); i != logLevels.end(); ++i) {
		if (i.value() != l) continue;
		if (ok) *ok = true;
		return i.key();
	}
	if (ok) *ok = false;
	return QString();
}

} // namespace wkhtmltopdf::settings
