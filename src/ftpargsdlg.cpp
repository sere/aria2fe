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


#include <ftpargsdlg.h>

QString argFtpContinue;
QString argFtpPassive;
QString argFtpType;
QString argFtpViaHttp;
QString argFtpRename;
QString argFtpUser;
QString argFtpPasswd;

bool ftpContinue;
bool ftpPassive;
int ftpType;
int ftpViaHttp;
int ftpRename;
QString ftpUser;
QString ftpPasswd;

ftpArgsDlg::ftpArgsDlg()  //constructor
{
	setupUi(this);
	setupConnections();
	init();
}


ftpArgsDlg::~ftpArgsDlg()  //destructor
{
	//no need to delete child widgets, Qt does it all for us
}


void ftpArgsDlg::languageChange()  //future use
{
	retranslateUi(this);
}


void ftpArgsDlg::acceptArgs()  //ok btn
{
	acquireAll();

	ftpContinue=ftpContinueCkBox->isChecked();
	ftpPassive=ftpPassiveCkBox->isChecked();
	ftpType=ftpTypeCombo->currentIndex();
	ftpViaHttp=ftpViaHttpCombo->currentIndex();
	ftpRename=ftpRenameCombo->currentIndex();
	ftpUser=ftpUserEdit->text();
	ftpPasswd=ftpPasswdEdit->text();

	close();
}


void ftpArgsDlg::rejectArgs()  //cancel btn
{
	close();
}


void ftpArgsDlg::acquireFtpContinue()
{
	argFtpContinue="";

	if (ftpContinueCkBox->isChecked())
		argFtpContinue="--continue";
}


void ftpArgsDlg::acquireFtpPassive()
{
	argFtpPassive="";

	if (ftpPassiveCkBox->isChecked())
		argFtpPassive="--ftp-pasv";
}


void ftpArgsDlg::acquireFtpType()
{
	argFtpType="";

	if (ftpTypeCombo->currentText()=="ascii")
		argFtpType="--ftp-type=ascii";
}


void ftpArgsDlg::acquireFtpViaHttp()
{
	argFtpViaHttp="";

	if (ftpViaHttpCombo->currentText()=="get")
		argFtpViaHttp="--ftp-via-http-proxy=get";
}


void ftpArgsDlg::acquireFtpRename()
{
	argFtpRename="";

	if (ftpRenameCombo->currentText()=="false")
		argFtpRename="--auto-file-renaming=false";
}


void ftpArgsDlg::acquireFtpUser()
{
	argFtpUser="";

	if (ftpUserEdit->text()!="anonymous")
		argFtpUser="--ftp-user="+ftpUserEdit->text();
}


void ftpArgsDlg::acquireFtpPasswd()
{
	argFtpPasswd="";

	if (ftpPasswdEdit->text()!="ARIA2USER@")
		argFtpPasswd="--ftp-passwd="+ftpPasswdEdit->text();
}

void ftpArgsDlg::acquireAll()
{
	acquireFtpContinue();
	acquireFtpPassive();
	acquireFtpType();
	acquireFtpViaHttp();
	acquireFtpRename();
	acquireFtpUser();
	acquireFtpPasswd();
}


void ftpArgsDlg::restoreDefaults()  //restore btn
{
	ftpContinueCkBox->setChecked(false);
	ftpPassiveCkBox->setChecked(false);
	ftpTypeCombo->setCurrentIndex(0);
	ftpViaHttpCombo->setCurrentIndex(0);
	ftpRenameCombo->setCurrentIndex(0);
	ftpUserEdit->setText("anonymous");
	ftpPasswdEdit->setText("ARIA2USER@");

	argFtpContinue="";
	argFtpPassive="";
	argFtpType="";
	argFtpViaHttp="";
	argFtpRename="";
	argFtpUser="";
	argFtpPasswd="";

	ftpContinue=false;
	ftpPassive=false;
	ftpType=0;
	ftpViaHttp=0;
	ftpRename=0;
	ftpUser="anonymous";
	ftpPasswd="ARIA2USER@";

	QMessageBox::warning
		(this,"Warning - aria2fe","The FTP argument list has been cleared!");
}


void ftpArgsDlg::setupConnections()  //called by constructor
{
	connect(restoreBtn,SIGNAL(released()),this,SLOT(restoreDefaults()));
	connect(okBtn,SIGNAL(released()),this,SLOT(acceptArgs()));
	connect(cancelBtn,SIGNAL(released()),this,SLOT(rejectArgs()));
}


void ftpArgsDlg::init()  //called by constructor
{
	ftpContinueCkBox->setChecked(ftpContinue);
	ftpPassiveCkBox->setChecked(ftpPassive);
	ftpTypeCombo->setCurrentIndex(ftpType);
	ftpViaHttpCombo->setCurrentIndex(ftpViaHttp);
	ftpRenameCombo->setCurrentIndex(ftpRename);
	ftpUserEdit->setText(ftpUser);
	ftpPasswdEdit->setText(ftpPasswd);

	acquireAll();
}
