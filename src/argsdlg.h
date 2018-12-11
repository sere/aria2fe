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

#ifndef ARGSDLG_H
#define ARGSDLG_H

#include <ui_argsdlg.h>

class argsDlg : public QDialog, public Ui::argsDlg {
    Q_OBJECT

public:
    argsDlg();
    ~argsDlg();

protected slots:

    virtual void languageChange();
};

#endif // ARGSDLG_H
