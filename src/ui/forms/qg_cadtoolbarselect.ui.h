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
#include <QMouseEvent>
#include <QContextMenuEvent>
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void QG_CadToolBarSelect::init() {
    cadToolBar = NULL;
    actionHandler = NULL;
    selectAction = NULL;
    nextAction = -1;
}

void QG_CadToolBarSelect::mousePressEvent(QMouseEvent* e) {
    if (e->button()==Qt::RightButton && cadToolBar!=NULL) {
        cadToolBar->back();
        e->accept();
    }
}

void QG_CadToolBarSelect::contextMenuEvent(QContextMenuEvent *e) {
    e->accept();
}

void QG_CadToolBarSelect::setCadToolBar(QG_CadToolBar* tb) {
    cadToolBar = tb;
    if (tb!=NULL) {
        actionHandler = tb->getActionHandler();
        //actionHandler->setCadToolBarSelect(this);
    }
    else {
        RS_DEBUG->print(RS_Debug::D_ERROR, 
			"QG_CadToolBarSelect::setCadToolBar(): No valid toolbar set.");
    }
}

void QG_CadToolBarSelect::selectSingle() {
    if (actionHandler!=NULL) {
        actionHandler->slotSelectSingle();
    }
}

void QG_CadToolBarSelect::selectContour() {
    if (actionHandler!=NULL) {
        actionHandler->slotSelectContour();
    }
}

void QG_CadToolBarSelect::deselectAll() {
    if (actionHandler!=NULL) {
        actionHandler->slotDeselectAll();
    }
}

void QG_CadToolBarSelect::selectAll() {
    if (actionHandler!=NULL) {
        actionHandler->slotSelectAll();
    }
}

void QG_CadToolBarSelect::selectWindow() {
    if (actionHandler!=NULL) {
        actionHandler->slotSelectWindow();
    }
}

void QG_CadToolBarSelect::deselectWindow() {
    if (actionHandler!=NULL) {
        actionHandler->slotDeselectWindow();
    }
}

void QG_CadToolBarSelect::selectIntersected() {
    if (actionHandler!=NULL) {
        actionHandler->slotSelectIntersected();
    }
}

void QG_CadToolBarSelect::deselectIntersected() {
    if (actionHandler!=NULL) {
        actionHandler->slotDeselectIntersected();
    }
}

void QG_CadToolBarSelect::selectInvert() {
    if (actionHandler!=NULL) {
        actionHandler->slotSelectInvert();
    }
}

void QG_CadToolBarSelect::selectLayer() {
    if (actionHandler!=NULL) {
        actionHandler->slotSelectLayer();
    }
}

void QG_CadToolBarSelect::setSelectAction(RS_ActionInterface* selectAction) {
    this->selectAction = selectAction;
}

void QG_CadToolBarSelect::setNextAction(int nextAction) {
    this->nextAction = nextAction;
    if (nextAction==-1) {
        bDoit->hide();
    } else {
        bDoit->show();
    }
}

void QG_CadToolBarSelect::runNextAction() {
    if (selectAction!=NULL) {
        selectAction->finish();
        selectAction = NULL;
    }
    if (nextAction!=-1) {
        actionHandler->killSelectActions();
    	actionHandler->setCurrentAction((RS2::ActionType)nextAction);
    }
}

void QG_CadToolBarSelect::back() {
    if (cadToolBar!=NULL) {
        cadToolBar->back();
    }
}
