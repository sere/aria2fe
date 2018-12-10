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


#ifndef METAARGSDLG_H
#define METAARGSDLG_H

#include <ui_metaargsdlg.h>

#include <QMessageBox>

extern QString argMetaShowFiles;
extern QString argMetaFollow;
extern QString argMetaIntegrity;
extern QString argMetaChecksum;
extern QString argMetaIndex;
extern QString argMetaServers;
extern QString argMetaVersion;
extern QString argMetaLanguage;
extern QString argMetaOs;
extern QString argMetaLocation;

extern bool metaShowFiles;
extern int metaFollow;
extern int metaIntegrity;
extern int metaChecksum;
extern QString metaIndex;
extern QString metaServers;
extern QString metaVersion;
extern QString metaLanguage;
extern QString metaOs;
extern QString metaLocation;

class metaArgsDlg : public QDialog, public Ui::metaArgsDlg
{
	Q_OBJECT

public:

	metaArgsDlg();
	~metaArgsDlg();

public slots:

	void acceptArgs();
	void rejectArgs();
	void acquireMetaShowFiles();
	void acquireMetaFollow();
	void acquireMetaIntegrity();
	void acquireMetaChecksum();
	void acquireMetaIndex();
	void acquireMetaServers();
	void acquireMetaVersion();
	void acquireMetaLanguage();
	void acquireMetaOs();
	void acquireMetaLocation();
	void acquireAll();
	void restoreDefaults();

protected slots:

	virtual void languageChange();

private:

	void setupConnections();
	void init();
};

#endif // METAARGSDLG_H
