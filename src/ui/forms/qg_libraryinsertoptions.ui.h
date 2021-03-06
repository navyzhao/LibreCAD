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

void QG_LibraryInsertOptions::destroy() {
    RS_SETTINGS->beginGroup("/LibraryInsert");
    RS_SETTINGS->writeEntry("/LibraryInsertAngle", leAngle->text());
    RS_SETTINGS->writeEntry("/LibraryInsertFactor", leFactor->text());
    RS_SETTINGS->endGroup();
}

void QG_LibraryInsertOptions::setAction(RS_ActionInterface* a, bool update) {
    if (a!=NULL && a->rtti()==RS2::ActionLibraryInsert) {
        action = (RS_ActionLibraryInsert*)a;

        QString sAngle;
        QString sFactor;
        if (update) {
            sAngle = QString("%1").arg(RS_Math::rad2deg(action->getAngle()));
            sFactor = QString("%1").arg(action->getFactor());
        } else {
            RS_SETTINGS->beginGroup("/LibraryInsert");
            sAngle = RS_SETTINGS->readEntry("/LibraryInsertAngle", "0.0");
            sFactor = RS_SETTINGS->readEntry("/LibraryInsertFactor", "1.0");
            RS_SETTINGS->endGroup();
        }
	leAngle->setText(sAngle);
	leFactor->setText(sFactor);
    } else {
        RS_DEBUG->print(RS_Debug::D_ERROR, 
			"QG_LibraryInsertOptions::setAction: wrong action type");
        action = NULL;
    }
}

void QG_LibraryInsertOptions::updateData() {
    if (action!=NULL) {
        action->setAngle(RS_Math::deg2rad(RS_Math::eval(leAngle->text())));
        action->setFactor(RS_Math::eval(leFactor->text()));
    }
}
