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


#include <metaargsdlg.h>

QString argMetaShowFiles;
QString argMetaFollow;
QString argMetaIntegrity;
QString argMetaChecksum;
QString argMetaIndex;
QString argMetaServers;
QString argMetaVersion;
QString argMetaLanguage;
QString argMetaOs;
QString argMetaLocation;

bool metaShowFiles;
int metaFollow;
int metaIntegrity;
int metaChecksum;
QString metaIndex;
QString metaServers;
QString metaVersion;
QString metaLanguage;
QString metaOs;
QString metaLocation;

metaArgsDlg::metaArgsDlg()
{
	setupUi(this);
	setupConnections();
	init();
}


metaArgsDlg::~metaArgsDlg()
{
	//no need to delete child widgets, Qt does it all for us
}


void metaArgsDlg::languageChange()  //future use
{
	retranslateUi(this);
}


void metaArgsDlg::acceptArgs()  //ok btn
{
	acquireAll();

	metaShowFiles=metaShowFilesCkBox->isChecked();
	metaFollow=metaFollowCombo->currentIndex();
	metaIntegrity=metaIntegrityCombo->currentIndex();
	metaChecksum=metaChecksumCombo->currentIndex();
	metaIndex=metaIndexEdit->text();
	metaServers=metaServersEdit->text();
	metaVersion=metaVersionEdit->text();
	metaLanguage=metaLanguageEdit->text();
	metaOs=metaOsEdit->text();
	metaLocation=metaLocationEdit->text();

	close();
}


void metaArgsDlg::rejectArgs()  //cancel btn
{
	close();
}


void metaArgsDlg::acquireMetaShowFiles()
{
	argMetaShowFiles="";

	if (metaShowFilesCkBox->isChecked())
		argMetaShowFiles="--show-files";
}


void metaArgsDlg::acquireMetaFollow()
{
	argMetaFollow="";

	if (metaFollowCombo->currentText()=="false")
		argMetaFollow="--follow-metalink=false";
	else if (metaFollowCombo->currentText()=="mem")
		argMetaFollow="--follow-metalink=mem";
}


void metaArgsDlg::acquireMetaIntegrity()
{
	argMetaIntegrity="";

	if (metaIntegrityCombo->currentText()=="true")
		argMetaIntegrity="--check-integrity=true";
}


void metaArgsDlg::acquireMetaChecksum()
{
	argMetaChecksum="";

	if (metaChecksumCombo->currentText()=="false")
		argMetaChecksum="--realtime-chunk-checksum=false";
}


void metaArgsDlg::acquireMetaIndex()
{
	argMetaIndex="";

	if (metaIndexEdit->text()!="")
		argMetaIndex="--select-file="+metaIndexEdit->text();
}


void metaArgsDlg::acquireMetaServers()
{
	argMetaServers="";

	if (metaServersEdit->text()!="5")
		argMetaServers="--metalink-servers="+metaServersEdit->text();
}


void metaArgsDlg::acquireMetaVersion()
{
	argMetaVersion="";

	if (metaVersionEdit->text()!="")
		argMetaVersion="--metalink-version="+metaVersionEdit->text();
}


void metaArgsDlg::acquireMetaLanguage()
{
	argMetaLanguage="";

	if (metaLanguageEdit->text()!="")
		argMetaLanguage="--metalink-language="+metaLanguageEdit->text();
}


void metaArgsDlg::acquireMetaOs()
{
	argMetaOs="";

	if (metaOsEdit->text()!="")
		argMetaOs="--metalink-os="+metaOsEdit->text();
}


void metaArgsDlg::acquireMetaLocation()
{
	argMetaLocation="";

	if (metaLocationEdit->text()!="")
		argMetaLocation="--metalink-location="+metaLocationEdit->text();
}


void metaArgsDlg::acquireAll()
{
	acquireMetaShowFiles();
	acquireMetaFollow();
	acquireMetaIntegrity();
	acquireMetaChecksum();
	acquireMetaIndex();
	acquireMetaServers();
	acquireMetaVersion();
	acquireMetaLanguage();
	acquireMetaOs();
	acquireMetaLocation();
}


void metaArgsDlg::restoreDefaults()  //restore btn
{
	metaShowFilesCkBox->setChecked(false);
	metaFollowCombo->setCurrentIndex(0);
	metaIntegrityCombo->setCurrentIndex(0);
	metaChecksumCombo->setCurrentIndex(0);
	metaIndexEdit->setText("");
	metaServersEdit->setText("5");
	metaVersionEdit->setText("");
	metaLanguageEdit->setText("");
	metaOsEdit->setText("");
	metaLocationEdit->setText("");

	argMetaShowFiles="";
	argMetaFollow="";
	argMetaIntegrity="";
	argMetaChecksum="";
	argMetaIndex="";
	argMetaServers="";
	argMetaVersion="";
	argMetaLanguage="";
	argMetaOs="";
	argMetaLocation="";

	metaShowFiles=false;
	metaFollow=0;
	metaIntegrity=0;
	metaChecksum=0;
	metaIndex="";
	metaServers="5";
	metaVersion="";
	metaLanguage="";
	metaOs="";
	metaLocation="";

	QMessageBox::warning
		(this,"Warning - aria2fe","The Metalink argument list has been cleared!");
}


void metaArgsDlg::setupConnections()  //called by constructor
{
	connect(restoreBtn,SIGNAL(released()),this,SLOT(restoreDefaults()));
	connect(okBtn,SIGNAL(released()),this,SLOT(acceptArgs()));
	connect(cancelBtn,SIGNAL(released()),this,SLOT(rejectArgs()));
}


void metaArgsDlg::init()  //called by constructor
{
	metaShowFilesCkBox->setChecked(metaShowFiles);
	metaFollowCombo->setCurrentIndex(metaFollow);
	metaIntegrityCombo->setCurrentIndex(metaIntegrity);
	metaChecksumCombo->setCurrentIndex(metaChecksum);
	metaIndexEdit->setText(metaIndex);
	metaServersEdit->setText(metaServers);
	metaVersionEdit->setText(metaVersion);
	metaLanguageEdit->setText(metaLanguage);
	metaOsEdit->setText(metaOs);
	metaLocationEdit->setText(metaLocation);

	acquireAll();
}
