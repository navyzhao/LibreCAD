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

#ifndef RS_SCRIPTLIST_H
#define RS_SCRIPTLIST_H


#include "rs_script.h"
#include "rs_ptrlist.h"

#define RS_SCRIPTLIST RS_ScriptList::instance()

/**
 * The global list of scripts. This is implemented as a singleton.
 * Use RS_ScriptList::instance() to get a pointer to the object.
 *
 * OBSOLETE
 *
 * @author Andrew Mustun
 */
class RS_ScriptList {
protected:
    RS_ScriptList();

public:
    /**
     * @return Instance to the unique script list.
     */
    static RS_ScriptList* instance() {
        if (uniqueInstance==NULL) {
            uniqueInstance = new RS_ScriptList();
        }
        return uniqueInstance;
    }

    virtual ~RS_ScriptList() {}

    void init();

    void clearScripts();
    int countScripts() {
        return scripts.count();
    }
    //void activateScript(const RS_String& name);
    //void activateScript(RS_Script* script);
    ////! @return The active script of NULL if no script is activated.
    //RS_Script* getActiveScript() { return activeScript; }
    //virtual void addScript(RS_Script* script);
    virtual void removeScript(RS_Script* script);
    //virtual void editScript(RS_Script* script, const RS_Script& source);
    RS_Script* requestScript(const RS_String& name);
    //RS_Script* loadScript(const RS_String& name);
    //void toggleScript(const RS_String& name);
    //! @return First script of the list.
    RS_Script* firstScript() {
        return scripts.first();
    }
    /** @return Next script from the list after
     * calling firstScript() or nextScript().
     */
    RS_Script* nextScript() {
        return scripts.next();
    }

    //void addScriptListListener(RS_ScriptListListener* listener);

    static bool test();

protected:
    static RS_ScriptList* uniqueInstance;

private:
    //! all scripts available
    RS_PtrList<RS_Script> scripts;
    //! List of registered ScriptListListeners
    //RS_PtrList<RS_ScriptListListener> scriptListListeners;
    //! Currently active script
    //RS_Script* activeScript;
}
;

#endif
