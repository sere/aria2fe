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


#ifndef TORRENTARGSDLG_H
#define TORRENTARGSDLG_H

#include <ui_torrentargsdlg.h>

#include <QMessageBox>

extern QString argTorrentShowFiles;
extern QString argTorrentFollow;
extern QString argTorrentIntegrity;
extern QString argTorrentMapping;
extern QString argTorrentIndex;
extern QString argTorrentPorts;
extern QString argTorrentMaxSpeed;
extern QString argTorrentSeedTime;
extern QString argTorrentSeedRatio;
extern QString argTorrentPeer;

extern bool torrentShowFiles;
extern int torrentFollow;
extern int torrentIntegrity;
extern int torrentMapping;
extern QString torrentIndex;
extern QString torrentPorts;
extern QString torrentMaxSpeed;
extern QString torrentSeedTime;
extern QString torrentSeedRatio;
extern QString torrentPeer;

class torrentArgsDlg : public QDialog, public Ui::torrentArgsDlg
{
	Q_OBJECT

public:

	torrentArgsDlg();
	~torrentArgsDlg();

public slots:

	void acceptArgs();
	void rejectArgs();
	void acquireTorrentShowFiles();
	void acquireTorrentFollow();
	void acquireTorrentIntegrity();
	void acquireTorrentMapping();
	void acquireTorrentIndex();
	void acquireTorrentPorts();
	void acquireTorrentMaxSpeed();
	void acquireTorrentSeedTime();
	void acquireTorrentSeedRatio();
	void acquireTorrentPeer();
	void acquireAll();
	void restoreDefaults();

protected slots:

	virtual void languageChange();

private:

	void setupConnections();
	void init();
};

#endif // TORRENTARGSDLG_H
