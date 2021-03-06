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

#include "rs_actionfileopen.h"

#include "rs_graphic.h"
//Added by qt3to4:
#include <q3mimefactory.h>



RS_ActionFileOpen::RS_ActionFileOpen(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
        :RS_ActionInterface("File Open", container, graphicView) {}


QAction* RS_ActionFileOpen::createGUIAction(RS2::ActionType /*type*/, QObject* parent) {
	// tr("Open Drawing")
	QAction* action = new QAction(tr("&Open..."), parent);
	action->setIcon(QIcon(":/actions/fileopen2.png"));
	action->setShortcut(QKeySequence::Open);
    //action->zetStatusTip(tr("Opens an existing drawing"));
    return action;
}


void RS_ActionFileOpen::trigger() {
    /*
    // Not supported currently
    RS_DEBUG->print("RS_ActionFileOpen::trigger");

    RS_String fileName; //= RS_DIALOGFACTORY->requestFileOpenDialog();
    if (graphic!=NULL && !fileName.isEmpty()) {
        graphic->open(fileName, );
}
    */
    finish();
}


void RS_ActionFileOpen::init(int status) {
    RS_ActionInterface::init(status);
    trigger();
}

// EOF
