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
#ifndef QG_COORDINATEWIDGET_H
#define QG_COORDINATEWIDGET_H

#include "intermediate/ui/ui_qg_coordinatewidget.h"

class QG_CoordinateWidget : public QWidget, public Ui::QG_CoordinateWidget
{
    Q_OBJECT

public:
    QG_CoordinateWidget(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = 0);
    ~QG_CoordinateWidget();

public slots:
    virtual void init();
    virtual void setGraphic( RS_Graphic * graphic );
    virtual void setCoordinates( const RS_Vector & abs, const RS_Vector & rel, bool updateFormat );
    virtual void setCoordinates( double x, double y, double rx, double ry, bool updateFormat );

protected slots:
    virtual void languageChange();

private:
    RS_Graphic* graphic;
    int prec;
    RS2::LinearFormat format;
    int aprec;
    RS2::AngleFormat aformat;

};

#endif // QG_COORDINATEWIDGET_H
