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

#include <QDir>
#include <QFile>
#include <QStringList>
#include <QUuid>

class TempFile {
  private:
	QStringList paths;

  public:
	TempFile() {}
	~TempFile() {
		removeAll();
	}

	QString create(const QString & ext) {
		QString path = QDir::tempPath() + "/wktemp-" + QUuid::createUuid().toString().mid(1, 36) + ext;
		paths.append(path);
		return path;
	}
	void removeAll() {
		foreach (const QString & path, paths)
			QFile::remove(path);
		paths.clear();
	}
};
