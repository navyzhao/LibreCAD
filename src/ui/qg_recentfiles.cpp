/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by 
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/

#include "qg_recentfiles.h"

#include "rs_debug.h"

/**
 * Constructor
 * @param number Number of files that can be stored in the list at maximum
 */
QG_RecentFiles::QG_RecentFiles(int number) {
    this->number = number;
}


/**
 * Destructor
 */
QG_RecentFiles::~QG_RecentFiles() {}

/**
 * Adds a file to the list of recently loaded files if 
 * it's not already in the list.
 */
void QG_RecentFiles::add(const QString& filename) {
	RS_DEBUG->print("QG_RecentFiles::add");
	
    // is the file already in the list?
    if (files.find(filename) != files.end()) {
        return;
    }

    // append
    //files.push_back(filename);
    files.append(filename);
    if ((int)files.count() > number) {
        // keep the list short
        files.pop_front();
    }

    //for (int i=0; i<(int)files.count(); ++i) {
    //	printf("recent file[%d]: %s\n", i, files[i].latin1());
    //}
	RS_DEBUG->print("QG_RecentFiles::add: OK");
}


