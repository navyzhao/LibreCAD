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

#ifndef RS_ACTIONDRAWLINEPARALLEL_H
#define RS_ACTIONDRAWLINEPARALLEL_H

#include "rs_previewactioninterface.h"


/**
 * This action class can handle user events to draw parallel 
 * lines, arcs and circles.
 *
 * @author Andrew Mustun
 */
class RS_ActionDrawLineParallel : public RS_PreviewActionInterface {
	Q_OBJECT
private:
    enum Status {
        SetEntity,    /**< Choose original entity. */
		//SetDistance,  /**< Setting distance in the command line. */
		SetNumber     /**< Setting number in the command line. */
		//SetThrough     /**< Setting a point for the parallel to go through. */
	};
	
public:
    RS_ActionDrawLineParallel(RS_EntityContainer& container,
                              RS_GraphicView& graphicView);
    ~RS_ActionDrawLineParallel() {}

	static QAction* createGUIAction(RS2::ActionType type, QObject* /*parent*/);
	
	virtual RS2::ActionType rtti() {
		return RS2::ActionDrawLineParallel;
	}

    virtual void trigger();
	
    virtual void mouseMoveEvent(RS_MouseEvent* e);
    virtual void mouseReleaseEvent(RS_MouseEvent* e);
    virtual void updateMouseButtonHints();
	
    virtual void commandEvent(RS_CommandEvent* e);
	virtual RS_StringList getAvailableCommands();
	
    virtual void hideOptions();
    virtual void showOptions();

    virtual void updateMouseCursor();
    virtual void updateToolBar();

	double getDistance() {
		return distance;
	}

	void setDistance(double d) {
		distance = d;
	}

	int getNumber() {
		return number;
	}

	void setNumber(int n) {
		number = n;
	}

private:
    /** Closest parallel. */
    RS_Entity* parallel;
    /** Data of new line */
    RS_LineData data;
    /** Distance of the parallel. */
    double distance;
	/** Number of parallels. */
	int number;
	/** Coordinate of the mouse. */
	RS_Vector coord;
	/** Original entity. */
	RS_Entity* entity;
	/**
	 * Commands
	 */
	/*
	RS_String cmdDistance;
	RS_String cmdDistance2;
	RS_String cmdDistance3;
	
	RS_String cmdNumber;
	RS_String cmdNumber2;
	RS_String cmdNumber3;
	*/
};

#endif
