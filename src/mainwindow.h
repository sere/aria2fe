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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ui_mainwindow.h>

#include <aboutdlg.h>
#include <argsdlg.h>
#include <ftpargsdlg.h>
#include <helpdlg.h>
#include <httpargsdlg.h>
#include <metaargsdlg.h>
#include <torrentargsdlg.h>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QStatusBar>
#include <QTextStream>

class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    bool aria2Help;
    bool aria2Version;
    QString appName;
    QString delimiter;
    QString confFileName;
    QString saveFileName;
    QString fileType;
    QString filesOfType;
    QString argDaemon;
    QString argNetrc;
    QString argUriType;
    QString argUriFileName;
    QString argTargetDir;
    QString argTargetFileName;
    QString argLogFileName;
    QString argAlloc;
    QString argSizeLimit;
    QString argOverwrite;
    QString argForceSeq;
    QString argParameter;
    QString argSplit;
    QString argRetryDelay;
    QString argTimeout;
    QString argMaxTries;
    QString argReferer;
    QString argMinDownSpeed;
    QString argMaxDownSpeed;
    QString argCookies;
    QString argMaxConcurrent;
    QString argDirect;
    QString argPieceLength;
    QStringList argAddOpts;
    QStringList args;
    QStringList arguments;
    QStringList argsXterm;

public slots:

    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void fileExit();
    void helpAria2fe();
    void helpAria2();
    void versionAria2();
    void helpAbout();
    void helpAboutQt();
    void clearUri();
    void clearTargetDir();
    void clearTargetFile();
    void clearLogFile();
    void clearCookies();
    void clearReferer();
    void clearAddOpts();
    void acquireDaemon();
    void acquireNetrc();
    void acquireUriType();
    void browseUriObject();
    void acquireUriObject();
    void browseTargetDir();
    void acquireTargetDir();
    void acquireTargetFileName();
    void acquireLogFileName();
    void acquireMaxTries();
    void acquireSplit();
    void acquireRetryDelay();
    void acquireTimeout();
    void acquireMinDownSpeed();
    void acquireMaxDownSpeed();
    void acquireReferer();
    void acquireAlloc();
    void acquireSizeLimit();
    void acquireOverwrite();
    void acquireForceSeq();
    void acquireParameter();
    void browseCookieFiles();
    void acquireCookies();
    void acquireMaxConcurrent();
    void acquireDirect();
    void acquirePieceLength();
    void acquireAddOpts();
    void callHttpDlg();
    void callFtpDlg();
    void callMetaDlg();
    void callTorrentDlg();
    void runExternal();
    void catArgs();
    void restoreDefaults();
    void saveWidgets();
    void loadWidgets();

protected slots:

    void languageChange();

private:
    QLabel *confFile;

    void setupConnections();
    void init();
};

#endif // MAINWINDOW_H
