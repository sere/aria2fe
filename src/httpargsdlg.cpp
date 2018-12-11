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

#include <httpargsdlg.h>

QString argHttpContinue;
QString argHttpPersistence;
QString argHttpRename;
QString argHttpScheme;
QString argHttpPipelining;
QString argHttpMethod;
QString argHttpAgent;
QString argHttpProxyServer;
QString argHttpUser;
QString argHttpPasswd;
QString argHttpProxyUser;
QString argHttpProxyPasswd;

bool httpContinue;
int httpPersistence;
int httpRename;
int httpScheme;
int httpPipelining;
int httpMethod;
QString httpAgent;
QString httpProxyServer;
QString httpUser;
QString httpPasswd;
QString httpProxyUser;
QString httpProxyPasswd;

httpArgsDlg::httpArgsDlg() // constructor
{
    setupUi(this);
    setupConnections();
    init();
}

httpArgsDlg::~httpArgsDlg() // destructor
{
    // no need to delete child widgets, Qt does it all for us
}

void httpArgsDlg::languageChange() // future use
{
    retranslateUi(this);
}

void httpArgsDlg::acceptArgs() // ok btn
{
    acquireAll();

    httpContinue = httpContinueCkBox->isChecked();
    httpPersistence = httpPersistenceCombo->currentIndex();
    httpRename = httpRenameCombo->currentIndex();
    httpScheme = httpSchemeCombo->currentIndex();
    httpPipelining = httpPipeliningCombo->currentIndex();
    httpMethod = httpMethodCombo->currentIndex();
    httpAgent = httpAgentEdit->text();
    httpProxyServer = httpProxyServerEdit->text();
    httpUser = httpUserEdit->text();
    httpPasswd = httpPasswdEdit->text();
    httpProxyUser = httpProxyUserEdit->text();
    httpProxyPasswd = httpProxyPasswdEdit->text();

    close();
}

void httpArgsDlg::rejectArgs() // cancel btn
{
    close();
}

void httpArgsDlg::acquireHttpContinue() {
    argHttpContinue = "";

    if (httpContinueCkBox->isChecked())
        argHttpContinue = "--continue";
}

void httpArgsDlg::acquireHttpPersistence() {
    argHttpPersistence = "";

    if (httpPersistenceCombo->currentText() == "true")
        argHttpPersistence = "--enable-http-keep-alive=true";
}

void httpArgsDlg::acquireHttpRename() {
    argHttpRename = "";

    if (httpRenameCombo->currentText() == "false")
        argHttpRename = "--auto-file-renaming=false";
}

void httpArgsDlg::acquireHttpScheme() {
    argHttpScheme = "";

    /*if (httpSchemeCombo->currentText()=="basic")  //future use
        argHttpScheme="--http-auth-scheme=basic";*/
}

void httpArgsDlg::acquireHttpPipelining() {
    argHttpPipelining = "";

    if (httpPipeliningCombo->currentText() == "true")
        argHttpPipelining = "--enable-http-pipelining=true";
}

void httpArgsDlg::acquireHttpMethod() {
    argHttpMethod = "";

    if (httpMethodCombo->currentText() == "get")
        argHttpMethod = "--http-proxy-method=get";
}

void httpArgsDlg::acquireHttpAgent() {
    argHttpAgent = "";

    if (httpAgentEdit->text() != "")
        argHttpAgent = "--user-agent=" + httpAgentEdit->text();
}

void httpArgsDlg::acquireHttpProxyServer() {
    argHttpProxyServer = "";

    if (httpProxyServerEdit->text() != "")
        argHttpProxyServer = "--http-proxy=" + httpProxyServerEdit->text();
}

void httpArgsDlg::acquireHttpUser() {
    argHttpUser = "";

    if (httpUserEdit->text() != "")
        argHttpUser = "--http-user=" + httpUserEdit->text();
}

void httpArgsDlg::acquireHttpPasswd() {
    argHttpPasswd = "";

    if (httpPasswdEdit->text() != "")
        argHttpPasswd = "--http-passwd=" + httpPasswdEdit->text();
}

void httpArgsDlg::acquireHttpProxyUser() {
    argHttpProxyUser = "";

    if (httpProxyUserEdit->text() != "")
        argHttpProxyUser = "--http-proxy-user=" + httpProxyUserEdit->text();
}

void httpArgsDlg::acquireHttpProxyPasswd() {
    argHttpProxyPasswd = "";

    if (httpProxyPasswdEdit->text() != "")
        argHttpProxyPasswd =
                "--http-proxy-passwd=" + httpProxyPasswdEdit->text();
}

void httpArgsDlg::acquireAll() {
    acquireHttpContinue();
    acquireHttpPersistence();
    acquireHttpRename();
    acquireHttpScheme();
    acquireHttpPipelining();
    acquireHttpMethod();
    acquireHttpAgent();
    acquireHttpProxyServer();
    acquireHttpUser();
    acquireHttpPasswd();
    acquireHttpProxyUser();
    acquireHttpProxyPasswd();
}

void httpArgsDlg::restoreDefaults() // restore btn
{
    httpContinueCkBox->setChecked(false);
    httpPersistenceCombo->setCurrentIndex(0);
    httpRenameCombo->setCurrentIndex(0);
    httpSchemeCombo->setCurrentIndex(0);
    httpPipeliningCombo->setCurrentIndex(0);
    httpMethodCombo->setCurrentIndex(0);
    httpAgentEdit->setText("");
    httpProxyServerEdit->setText("");
    httpUserEdit->setText("");
    httpPasswdEdit->setText("");
    httpProxyUserEdit->setText("");
    httpProxyPasswdEdit->setText("");

    argHttpContinue = "";
    argHttpPersistence = "";
    argHttpRename = "";
    argHttpScheme = "";
    argHttpPipelining = "";
    argHttpMethod = "";
    argHttpAgent = "";
    argHttpProxyServer = "";
    argHttpUser = "";
    argHttpPasswd = "";
    argHttpProxyUser = "";
    argHttpProxyPasswd = "";

    httpContinue = false;
    httpPersistence = 0;
    httpRename = 0;
    httpScheme = 0;
    httpPipelining = 0;
    httpMethod = 0;
    httpAgent = "";
    httpProxyServer = "";
    httpUser = "";
    httpPasswd = "";
    httpProxyUser = "";
    httpProxyPasswd = "";

    QMessageBox::warning(this, "Warning - aria2fe",
                         "The HTTP(S) argument list has been cleared!");
}

void httpArgsDlg::setupConnections() // called by constructor
{
    connect(restoreBtn, SIGNAL(released()), this, SLOT(restoreDefaults()));
    connect(okBtn, SIGNAL(released()), this, SLOT(acceptArgs()));
    connect(cancelBtn, SIGNAL(released()), this, SLOT(rejectArgs()));
}

void httpArgsDlg::init() // called by constructor
{
    httpContinueCkBox->setChecked(httpContinue);
    httpPersistenceCombo->setCurrentIndex(httpPersistence);
    httpRenameCombo->setCurrentIndex(httpRename);
    httpSchemeCombo->setCurrentIndex(httpScheme);
    httpPipeliningCombo->setCurrentIndex(httpPipelining);
    httpMethodCombo->setCurrentIndex(httpMethod);
    httpAgentEdit->setText(httpAgent);
    httpProxyServerEdit->setText(httpProxyServer);
    httpUserEdit->setText(httpUser);
    httpPasswdEdit->setText(httpPasswd);
    httpProxyUserEdit->setText(httpProxyUser);
    httpProxyPasswdEdit->setText(httpProxyPasswd);

    acquireAll();
}
