////////////////////////////////////////////////////////////////////////////////
//
// aria2fe
// A graphical "Front End" (GUI) for aria2
// Copyright (C) 2007, Mike Wells
//
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see http://www.gnu.org/licenses/.
//
//
// Web: http://aria2fe.com/
// Email: aria2fe@cox.net
//
////////////////////////////////////////////////////////////////////////////////

#ifndef HTTPARGSDLG_H
#define HTTPARGSDLG_H

#include <ui_httpargsdlg.h>

#include <QMessageBox>

extern QString argHttpContinue;
extern QString argHttpPersistence;
extern QString argHttpRename;
extern QString argHttpScheme;
extern QString argHttpPipelining;
extern QString argHttpMethod;
extern QString argHttpAgent;
extern QString argHttpProxyServer;
extern QString argHttpUser;
extern QString argHttpPasswd;
extern QString argHttpProxyUser;
extern QString argHttpProxyPasswd;

extern bool httpContinue;
extern int httpPersistence;
extern int httpRename;
extern int httpScheme;
extern int httpPipelining;
extern int httpMethod;
extern QString httpAgent;
extern QString httpProxyServer;
extern QString httpUser;
extern QString httpPasswd;
extern QString httpProxyUser;
extern QString httpProxyPasswd;

class httpArgsDlg : public QDialog, public Ui::httpArgsDlg {
    Q_OBJECT

public:
    httpArgsDlg();
    ~httpArgsDlg();

public slots:

    void acceptArgs();
    void rejectArgs();
    void acquireHttpContinue();
    void acquireHttpPersistence();
    void acquireHttpRename();
    void acquireHttpScheme();
    void acquireHttpPipelining();
    void acquireHttpMethod();
    void acquireHttpAgent();
    void acquireHttpProxyServer();
    void acquireHttpUser();
    void acquireHttpPasswd();
    void acquireHttpProxyUser();
    void acquireHttpProxyPasswd();
    void acquireAll();
    void restoreDefaults();

protected slots:

    virtual void languageChange();

private:
    void setupConnections();
    void init();
};

#endif // HTTPARGSDLG_H
