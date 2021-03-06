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

#include "qc_graphicview.h"


#include "rs_actiondefault.h"
#include "rs_settings.h"

#include "qc_applicationwindow.h"

QC_GraphicView::QC_GraphicView(RS_Document* doc, QWidget* parent)
        :QG_GraphicView(parent, "graphicview") {

    RS_DEBUG->print("QC_GraphicView::QC_GraphicView()..");

    RS_DEBUG->print("  Setting Container..");
    if (doc!=NULL) {
        setContainer(doc);
    }
    RS_DEBUG->print("  container set.");
    setFactorX(4.0);
    setFactorY(4.0);
    setOffset(50, 50);
    setBorders(10, 10, 10, 10);
	
	if (doc!=NULL) {
		setDefaultAction(new RS_ActionDefault(*doc, *this));
	}
}


QC_GraphicView::~QC_GraphicView() {
}

// EOF
