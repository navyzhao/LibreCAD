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

#include "rs_actiondrawtext.h"

#include "rs_snapper.h"
#include "rs_graphicview.h"



RS_ActionDrawText::RS_ActionDrawText(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
        :RS_PreviewActionInterface("Draw Text",
                           container, graphicView) {

    //text = NULL;
    pos = RS_Vector(false);
    textChanged = true;
}


QAction* RS_ActionDrawText::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
	// tr("Text")
    QAction* action = new QAction(tr("&Text"),  NULL);
	action->setIcon(QIcon(":/extui/menutext.png"));
    //action->zetStatusTip(tr("Draw Text Entities"));
    return action;
}


void RS_ActionDrawText::init(int status) {
    RS_ActionInterface::init(status);
    if (RS_DIALOGFACTORY!=NULL) {

        switch (status) {
        case ShowDialog: {
                reset();

                RS_Text tmp(NULL, data);
                if (RS_DIALOGFACTORY->requestTextDialog(&tmp)) {
                    data = tmp.getData();
                    preparePreview();
                    preview->setVisible(false);

                    setStatus(SetPos);
                    showOptions();
                } else {
                    hideOptions();
                    finish();
                }
			// RVT_PORT should we reall redraw here??
			graphicView->redraw(RS2::RedrawDrawing); 

            }
            break;

        case SetPos:
            RS_DIALOGFACTORY->requestOptions(this, true, true);
            break;

        default:
            break;
        }
    }
}



void RS_ActionDrawText::reset() {
    data = RS_TextData(RS_Vector(0.0,0.0),
                       1.0, 100.0,
                       RS2::VAlignTop,
                       RS2::HAlignLeft,
                       RS2::LeftToRight,
                       RS2::Exact,
                       1.0,
                       data.text,
                       "standard",
                       0.0,
                       RS2::Update);
}



void RS_ActionDrawText::trigger() {

    RS_DEBUG->print("RS_ActionDrawText::trigger()");

    if (pos.valid) {
        deletePreview();

        RS_Text* text = new RS_Text(container, data);
        text->update();
        container->addEntity(text);

        if (document) {
            document->startUndoCycle();
            document->addUndoable(text);
            document->endUndoCycle();
        }

		graphicView->redraw(RS2::RedrawDrawing);

        textChanged = true;
        setStatus(SetPos);
    }
}


void RS_ActionDrawText::preparePreview() {
    data.insertionPoint = RS_Vector(0.0,0.0);
    RS_Text* text = new RS_Text(preview, data);
    text->update();
    //text->setVisible(false);
    preview->addEntity(text);
    textChanged = false;
}


void RS_ActionDrawText::mouseMoveEvent(RS_MouseEvent* e) {
    RS_DEBUG->print("RS_ActionDrawText::mouseMoveEvent begin");

    if (getStatus()==SetPos) {
        RS_Vector mouse = snapPoint(e);
        pos = mouse;

        deletePreview();
        if (textChanged) {
            preparePreview();
        }
        if (!preview->isVisible()) {
            preview->setVisible(true);
        }
        offset = RS_Vector(graphicView->toGuiDX(pos.x),
                           -graphicView->toGuiDY(pos.y));
        drawPreview();
    }

    RS_DEBUG->print("RS_ActionDrawText::mouseMoveEvent end");
}



void RS_ActionDrawText::mouseReleaseEvent(RS_MouseEvent* e) {
    if (RS2::qtToRsButtonState(e->button())==RS2::LeftButton) {
        RS_CoordinateEvent ce(snapPoint(e));
        coordinateEvent(&ce);
    } else if (RS2::qtToRsButtonState(e->button())==RS2::RightButton) {
        deletePreview();
        //init(getStatus()-1);
        finish();
    }
}



void RS_ActionDrawText::coordinateEvent(RS_CoordinateEvent* e) {
    if (e==NULL) {
        return;
    }

    RS_Vector mouse = e->getCoordinate();

    switch (getStatus()) {
    case ShowDialog:
        break;

    case SetPos:
        data.insertionPoint = mouse;
        trigger();
        break;

    default:
        break;
    }
}



void RS_ActionDrawText::commandEvent(RS_CommandEvent* e) {
    RS_String c = e->getCommand().lower();

    if (checkCommand("help", c)) {
        if (RS_DIALOGFACTORY!=NULL) {
            RS_DIALOGFACTORY->commandMessage(msgAvailableCommands()
                                             + getAvailableCommands().join(", "));
        }
        return;
    }

    switch (getStatus()) {
    case SetPos:
        if (checkCommand("text", c)) {
            deletePreview();
            graphicView->disableCoordinateInput();
            setStatus(SetText);
        }
        break;

    case SetText: {
            setText(e->getCommand());
            if (RS_DIALOGFACTORY!=NULL) {
                RS_DIALOGFACTORY->requestOptions(this, true, true);
            }
            graphicView->enableCoordinateInput();
            setStatus(SetPos);
        }
        break;

    default:
        break;
    }
}



RS_StringList RS_ActionDrawText::getAvailableCommands() {
    RS_StringList cmd;
    if (getStatus()==SetPos) {
        cmd += command("text");
    }
    return cmd;
}



void RS_ActionDrawText::showOptions() {
    RS_ActionInterface::showOptions();

    if (RS_DIALOGFACTORY!=NULL) {
        RS_DIALOGFACTORY->requestOptions(this, true, true);
    }
}



void RS_ActionDrawText::hideOptions() {
    RS_ActionInterface::hideOptions();

    if (RS_DIALOGFACTORY!=NULL) {
        RS_DIALOGFACTORY->requestOptions(this, false);
    }
}



void RS_ActionDrawText::updateMouseButtonHints() {
    if (RS_DIALOGFACTORY!=NULL) {
        switch (getStatus()) {
        case SetPos:
            RS_DIALOGFACTORY->updateMouseWidget(tr("Specify insertion point"),
                                                tr("Cancel"));
            break;
        case SetText:
            RS_DIALOGFACTORY->updateMouseWidget(tr("Enter text:"),
                                                tr("Back"));
            break;
        default:
            RS_DIALOGFACTORY->updateMouseWidget("", "");
            break;
        }
    }
}



void RS_ActionDrawText::updateMouseCursor() {
    graphicView->setMouseCursor(RS2::CadCursor);
}



void RS_ActionDrawText::updateToolBar() {
    if (RS_DIALOGFACTORY!=NULL) {
        switch (getStatus()) {
        case SetPos:
            RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarSnap);
            break;
        default:
            RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarMain);
            break;
        }
    }
}



void RS_ActionDrawText::setText(const RS_String& t) {
    data.text = t;
    textChanged = true;
}



RS_String RS_ActionDrawText::getText() {
    return data.text;
}


void RS_ActionDrawText::setAngle(double a) {
    data.angle = a;
    textChanged = true;
}

double RS_ActionDrawText::getAngle() {
    return data.angle;
}


// EOF
