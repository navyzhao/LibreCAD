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

void QG_BevelOptions::destroy() {
    RS_SETTINGS->beginGroup("/Modify");
    RS_SETTINGS->writeEntry("/BevelLength1", leLength1->text());
    RS_SETTINGS->writeEntry("/BevelLength2", leLength2->text());
    RS_SETTINGS->writeEntry("/BevelTrim", (int)cbTrim->isChecked());
    RS_SETTINGS->endGroup();
}

void QG_BevelOptions::setAction(RS_ActionInterface* a, bool update) {
    if (a!=NULL && a->rtti()==RS2::ActionModifyBevel) {
        action = (RS_ActionModifyBevel*)a;

        QString sd1;
        QString sd2;
		QString st;
        if (update) {
            sd1 = QString("%1").arg(action->getLength1());
            sd2 = QString("%1").arg(action->getLength2());
            st = QString("%1").arg((int)action->isTrimOn());
        } else {
            RS_SETTINGS->beginGroup("/Modify");
            sd1 = RS_SETTINGS->readEntry("/BevelLength1", "1.0");
            sd2 = RS_SETTINGS->readEntry("/BevelLength2", "1.0");
            st = RS_SETTINGS->readEntry("/BevelTrim", "1");
            RS_SETTINGS->endGroup();
        }
		leLength1->setText(sd1);
		leLength2->setText(sd2);
    	cbTrim->setChecked(st=="1");
    } else {
        RS_DEBUG->print(RS_Debug::D_ERROR, 
			"QG_BevelOptions::setAction: wrong action type");
        action = NULL;
    }
}

void QG_BevelOptions::updateData() {
    if (action!=NULL) {
        action->setTrim(cbTrim->isChecked());
        action->setLength1(RS_Math::eval(leLength1->text()));
        action->setLength2(RS_Math::eval(leLength2->text()));
    }
}
