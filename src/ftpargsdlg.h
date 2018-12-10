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


#ifndef FTPARGSDLG_H
#define FTPARGSDLG_H

#include <ui_ftpargsdlg.h>

#include <QMessageBox>

extern QString argFtpContinue;
extern QString argFtpPassive;
extern QString argFtpType;
extern QString argFtpViaHttp;
extern QString argFtpRename;
extern QString argFtpUser;
extern QString argFtpPasswd;

extern bool ftpContinue;
extern bool ftpPassive;
extern int ftpType;
extern int ftpViaHttp;
extern int ftpRename;
extern QString ftpUser;
extern QString ftpPasswd;

class ftpArgsDlg : public QDialog, public Ui::ftpArgsDlg
{
	Q_OBJECT

public:

	ftpArgsDlg();
	~ftpArgsDlg();

public slots:

	void acceptArgs();
	void rejectArgs();
	void acquireFtpContinue();
	void acquireFtpPassive();
	void acquireFtpType();
	void acquireFtpViaHttp();
	void acquireFtpRename();
	void acquireFtpUser();
	void acquireFtpPasswd();
	void acquireAll();
	void restoreDefaults();

protected slots:

	virtual void languageChange();

private:

	void setupConnections();
	void init();
};

#endif // FTPARGSDLG_H
