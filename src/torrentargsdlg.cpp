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


#include <torrentargsdlg.h>

QString argTorrentShowFiles;
QString argTorrentFollow;
QString argTorrentIntegrity;
QString argTorrentMapping;
QString argTorrentIndex;
QString argTorrentPorts;
QString argTorrentMaxSpeed;
QString argTorrentSeedTime;
QString argTorrentSeedRatio;
QString argTorrentPeer;

bool torrentShowFiles;
int torrentFollow;
int torrentIntegrity;
int torrentMapping;
QString torrentIndex;
QString torrentPorts;
QString torrentMaxSpeed;
QString torrentSeedTime;
QString torrentSeedRatio;
QString torrentPeer;

torrentArgsDlg::torrentArgsDlg()
{
	setupUi(this);
	setupConnections();
	init();
}


torrentArgsDlg::~torrentArgsDlg()
{
	//no need to delete child widgets, Qt does it all for us
}


void torrentArgsDlg::languageChange()  //future use
{
	retranslateUi(this);
}

void torrentArgsDlg::acceptArgs()  //ok btn
{
	acquireAll();

	torrentShowFiles=torrentShowFilesCkBox->isChecked();
	torrentFollow=torrentFollowCombo->currentIndex();
	torrentIntegrity=torrentIntegrityCombo->currentIndex();
	torrentMapping=torrentMappingCombo->currentIndex();
	torrentIndex=torrentIndexEdit->text();
	torrentPorts=torrentPortsEdit->text();
	torrentMaxSpeed=torrentMaxSpeedEdit->text();
	torrentSeedTime=torrentSeedTimeEdit->text();
	torrentSeedRatio=torrentSeedRatioEdit->text();
	torrentPeer=torrentPeerEdit->text();

	close();
}


void torrentArgsDlg::rejectArgs()  //cancel btn
{
	close();
}


void torrentArgsDlg::acquireTorrentShowFiles()
{
	argTorrentShowFiles="";

	if (torrentShowFilesCkBox->isChecked())
		argTorrentShowFiles="--show-files";
}


void torrentArgsDlg::acquireTorrentFollow()
{
	argTorrentFollow="";

	if (torrentFollowCombo->currentText()=="false")
		argTorrentFollow="--follow-torrent=false";
	else if (torrentFollowCombo->currentText()=="mem")
		argTorrentFollow="--follow-torrent=mem";
}


void torrentArgsDlg::acquireTorrentIntegrity()
{
	argTorrentIntegrity="";

	if (torrentIntegrityCombo->currentText()=="true")
		argTorrentIntegrity="--check-integrity=true";
}


void torrentArgsDlg::acquireTorrentMapping()
{
	argTorrentMapping="";

	if (torrentMappingCombo->currentText()=="false")
		argTorrentMapping="--direct-file-mapping=false";
}


void torrentArgsDlg::acquireTorrentIndex()
{
	argTorrentIndex="";

	if (torrentIndexEdit->text()!="")
		argTorrentIndex="--select-file="+torrentIndexEdit->text();
}


void torrentArgsDlg::acquireTorrentPorts()
{
	argTorrentPorts="";

	if (torrentPortsEdit->text()!="6881-6999")
		argTorrentPorts="--listen-port="+torrentPortsEdit->text();
}


void torrentArgsDlg::acquireTorrentMaxSpeed()
{
	argTorrentMaxSpeed="";

	if (torrentMaxSpeedEdit->text()!="0")
		argTorrentMaxSpeed="--max-upload-limit="+torrentMaxSpeedEdit->text();
}


void torrentArgsDlg::acquireTorrentSeedTime()
{
	argTorrentSeedTime="";

	if (torrentSeedTimeEdit->text()!="")
		argTorrentSeedTime="--seed-time="+torrentSeedTimeEdit->text();
}


void torrentArgsDlg::acquireTorrentSeedRatio()
{
	argTorrentSeedRatio="";

	if (torrentSeedRatioEdit->text()!="1.0")
		argTorrentSeedRatio="--seed-ratio="+torrentSeedRatioEdit->text();
}


void torrentArgsDlg::acquireTorrentPeer()
{
	argTorrentPeer="";

	if (torrentPeerEdit->text()!="-aria2-")
		argTorrentPeer="--peer-id-prefix="+torrentPeerEdit->text();
}


void torrentArgsDlg::acquireAll()
{
	acquireTorrentShowFiles();
	acquireTorrentFollow();
	acquireTorrentIntegrity();
	acquireTorrentMapping();
	acquireTorrentIndex();
	acquireTorrentPorts();
	acquireTorrentMaxSpeed();
	acquireTorrentSeedTime();
	acquireTorrentSeedRatio();
	acquireTorrentPeer();
}


void torrentArgsDlg::restoreDefaults()  //restore btn
{
	torrentShowFilesCkBox->setChecked(false);
	torrentFollowCombo->setCurrentIndex(0);
	torrentIntegrityCombo->setCurrentIndex(0);
	torrentMappingCombo->setCurrentIndex(0);
	torrentIndexEdit->setText("");
	torrentPortsEdit->setText("6881-6999");
	torrentMaxSpeedEdit->setText("0");
	torrentSeedTimeEdit->setText("");
	torrentSeedRatioEdit->setText("1.0");
	torrentPeerEdit->setText("-aria2-");

	argTorrentShowFiles="";
	argTorrentFollow="";
	argTorrentIntegrity="";
	argTorrentMapping="";
	argTorrentIndex="";
	argTorrentPorts="";
	argTorrentMaxSpeed="";
	argTorrentSeedTime="";
	argTorrentSeedRatio="";
	argTorrentPeer="";

	torrentShowFiles=false;
	torrentFollow=0;
	torrentIntegrity=0;
	torrentMapping=0;
	torrentIndex="";
	torrentPorts="6881-6999";
	torrentMaxSpeed="0";
	torrentSeedTime="";
	torrentSeedRatio="1.0";
	torrentPeer="-aria2-";

	QMessageBox::warning
		(this,"Warning - aria2fe","The BitTorrent argument list has been cleared!");
}


void torrentArgsDlg::setupConnections()  //called by constructor
{
	connect(restoreBtn,SIGNAL(released()),this,SLOT(restoreDefaults()));
	connect(okBtn,SIGNAL(released()),this,SLOT(acceptArgs()));
	connect(cancelBtn,SIGNAL(released()),this,SLOT(rejectArgs()));
}


void torrentArgsDlg::init()  //called by constructor
{
	torrentShowFilesCkBox->setChecked(torrentShowFiles);
	torrentFollowCombo->setCurrentIndex(torrentFollow);
	torrentIntegrityCombo->setCurrentIndex(torrentIntegrity);
	torrentMappingCombo->setCurrentIndex(torrentMapping);
	torrentIndexEdit->setText(torrentIndex);
	torrentPortsEdit->setText(torrentPorts);
	torrentMaxSpeedEdit->setText(torrentMaxSpeed);
	torrentSeedTimeEdit->setText(torrentSeedTime);
	torrentSeedRatioEdit->setText(torrentSeedRatio);
	torrentPeerEdit->setText(torrentPeer);

	acquireAll();
}
