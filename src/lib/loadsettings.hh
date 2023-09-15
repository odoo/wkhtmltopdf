#pragma once

// Copyright 2010, 2012 wkhtmltopdf authors
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

#include <QNetworkProxy>
#include <QString>

namespace wkhtmltopdf {
namespace settings {

/*! \brief Settings considering proxy */
struct Proxy {
	//! Type of proxy to use
	QNetworkProxy::ProxyType type{QNetworkProxy::NoProxy};
	//! The port of the proxy to use
	int port{-1};
	//! The host name of the proxy to use or NULL
	QString host{};
	//! Username for the said proxy or NULL
	QString user{};
	//! Password for the said proxy or NULL
	QString password{};
};

struct PostItem {
	QString name;
	QString value;
	bool file;
};

struct LoadGlobal {
	//! Path of the cookie jar file
	QString cookieJar{""};
};

struct LoadPage {

	enum LoadErrorHandling {
		abort,
		skip,
		ignore
	};

	//! Username used for http auth login
	QString username;

	//! Password used for http auth login
	QString password;

	//! Path to the ssl client cert private key in OpenSSL PEM format
	QString clientSslKeyPath;

	//! Password to ssl client cert private key
	QString clientSslKeyPassword;

	//! Path to the ssl client cert public key in OpenSSL PEM format, optionally followed by intermediate ca and trusted certs
	QString clientSslCrtPath;

	//! How many milliseconds should we wait for a Javascript redirect
	int jsdelay{200};

	//! What window.status value should we wait for
	QString windowStatus{};

	//! What zoom factor should we apply when printing
	// TODO MOVE
	float zoomFactor{1};

	//! Map of custom header variables
	QList<QPair<QString, QString>> customHeaders;

	//! Set if the custom header should be repeated for each resource request
	bool repeatCustomHeaders{false};

	//! Map of cookies
	QList<QPair<QString, QString>> cookies;

	QList<PostItem> post;

	//! Block access to local files for the given page
	bool blockLocalFileAccess{true};

	//! If access to local files is not allowed in general, allow it for these files
	QList<QString> allowed;

	//! Stop Javascript from running too long
	bool stopSlowScripts{true};

	//! Output Javascript debug messages
	bool debugJavascript{false};

	//! What should we do about load errors
	LoadErrorHandling loadErrorHandling{abort};
	LoadErrorHandling mediaLoadErrorHandling{ignore};

	//! Proxy related settings
	Proxy proxy;

	//! Additional javascript to run on a page once it has loaded
	QList<QString> runScript;

	QString checkboxSvg;
	QString checkboxCheckedSvg;
	QString radiobuttonSvg;
	QString radiobuttonCheckedSvg;

	QString cacheDir{""};
	static QList<QString> mediaFilesExtensions;

	// Hosts to bypass
	QList<QString> bypassProxyForHosts;

	//! Whether to use the proxy for resolving hostnames
	bool proxyHostNameLookup{false};

	//! Should we use the print or the screen media type
	bool printMediaType{false};
};

LoadPage::LoadErrorHandling strToLoadErrorHandling(const char * s, bool * ok = 0);
QString loadErrorHandlingToStr(LoadPage::LoadErrorHandling leh);

Proxy strToProxy(const char * s, bool * ok = 0);
QString proxyToStr(const Proxy & proxy);

} // namespace settings
} // namespace wkhtmltopdf
