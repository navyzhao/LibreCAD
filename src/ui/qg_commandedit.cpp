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

#include "qg_commandedit.h"
//Added by qt3to4:
#include <QFocusEvent>
#include <QKeyEvent>
#include <QEvent>


#include "rs_debug.h"


/**
 * Default Constructor. You must call init manually if you choose
 * to use this constructor.
 */
QG_CommandEdit::QG_CommandEdit(QWidget* parent, const char* name)
        : QLineEdit(parent, name) {}



/**
 * Destructor
 */
QG_CommandEdit::~QG_CommandEdit() {
}


/**
 * Bypass for key press events from the tab key.
 */
bool QG_CommandEdit::event(QEvent* e) {
	if (e->type()==QEvent::KeyPress) {
		QKeyEvent* k = (QKeyEvent*)e;
		if (k->key()==Qt::Key_Tab) {
			emit tabPressed();
			return true;
		}
	}
	
	return QLineEdit::event(e);
}



/**
 * History (arrow key up/down) support, tab.
 */
void QG_CommandEdit::keyPressEvent(QKeyEvent* e) {

	switch (e->key()) {
            case Qt::Key_Up:
                    if (!historyList.isEmpty() && it>historyList.begin()) {
                            it--;
                            setText(*it);
                    }
                    break;

            case Qt::Key_Down:
                    if (!historyList.isEmpty() && it<historyList.end() ) {
                            it++;
                            if (it<historyList.end()) {
                                    setText(*it);
                            }
                            else {
                                    setText("");
                            }
                    }
                    break;

            case Qt::Key_Return:
                    historyList.append(text());
                    it = historyList.end();
                    QLineEdit::keyPressEvent(e);
                    break;

            case Qt::Key_Escape:
                    if (text().isEmpty()) {
                            emit escape();
                    }
                    else {
                            setText("");
                    }
                    break;

            default:
                    QLineEdit::keyPressEvent(e);
                    break;
	}
}


void QG_CommandEdit::focusInEvent(QFocusEvent *e) {
	emit focusIn();
	QLineEdit::focusInEvent(e);
}


void QG_CommandEdit::focusOutEvent(QFocusEvent *e) {
	emit focusOut();
	QLineEdit::focusOutEvent(e);
}


