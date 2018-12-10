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


#include <aboutdlg.h>


aboutDlg::aboutDlg()  //constructor
{
	setupUi(this);
	init();
}


aboutDlg::~aboutDlg()  //destructor
{
	//no need to delete child widgets, Qt does it all for us
}


void aboutDlg::languageChange()  //future use
{
	retranslateUi(this);
}


void aboutDlg::init()
{
	txtLabel1_2->setText("<b>aria2fe 0.0.5 Build 20071208</b>");
}	
