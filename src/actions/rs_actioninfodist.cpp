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

#include "rs_actioninfodist.h"

#include "rs_snapper.h"



RS_ActionInfoDist::RS_ActionInfoDist(RS_EntityContainer& container,
                                     RS_GraphicView& graphicView)
        :RS_PreviewActionInterface("Info Dist",
                           container, graphicView) {}


QAction* RS_ActionInfoDist::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
	// tr("Distance Point to Point")
	QAction* action = new QAction(tr("&Distance Point to Point"), NULL);
	//action->zetStatusTip(tr("Measures the distance between two points"));
	action->setIcon(QIcon(":/extui/restricthorizontal.png"));
	return action;
}


void RS_ActionInfoDist::init(int status) {
    RS_ActionInterface::init(status);

}



void RS_ActionInfoDist::trigger() {

    RS_DEBUG->print("RS_ActionInfoDist::trigger()");

    if (point1.valid && point2.valid) {
        double dist = point1.distanceTo(point2);
        QString str;
        str.sprintf("%.6f", dist);
        RS_DIALOGFACTORY->commandMessage(tr("Distance: %1").arg(str));
    }
}



void RS_ActionInfoDist::mouseMoveEvent(RS_MouseEvent* e) {
    RS_DEBUG->print("RS_ActionInfoDist::mouseMoveEvent begin");

    if (getStatus()==SetPoint1 ||
            getStatus()==SetPoint2) {

        RS_Vector mouse = snapPoint(e);
        switch (getStatus()) {
        case SetPoint1:
            break;

        case SetPoint2:
            if (point1.valid) {
                point2 = mouse;

                deletePreview();

                preview->addEntity(new RS_Line(preview,
                                               RS_LineData(point1,
                                                           point2)));

                drawPreview();
            }
            break;

        default:
            break;
        }
    }

    RS_DEBUG->print("RS_ActionInfoDist::mouseMoveEvent end");
}



void RS_ActionInfoDist::mouseReleaseEvent(RS_MouseEvent* e) {
    if (RS2::qtToRsButtonState(e->button())==RS2::LeftButton) {
        RS_CoordinateEvent ce(snapPoint(e));
        coordinateEvent(&ce);
    } else if (RS2::qtToRsButtonState(e->button())==RS2::RightButton) {
        deletePreview();
        init(getStatus()-1);
    }
}



void RS_ActionInfoDist::coordinateEvent(RS_CoordinateEvent* e) {
    if (e==NULL) {
        return;
    }

    RS_Vector mouse = e->getCoordinate();

    switch (getStatus()) {
    case SetPoint1:
        point1 = mouse;
    	graphicView->moveRelativeZero(point1);
        setStatus(SetPoint2);
        break;

    case SetPoint2:
        if (point1.valid) {
            point2 = mouse;
            deletePreview();
    		graphicView->moveRelativeZero(point2);
            trigger();
            setStatus(SetPoint1);
        }
        break;

    default:
        break;
    }
}


void RS_ActionInfoDist::updateMouseButtonHints() {
    switch (getStatus()) {
    case SetPoint1:
        RS_DIALOGFACTORY->updateMouseWidget(
            tr("Specify first point of distance"),
            tr("Cancel"));
        break;
    case SetPoint2:
        RS_DIALOGFACTORY->updateMouseWidget(
            tr("Specify second point of distance"),
            tr("Back"));
        break;
    default:
        RS_DIALOGFACTORY->updateMouseWidget("", "");
        break;
    }
}



void RS_ActionInfoDist::updateMouseCursor() {
    graphicView->setMouseCursor(RS2::CadCursor);
}



void RS_ActionInfoDist::updateToolBar() {
    switch (getStatus()) {
    case SetPoint1:
    case SetPoint2:
        RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarSnap);
        break;
    default:
        RS_DIALOGFACTORY->requestToolBar(RS2::ToolBarInfo);
        break;
    }
}


// EOF
