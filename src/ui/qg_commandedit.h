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

#ifndef QG_COMMANDEDIT_H
#define QG_COMMANDEDIT_H

#include <qlineedit.h>
#include <qstringlist.h>
//Added by qt3to4:
#include <QFocusEvent>
#include <QEvent>
#include <QKeyEvent>

/**
 * A command line edit with some typical console features 
 * (uparrow for the history, tab, ..).
 */
class QG_CommandEdit: public QLineEdit {
    Q_OBJECT

public:
    QG_CommandEdit(QWidget* parent=0, const char* name=0);
    virtual ~QG_CommandEdit();

protected:
	virtual bool event(QEvent* e);
	virtual void keyPressEvent(QKeyEvent* e);
	virtual void focusInEvent(QFocusEvent *e);
	virtual void focusOutEvent(QFocusEvent *e);

signals:
	void tabPressed();
	void escape();
	void focusIn();
	void focusOut();

private:
	QStringList historyList;
	QStringList::Iterator it;
	bool acceptCoordinates;
};

#endif

