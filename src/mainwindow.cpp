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

#include <mainwindow.h>

MainWindow::MainWindow() // constructor
{
    setupUi(this);
    setupConnections();
    init();
}

MainWindow::~MainWindow() // destructor
{
    // destroys the object and frees allocated resources
    // no need to delete child widgets, Qt does it all for us
}

void MainWindow::languageChange() // future use
{
    // sets the strings of the subwidgets using the current language.
    retranslateUi(this);
}

//
// menubar/toolbar procedure blocks begin here
//
void MainWindow::fileOpen() // conf file
{
    confFileName = QFileDialog::getOpenFileName(this, "Open File - aria2fe",
                                                QDir::homePath(),
                                                "Configuration Files (*.conf)");

    if (!confFileName.isEmpty()) {
        fileSaveAction->setEnabled(true);
        loadWidgets();
    }
}

void MainWindow::fileSave() // conf file
{
    saveFileName = confFileName;
    saveWidgets();
}

void MainWindow::fileSaveAs() // conf file
{
    if (confFileName != "")
        saveFileName = QDir::homePath() + confFileName;
    else
        saveFileName = QDir::homePath() + "/untitled.conf";

    saveFileName = QFileDialog::getSaveFileName(this, "Save File As - aria2fe",
                                                saveFileName,
                                                "Configuration Files (*.conf)");

    if (!saveFileName.isEmpty())
        saveWidgets();
}

void MainWindow::fileExit() { QApplication::exit(0); }

void MainWindow::helpAria2fe() {
    helpDlg *help = new helpDlg;
    help->show();

    /*    QMessageBox::information
            (this,"Information - aria2fe","This feature will be implemented \n "
            "in a future release of aria2fe.");*/
}

void MainWindow::helpAria2() {
    aria2Help = true;
    catArgs();
}

void MainWindow::versionAria2() {
    aria2Version = true;
    catArgs();
}

void MainWindow::helpAbout() { aboutDlg().exec(); }

void MainWindow::helpAboutQt() {
    QMessageBox::aboutQt // a little plug for Trolltech
            (this, "About Qt");
}

//
// clear line edit procedure blocks begin here
//
void MainWindow::clearUri() // clear btn press
{
    uriEdit->clear();
    argUriFileName = "";
    uriEdit->setFocus();
}

void MainWindow::clearTargetDir() // clear btn press
{
    targetDirEdit->clear();
    argTargetDir = "";
    targetDirEdit->setFocus();
}

void MainWindow::clearTargetFile() // clear btn press
{
    targetFileEdit->clear();
    argTargetFileName = "";
    targetFileEdit->setFocus();
}

void MainWindow::clearLogFile() // clear btn press
{
    logFileEdit->clear();
    argLogFileName = "";
    logFileEdit->setFocus();
}

void MainWindow::clearCookies() // clear btn press
{
    cookiesEdit->clear();
    argCookies = "";
    cookiesEdit->setFocus();
}

void MainWindow::clearReferer() // clear btn press
{
    refererEdit->clear();
    argReferer = "";
    refererEdit->setFocus();
}

void MainWindow::clearAddOpts() // clear btn press
{
    addOptsEdit->clear();
    argAddOpts.clear();
    addOptsEdit->setFocus();
}

//
// aria2 argument procedure blocks begin here
//
void MainWindow::acquireDaemon() // toggled
{
    argDaemon = "";

    if (daemonCkBox->isChecked())
        argDaemon = "--daemon";
}

void MainWindow::acquireNetrc() // toggled
{
    argNetrc = "";

    if (netrcCkBox->isChecked())
        argNetrc = "--no-netrc";
}

void MainWindow::acquireUriType() // activated (new selection)
{
    argUriType = "";

    if (uriCombo->currentText() == "Metalink") {
        argUriType = "-M";
        fileType = "*.metalink";
        uriBrowseBtn->setEnabled(true);
        httpBtn->setEnabled(false);
        ftpBtn->setEnabled(false);
        metaBtn->setEnabled(true);
        torrentBtn->setEnabled(false);
    } else if (uriCombo->currentText() == "Torrent") {
        argUriType = "-T";
        fileType = "*.torrent";
        uriBrowseBtn->setEnabled(true);
        httpBtn->setEnabled(false);
        ftpBtn->setEnabled(false);
        metaBtn->setEnabled(false);
        torrentBtn->setEnabled(true);
    } else if (uriCombo->currentText() == "URI File") {
        fileType = "*.txt";
        uriBrowseBtn->setEnabled(true);
        httpBtn->setEnabled(true);
        ftpBtn->setEnabled(true);
        metaBtn->setEnabled(false);
        torrentBtn->setEnabled(false);
    } else {
        uriBrowseBtn->setEnabled(false);
        httpBtn->setEnabled(true);
        ftpBtn->setEnabled(true);
        metaBtn->setEnabled(false);
        torrentBtn->setEnabled(false);
    }

    uriEdit->setFocus();
}

void MainWindow::browseUriObject() // uri browse btn press
{
    uriEdit->blockSignals(true);

    argUriFileName = "";

    filesOfType = uriCombo->currentText() + " Files (" + fileType + ")";

    argUriFileName = QFileDialog::getOpenFileName(
            this, "Open File - aria2fe", QDir::homePath(), filesOfType);

    if (!argUriFileName.isEmpty()) {
        uriEdit->setText(argUriFileName);
        if (fileType == "*.txt")
            argUriFileName = "--input-file=" + argUriFileName;
    }

    uriEdit->setFocus();

    uriEdit->blockSignals(false);
}

void MainWindow::acquireUriObject() // editingFinished()
{
    argUriFileName = "";

    if (uriEdit->text() != "") {
        argUriFileName = uriEdit->text();
        QFileInfo info(argUriFileName);
        QString fileExt = info.suffix();
        if (fileExt == "txt")
            argUriFileName = "--input-file=" + argUriFileName;
    }
}

void MainWindow::browseTargetDir() // target dir browse btn press
{
    targetDirEdit->blockSignals(true);

    argTargetDir = "";

    argTargetDir = QFileDialog::getExistingDirectory(
            this, "Browse Directories - aria2fe", QDir::homePath());

    if (!argTargetDir.isEmpty()) {
        targetDirEdit->setText(argTargetDir);
        argTargetDir = "--dir=" + argTargetDir;
    } else if (targetDirEdit->text() == "")
        argTargetDir = "";

    targetDirEdit->blockSignals(false);
}

void MainWindow::acquireTargetDir() // editingFinished()
{
    argTargetDir = "";

    if (targetDirEdit->text() != "")
        argTargetDir = "--dir=" + targetDirEdit->text();
}

void MainWindow::acquireTargetFileName() // editingFinished()
{
    argTargetFileName = "";

    if (targetFileEdit->text() != "")
        argTargetFileName = "--out=" + targetFileEdit->text();
}

void MainWindow::acquireLogFileName() // editingFinished()
{
    argLogFileName = "";

    if (logFileEdit->text() != "")
        argLogFileName = "--log=" + logFileEdit->text();
}

void MainWindow::acquireMaxTries() // editingFinished()
{
    argMaxTries = "";

    if (maxTriesEdit->text() != "5")
        argMaxTries = "--max-tries=" + maxTriesEdit->text();
}

void MainWindow::acquireSplit() // editingFinished()
{
    argSplit = "";

    if (splitEdit->text() != "1")
        argSplit = "--split=" + splitEdit->text();
}

void MainWindow::acquireRetryDelay() // editingFinished()
{
    argRetryDelay = "";

    if (retryEdit->text() != "5")
        argRetryDelay = "--retry-wait=" + retryEdit->text();
}

void MainWindow::acquireTimeout() // editingFinished()
{
    argTimeout = "";

    if (timeoutEdit->text() != "60")
        argTimeout = "--timeout=" + timeoutEdit->text();
}

void MainWindow::acquireMinDownSpeed() // editingFinished()
{
    argMinDownSpeed = "";

    if (minSpeedEdit->text() != "0")
        argMinDownSpeed = "--lowest-speed-limit=" + minSpeedEdit->text();
}

void MainWindow::acquireMaxDownSpeed() // editingFinished()
{
    argMaxDownSpeed = "";

    if (maxSpeedEdit->text() != "0")
        argMaxDownSpeed = "--max-download-limit=" + maxSpeedEdit->text();
}

void MainWindow::acquireReferer() // editingFinished()
{
    argReferer = "";

    if (refererEdit->text() != "")
        argReferer = "--referer=" + refererEdit->text();
}

void MainWindow::acquireAlloc() // activated (new selection)
{
    argAlloc = "";

    if (allocCombo->currentText() == "none") {
        argAlloc = "--file-allocation=none";
        sizeLimitEdit->setEnabled(true);
    } else
        sizeLimitEdit->setEnabled(false);
}

void MainWindow::acquireSizeLimit() // editingFinished()
{
    argSizeLimit = "";

    if (sizeLimitEdit->text() != "5M")
        argSizeLimit = "--no-file-allocation-limit=" + sizeLimitEdit->text();
}

void MainWindow::acquireOverwrite() // activated (new selection)
{
    argOverwrite = "";

    if (overwriteCombo->currentText() == "true")
        argOverwrite = "--allow-overwrite=true";
}

void MainWindow::acquireForceSeq() // activated (new selection)
{
    argForceSeq = "";

    if (forceCombo->currentText() == "true")
        argForceSeq = "--force-sequential=true";
}

void MainWindow::acquireParameter() // activated (new selection)
{
    argParameter = "";

    if (paramCombo->currentText() == "true")
        argParameter = "--parameterized-uri=true";
}

void MainWindow::browseCookieFiles() // cookie browse btn press
{
    cookiesEdit->blockSignals(true);

    argCookies = "";

    argCookies = QFileDialog::getOpenFileName(
            this, "Open File - aria2fe", QDir::homePath(), "All Files (*)");

    if (!argCookies.isEmpty()) {
        cookiesEdit->setText(argCookies);
        argCookies = "--load-cookies=" + cookiesEdit->text();
    }

    cookiesEdit->setFocus();

    cookiesEdit->blockSignals(false);
}

void MainWindow::acquireCookies() // editingFinished()
{
    argCookies = "";

    if (cookiesEdit->text() != "")
        argCookies = "--load-cookies=" + cookiesEdit->text();
}

void MainWindow::acquireMaxConcurrent() // editingFinished()
{
    argMaxConcurrent = "";

    if (maxConcurrentEdit->text() != "5")
        argMaxConcurrent =
                "--max-concurrent-downloads=" + maxConcurrentEdit->text();
}

void MainWindow::acquireDirect() // activated (new selection)
{
    argDirect = "";

    if (directCombo->currentText() == "true")
        argDirect = "--enable-direct-io=true";
}

void MainWindow::acquirePieceLength() // activated (new selection)
{
    argPieceLength = "";

    if (pieceLengthCombo->currentText() == "true")
        argPieceLength = "--allow-piece-length-change=true";
}

void MainWindow::acquireAddOpts() // editingFinished()
{
    argAddOpts.clear();
    argAddOpts = addOptsEdit->text().split(delimiter);
}

//
// dialog procedure blocks begin here
//
void MainWindow::callHttpDlg() // http btn press
{
    httpArgsDlg().exec();

    //    httpArgsDlg *httpDlg=new httpArgsDlg;
    //    httpDlg->exec();
}

void MainWindow::callFtpDlg() // ftp btn press
{
    ftpArgsDlg().exec();

    //    ftpArgsDlg *ftpDlg=new ftpArgsDlg;
    //    ftpDlg->exec();
}

void MainWindow::callMetaDlg() // meta btn press
{
    metaArgsDlg().exec();

    //    metaArgsDlg *metaDlg=new metaArgsDlg;
    //    metaDlg->exec();
}

void MainWindow::callTorrentDlg() // torrent btn press
{
    torrentArgsDlg().exec();

    //    torrentArgsDlg *torrentDlg=new torrentArgsDlg;
    //    torrentDlg->exec();
}

//
// this is where it all comes together
//
void MainWindow::runExternal() // called by catArgs
{
    QProcess program;
    if (!program.startDetached("xterm", arguments))
        QMessageBox::critical(this, "Error - aria2fe",
                              "Could not invoke xterm/aria2! Check for \n"
                              "proper installation in your system path.");
    else
        statusBar()->showMessage("xterm/aria2 startDetached: Success");
}

void MainWindow::catArgs() // called by run action, aria2 help/config actions
{
    args.clear();
    arguments.clear();

    if (aria2Help) {
        aria2Help = false;
        arguments = argsXterm + (QStringList() << "--help");
        runExternal();
    } else if (aria2Version) {
        aria2Version = false;
        arguments = argsXterm + (QStringList() << "--version");
        runExternal();
    } else {
        MenuBar->setFocus(); // fake out focus for Ctrl+R (run)
        if (argUriFileName == "") {
            QMessageBox::warning(this, "Warning - aria2fe",
                                 "You must specify at least one URL!");
            uriEdit->setFocus();
            return;
        }

        args.append(argUriType); // mainwindow args
        args.append(argUriFileName);
        args.append(argDaemon);
        args.append(argNetrc);
        args.append(argTargetDir);
        args.append(argTargetFileName);
        args.append(argLogFileName);
        args.append(argCookies);
        args.append(argReferer);
        args.append(argMinDownSpeed);
        args.append(argMaxDownSpeed);
        args.append(argMaxTries);
        args.append(argSplit);
        args.append(argRetryDelay);
        args.append(argTimeout);
        args.append(argAlloc);
        args.append(argSizeLimit);
        args.append(argMaxConcurrent);
        args.append(argOverwrite);
        args.append(argForceSeq);
        args.append(argParameter);
        args.append(argDirect);
        args.append(argPieceLength); // end mainwindow args

        args.append(argFtpContinue); // ftp dlg args
        args.append(argFtpPassive);
        args.append(argFtpType);
        args.append(argFtpViaHttp);
        args.append(argFtpRename);
        args.append(argFtpUser);
        args.append(argFtpPasswd); // end ftp dlg args

        args.append(argHttpContinue); // http dlg args
        args.append(argHttpPersistence);
        args.append(argHttpRename);
        args.append(argHttpScheme);
        args.append(argHttpPipelining);
        args.append(argHttpMethod);
        args.append(argHttpAgent);
        args.append(argHttpProxyServer);
        args.append(argHttpUser);
        args.append(argHttpPasswd);
        args.append(argHttpProxyUser);
        args.append(argHttpProxyPasswd); // end http dlg args

        args.append(argMetaShowFiles); // metalink dlg args
        args.append(argMetaFollow);
        args.append(argMetaIntegrity);
        args.append(argMetaChecksum);
        args.append(argMetaIndex);
        args.append(argMetaServers);
        args.append(argMetaVersion);
        args.append(argMetaLanguage);
        args.append(argMetaOs);
        args.append(argMetaLocation); // end metalink dlg args

        args.append(argTorrentShowFiles); // torrent dlg args
        args.append(argTorrentFollow);
        args.append(argTorrentIntegrity);
        args.append(argTorrentMapping);
        args.append(argTorrentIndex);
        args.append(argTorrentPorts);
        args.append(argTorrentMaxSpeed);
        args.append(argTorrentSeedTime);
        args.append(argTorrentSeedRatio);
        args.append(argTorrentPeer); // end torrent dlg args

        args = args + argAddOpts;

        argsDlg *argList = new argsDlg;

        QStringList work = args;
        QStringList::Iterator it = work.begin();
        it = work.begin();
        while (it != work.end()) {
            if (*it != "") {
                arguments.append(*it);
                argList->listWidget->addItem(*it);
            }
            ++it;
        }

        if (!argList->exec() == QDialog::Accepted)
            return;

        arguments = argsXterm + arguments;
        runExternal();
    }
}

void MainWindow::restoreDefaults() // menubar/toolbar action
{                                  // restore widgets with default values
    daemonCkBox->setChecked(false);
    netrcCkBox->setChecked(false);
    logFileEdit->setText("aria2.work.log");
    maxTriesEdit->setText("5");
    splitEdit->setText("1");
    retryEdit->setText("5");
    timeoutEdit->setText("60");
    minSpeedEdit->setText("0");
    maxSpeedEdit->setText("0");
    sizeLimitEdit->setText("5M");
    maxConcurrentEdit->setText("5");
    uriEdit->clear();
    targetDirEdit->clear();
    targetFileEdit->clear();
    refererEdit->clear();
    cookiesEdit->clear();
    addOptsEdit->clear();
    uriCombo->setCurrentIndex(0);
    allocCombo->setCurrentIndex(0);
    overwriteCombo->setCurrentIndex(0);
    forceCombo->setCurrentIndex(0);
    paramCombo->setCurrentIndex(0);
    directCombo->setCurrentIndex(0);
    pieceLengthCombo->setCurrentIndex(0);
    argLogFileName = "--log=aria2.work.log";

    argUriType = "";
    argUriFileName = "";
    argTargetDir = "";
    argTargetFileName = "";
    argAlloc = "";
    argOverwrite = "";
    argForceSeq = "";
    argParameter = "";
    argDaemon = "";
    argNetrc = "";
    argSplit = "";
    argRetryDelay = "";
    argTimeout = "";
    argMaxTries = "";
    argReferer = "";
    argMinDownSpeed = "";
    argMaxDownSpeed = "";
    argSizeLimit = "";
    argCookies = "";
    argMaxConcurrent = "";
    argDirect = "";
    argPieceLength = "";

    fileSaveAction->setEnabled(false);
    sizeLimitEdit->setEnabled(false);
    httpBtn->setEnabled(true);
    ftpBtn->setEnabled(true);
    metaBtn->setEnabled(false);
    torrentBtn->setEnabled(false);

    args.clear();
    argAddOpts.clear();

    confFileName = "";

    statusBar()->clearMessage();
    confFile->setText("Ready"); // label widget at far right of statusbar

    uriEdit->setFocus();

    QMessageBox::warning(this, "Warning - aria2fe",
                         "The Main argument list has been cleared! If\n"
                         "you want to initiate a download you must first\n"
                         "specify ALL of the appropriate options.");
}

void MainWindow::saveWidgets() // called by fileSave, fileSaveAs
{
    QFile file(saveFileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream streamOut(&file);

        streamOut << "# DO NOT edit this file! Instead, regen it with aria2fe."
                  << "\n";
        streamOut << appName << "\n";

        // mainwindow widgets out
        streamOut << daemonCkBox->isChecked() << "\n"
                  << uriCombo->currentIndex() << "\n"
                  << uriEdit->text() << "\n"
                  << targetDirEdit->text() << "\n"
                  << targetFileEdit->text() << "\n"
                  << logFileEdit->text() << "\n"
                  << maxTriesEdit->text() << "\n"
                  << splitEdit->text() << "\n"
                  << retryEdit->text() << "\n"
                  << timeoutEdit->text() << "\n"
                  << minSpeedEdit->text() << "\n"
                  << maxSpeedEdit->text() << "\n"
                  << refererEdit->text() << "\n"
                  << allocCombo->currentIndex() << "\n"
                  << overwriteCombo->currentIndex() << "\n"
                  << forceCombo->currentIndex() << "\n"
                  << paramCombo->currentIndex() << "\n"
                  << cookiesEdit->text() << "\n"
                  << maxConcurrentEdit->text() << "\n"
                  << sizeLimitEdit->text() << "\n"
                  << addOptsEdit->text() << "\n"
                  << netrcCkBox->isChecked() << "\n"
                  << directCombo->currentIndex() << "\n"
                  << pieceLengthCombo->currentIndex() << "\n";

        // ftp widgets out
        streamOut << ftpContinue << "\n"
                  << ftpPassive << "\n"
                  << ftpType << "\n"
                  << ftpViaHttp << "\n"
                  << ftpRename << "\n"
                  << ftpUser << "\n"
                  << ftpPasswd << "\n";

        // http widgets out
        streamOut << httpContinue << "\n"
                  << httpPersistence << "\n"
                  << httpRename << "\n"
                  << httpScheme << "\n"
                  << httpPipelining << "\n"
                  << httpMethod << "\n"
                  << httpAgent << "\n"
                  << httpProxyServer << "\n"
                  << httpUser << "\n"
                  << httpPasswd << "\n"
                  << httpProxyUser << "\n"
                  << httpProxyPasswd << "\n";

        // meta widgets out
        streamOut << metaShowFiles << "\n"
                  << metaFollow << "\n"
                  << metaIntegrity << "\n"
                  << metaChecksum << "\n"
                  << metaIndex << "\n"
                  << metaServers << "\n"
                  << metaVersion << "\n"
                  << metaLanguage << "\n"
                  << metaOs << "\n"
                  << metaLocation << "\n";

        // torrent widgets out
        streamOut << torrentShowFiles << "\n"
                  << torrentFollow << "\n"
                  << torrentIntegrity << "\n"
                  << torrentMapping << "\n"
                  << torrentIndex << "\n"
                  << torrentPorts << "\n"
                  << torrentMaxSpeed << "\n"
                  << torrentSeedTime << "\n"
                  << torrentSeedRatio << "\n"
                  << torrentPeer << "\n";

        file.close();
        statusBar()->showMessage("Saved: " + saveFileName);
    } else {
        QMessageBox::critical(this, "Error - aria2fe",
                              "Could not open \".conf\" file for write\n"
                              "operation! Unable to save widget states.");
    }
}

void MainWindow::loadWidgets() // called by fileOpen
{
    if (QFile::exists(confFileName)) {
        QFile file(confFileName);
        file.open(QIODevice::ReadOnly);
        QTextStream streamIn(&file);
        streamIn.readLine();
        if (streamIn.readLine() != appName) {
            QMessageBox::critical(this, "Error - aria2fe",
                                  "Corrupt \".conf\" file format!\n"
                                  "Unable to set widget states.");
        } else {
            daemonCkBox->setChecked(streamIn.readLine().toInt());
            uriCombo->setCurrentIndex(streamIn.readLine().toInt());
            uriEdit->setText(streamIn.readLine());
            targetDirEdit->setText(streamIn.readLine());
            targetFileEdit->setText(streamIn.readLine());
            logFileEdit->setText(streamIn.readLine());
            maxTriesEdit->setText(streamIn.readLine());
            splitEdit->setText(streamIn.readLine());
            retryEdit->setText(streamIn.readLine());
            timeoutEdit->setText(streamIn.readLine());
            minSpeedEdit->setText(streamIn.readLine());
            maxSpeedEdit->setText(streamIn.readLine());
            refererEdit->setText(streamIn.readLine());
            allocCombo->setCurrentIndex(streamIn.readLine().toInt());
            overwriteCombo->setCurrentIndex(streamIn.readLine().toInt());
            forceCombo->setCurrentIndex(streamIn.readLine().toInt());
            paramCombo->setCurrentIndex(streamIn.readLine().toInt());
            cookiesEdit->setText(streamIn.readLine());
            maxConcurrentEdit->setText(streamIn.readLine());
            sizeLimitEdit->setText(streamIn.readLine());
            addOptsEdit->setText(streamIn.readLine());
            netrcCkBox->setChecked(streamIn.readLine().toInt());
            directCombo->setCurrentIndex(streamIn.readLine().toInt());
            pieceLengthCombo->setCurrentIndex(streamIn.readLine().toInt());

            ftpContinue = streamIn.readLine().toInt(); // ftp dlg widget states
            ftpPassive = streamIn.readLine().toInt();
            ftpType = streamIn.readLine().toInt();
            ftpViaHttp = streamIn.readLine().toInt();
            ftpRename = streamIn.readLine().toInt();
            ftpUser = streamIn.readLine();
            ftpPasswd = streamIn.readLine(); // end ftp dlg widget states

            httpContinue = streamIn.readLine().toInt(); // http dlg widget
                                                        // states
            httpPersistence = streamIn.readLine().toInt();
            httpRename = streamIn.readLine().toInt();
            httpScheme = streamIn.readLine().toInt();
            httpPipelining = streamIn.readLine().toInt();
            httpMethod = streamIn.readLine().toInt();
            httpAgent = streamIn.readLine();
            httpProxyServer = streamIn.readLine();
            httpUser = streamIn.readLine();
            httpPasswd = streamIn.readLine();
            httpProxyUser = streamIn.readLine();
            httpProxyPasswd = streamIn.readLine(); // end http dlg widget states

            metaShowFiles =
                    streamIn.readLine().toInt(); // meta dlg widget states
            metaFollow = streamIn.readLine().toInt();
            metaIntegrity = streamIn.readLine().toInt();
            metaChecksum = streamIn.readLine().toInt();
            metaIndex = streamIn.readLine();
            metaServers = streamIn.readLine();
            metaVersion = streamIn.readLine();
            metaLanguage = streamIn.readLine();
            metaOs = streamIn.readLine();
            metaLocation = streamIn.readLine(); // end meta dlg widget states

            torrentShowFiles =
                    streamIn.readLine().toInt(); // torrent dlg widget states
            torrentFollow = streamIn.readLine().toInt();
            torrentIntegrity = streamIn.readLine().toInt();
            torrentMapping = streamIn.readLine().toInt();
            torrentIndex = streamIn.readLine();
            torrentPorts = streamIn.readLine();
            torrentMaxSpeed = streamIn.readLine();
            torrentSeedTime = streamIn.readLine();
            torrentSeedRatio = streamIn.readLine();
            torrentPeer = streamIn.readLine(); // end torrent dlg widget states

            file.close();

            acquireDaemon();
            acquireNetrc();
            acquireUriType();
            acquireUriObject();
            acquireTargetDir();
            acquireTargetFileName();
            acquireLogFileName();
            acquireMaxTries();
            acquireSplit();
            acquireRetryDelay();
            acquireTimeout();
            acquireMinDownSpeed();
            acquireMaxDownSpeed();
            acquireReferer();
            acquireAlloc();
            acquireSizeLimit();
            acquireOverwrite();
            acquireForceSeq();
            acquireParameter();
            acquireCookies();
            acquireMaxConcurrent();
            acquireDirect();
            acquirePieceLength();
            acquireAddOpts();

            ftpArgsDlg().acquireAll();
            httpArgsDlg().acquireAll();
            metaArgsDlg().acquireAll();
            torrentArgsDlg().acquireAll();

            statusBar()->showMessage("Loaded:");
            confFile->setText(
                    confFileName); // label widget at far right of statusbar
        }
    }
}

void MainWindow::setupConnections() // called by constructor
{
    connect(fileOpenAction, SIGNAL(activated()), this, SLOT(fileOpen()));
    connect(fileSaveAction, SIGNAL(activated()), this, SLOT(fileSave()));
    connect(fileSaveAsAction, SIGNAL(activated()), this, SLOT(fileSaveAs()));
    connect(fileQuitAction, SIGNAL(activated()), this, SLOT(fileExit()));
    connect(toolsRestoreDefaultsAction, SIGNAL(activated()), this,
            SLOT(restoreDefaults()));
    connect(toolsRunAction, SIGNAL(activated()), this, SLOT(catArgs()));
    connect(helpAria2feHelpAction, SIGNAL(activated()), this,
            SLOT(helpAria2fe()));
    connect(helpAria2HelpAction, SIGNAL(activated()), this, SLOT(helpAria2()));
    connect(helpAria2VersionAction, SIGNAL(activated()), this,
            SLOT(versionAria2()));
    connect(helpAboutAction, SIGNAL(activated()), this, SLOT(helpAbout()));
    connect(helpAboutQtAction, SIGNAL(activated()), this, SLOT(helpAboutQt()));
    connect(uriBrowseBtn, SIGNAL(released()), this, SLOT(browseUriObject()));
    connect(uriClearBtn, SIGNAL(released()), this, SLOT(clearUri()));
    connect(uriCombo, SIGNAL(activated(QString)), this, SLOT(acquireUriType()));
    connect(uriEdit, SIGNAL(editingFinished()), this, SLOT(acquireUriObject()));
    connect(daemonCkBox, SIGNAL(toggled(bool)), this, SLOT(acquireDaemon()));
    connect(netrcCkBox, SIGNAL(toggled(bool)), this, SLOT(acquireNetrc()));
    connect(targetDirBrowseBtn, SIGNAL(released()), this,
            SLOT(browseTargetDir()));
    connect(targetDirClearBtn, SIGNAL(released()), this,
            SLOT(clearTargetDir()));
    connect(targetDirEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireTargetDir()));
    connect(targetFileClearBtn, SIGNAL(released()), this,
            SLOT(clearTargetFile()));
    connect(targetFileEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireTargetFileName()));
    connect(logFileClearBtn, SIGNAL(released()), this, SLOT(clearLogFile()));
    connect(logFileEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireLogFileName()));
    connect(maxTriesEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireMaxTries()));
    connect(splitEdit, SIGNAL(editingFinished()), this, SLOT(acquireSplit()));
    connect(retryEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireRetryDelay()));
    connect(timeoutEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireTimeout()));
    connect(minSpeedEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireMinDownSpeed()));
    connect(maxSpeedEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireMaxDownSpeed()));
    connect(refererEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireReferer()));
    connect(refererClearBtn, SIGNAL(released()), this, SLOT(clearReferer()));
    connect(addOptsEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireAddOpts()));
    connect(addOptsClearBtn, SIGNAL(released()), this, SLOT(clearAddOpts()));
    connect(allocCombo, SIGNAL(activated(QString)), this, SLOT(acquireAlloc()));
    connect(sizeLimitEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireSizeLimit()));
    connect(overwriteCombo, SIGNAL(activated(QString)), this,
            SLOT(acquireOverwrite()));
    connect(forceCombo, SIGNAL(activated(QString)), this,
            SLOT(acquireForceSeq()));
    connect(paramCombo, SIGNAL(activated(QString)), this,
            SLOT(acquireParameter()));
    connect(cookiesBrowseBtn, SIGNAL(released()), this,
            SLOT(browseCookieFiles()));
    connect(cookiesClearBtn, SIGNAL(released()), this, SLOT(clearCookies()));
    connect(cookiesEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireCookies()));
    connect(maxConcurrentEdit, SIGNAL(editingFinished()), this,
            SLOT(acquireMaxConcurrent()));
    connect(directCombo, SIGNAL(activated(QString)), this,
            SLOT(acquireDirect()));
    connect(pieceLengthCombo, SIGNAL(activated(QString)), this,
            SLOT(acquirePieceLength()));
    connect(ftpBtn, SIGNAL(released()), this, SLOT(callFtpDlg()));
    connect(httpBtn, SIGNAL(released()), this, SLOT(callHttpDlg()));
    connect(metaBtn, SIGNAL(released()), this, SLOT(callMetaDlg()));
    connect(torrentBtn, SIGNAL(released()), this, SLOT(callTorrentDlg()));
}

void MainWindow::init() // called by constructor
{
    appName = "aria2fe"; // init header defined variables
    delimiter = " ";
    aria2Help = false;
    aria2Version = false;
    argsXterm = (QStringList() << "-bg"
                               << "black"
                               << "-fg"
                               << "white"
                               << "-hold"
                               << "-T"
                               << "Console - aria2fe/aria2"
                               << "-wf"
                               << "-font"
                               << "-*-fixed-medium-r-*-*-18-*-*-*-*-*-iso8859-*"
                               << "-geometry"
                               << "90x24"
                               << "-e"
                               << "aria2c");

    confFile = new QLabel("Ready", statusBar()); // set label widget in
                                                 // statusbar
    statusBar()->addPermanentWidget(confFile, 0); // for open *.conf file

    maxTriesEdit->setText("5"); // init numeric masked defaults
    splitEdit->setText("1");
    retryEdit->setText("5");
    timeoutEdit->setText("60");
    minSpeedEdit->setText("0");
    maxSpeedEdit->setText("0");
    sizeLimitEdit->setText("5M");
    maxConcurrentEdit->setText("5");

    logFileEdit->setText("aria2.work.log"); // init log file default
    argLogFileName = "--log=aria2.work.log";

    fileSaveAction->setEnabled(false);
    sizeLimitEdit->setEnabled(false);
    uriBrowseBtn->setEnabled(false);
    metaBtn->setEnabled(false);
    torrentBtn->setEnabled(false);

    uriEdit->setFocus();

    ftpUser = "anonymous"; // start dlg inits
    ftpPasswd = "ARIA2USER@";
    metaServers = "5";
    torrentPorts = "6881-6999";
    torrentMaxSpeed = "0";
    torrentSeedRatio = "1.0";
    torrentPeer = "-aria2-"; // end dlg inits
}
