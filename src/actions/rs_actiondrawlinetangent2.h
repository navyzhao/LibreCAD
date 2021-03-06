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

#ifndef RS_ACTIONDRAWLINETANGENT2_H
#define RS_ACTIONDRAWLINETANGENT2_H

#include "rs_previewactioninterface.h"


/**
 * This action class can handle user events to draw tangents from circle to
 * circle.
 *
 * @author Andrew Mustun
 */
class RS_ActionDrawLineTangent2 : public RS_PreviewActionInterface {
	Q_OBJECT
private:
    enum Status {
        SetCircle1,     /**< Choose the startpoint. */
        SetCircle2      /**< Choose the circle / arc. */
    };

public:
    RS_ActionDrawLineTangent2(RS_EntityContainer& container,
                              RS_GraphicView& graphicView);
    ~RS_ActionDrawLineTangent2() {}

	static QAction* createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/);

    virtual void trigger();
    virtual void mouseMoveEvent(RS_MouseEvent* e);
    virtual void mouseReleaseEvent(RS_MouseEvent* e);
    virtual void updateMouseButtonHints();
    //virtual void hideOptions();
    //virtual void showOptions();
    virtual void updateMouseCursor();
    virtual void updateToolBar();

private:
    /** Closest tangent. */
    RS_Line* tangent;
    /** 1st chosen entity */
    RS_Entity* circle1;
    /** 2nd chosen entity */
    RS_Entity* circle2;
    /** Data of new tangent */
    RS_LineData data;
};

#endif
