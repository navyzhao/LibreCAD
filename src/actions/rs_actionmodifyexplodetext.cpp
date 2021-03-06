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

#include "rs_actionmodifyexplodetext.h"

#include "rs_modification.h"

/**
 * Constructor.
 */
RS_ActionModifyExplodeText::RS_ActionModifyExplodeText(RS_EntityContainer& container,
        RS_GraphicView& graphicView)
        :RS_PreviewActionInterface("Blocks Explode",
                           container, graphicView) {
}



RS_ActionModifyExplodeText::~RS_ActionModifyExplodeText() {}


QAction* RS_ActionModifyExplodeText::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
	// tr("Explode Text")
    QAction* action = new QAction(tr("&Explode Text into Letters"), NULL);
	action->setIcon(QIcon(":/extui/modifyexplodetext.png"));
    //action->zetStatusTip(tr("Explodes Text Entities into single Letters"));
    return action;
}


void RS_ActionModifyExplodeText::init(int status) {
    RS_PreviewActionInterface::init(status);

    trigger();
    finish();
}



void RS_ActionModifyExplodeText::trigger() {
    RS_Modification m(*container, graphicView);
    m.explodeTextIntoLetters();
}


// EOF
