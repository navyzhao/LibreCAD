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

void QG_DlgInsert::setInsert(RS_Insert& i) {
    insert = &i;
    //pen = insert->getPen();
    wPen->setPen(insert->getPen(false), true, false, "Pen");
    RS_Graphic* graphic = insert->getGraphic();
    if (graphic!=NULL) {
        cbLayer->init(*(graphic->getLayerList()), false, false);
    }
    RS_Layer* lay = insert->getLayer(false);
    if (lay!=NULL) {
        cbLayer->setLayer(*lay);
    }
    QString s;
    s.setNum(insert->getInsertionPoint().x);
    leInsertionPointX->setText(s);
    s.setNum(insert->getInsertionPoint().y);
    leInsertionPointY->setText(s);
    s.setNum(insert->getScale().x);
    leScale->setText(s);
    s.setNum(RS_Math::rad2deg(insert->getAngle()));
    leAngle->setText(s);
    s.setNum(insert->getRows());
    leRows->setText(s);
    s.setNum(insert->getCols());
    leCols->setText(s);
    s.setNum(insert->getSpacing().x);
    leRowSpacing->setText(s);
    s.setNum(insert->getSpacing().y);
    leColSpacing->setText(s);
}

void QG_DlgInsert::updateInsert() {
    insert->setInsertionPoint(RS_Vector(RS_Math::eval(leInsertionPointX->text()),
                                  RS_Math::eval(leInsertionPointY->text())));
    insert->setScale(RS_Vector(RS_Math::eval(leScale->text()), 
                                RS_Math::eval(leScale->text())));
    insert->setAngle(RS_Math::deg2rad(RS_Math::eval(leAngle->text())));
    insert->setRows(RS_Math::round(RS_Math::eval(leRows->text())));
    insert->setCols(RS_Math::round(RS_Math::eval(leCols->text())));
    insert->setSpacing(RS_Vector(RS_Math::eval(leRowSpacing->text()),
                                 RS_Math::eval(leColSpacing->text())));
    insert->setPen(wPen->getPen());
    insert->setLayer(cbLayer->currentText());
}

