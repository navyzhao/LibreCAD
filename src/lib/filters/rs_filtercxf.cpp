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


#include "rs_filtercxf.h"

#include <iostream>
#include <fstream>

#include "rs_regexp.h"
#include "rs_font.h"
#include "rs_utility.h"
#include "rs_system.h"


/**
 * Default constructor.
 */
RS_FilterCXF::RS_FilterCXF() : RS_FilterInterface() {

    RS_DEBUG->print("Setting up CXF filter...");

    addImportFormat(RS2::FormatCXF);
    addExportFormat(RS2::FormatCXF);
}



/**
 * Implementation of the method used for RS_Import to communicate
 * with this filter.
 *
 * @param g The graphic in which the entities from the file
 * will be created or the graphics from which the entities are
 * taken to be stored in a file.
 */
bool RS_FilterCXF::fileImport(RS_Graphic& g, const RS_String& file, RS2::FormatType /*type*/) {
    RS_DEBUG->print("CXF Filter: importing file '%s'...", file.latin1());

    //this->graphic = &g;
    bool success = false;

    // Load font file as we normally do, but the font doesn't own the
    //  letters (we'll add them to the graphic instead. Hence 'false').
    RS_Font font(file, false);
    success = font.loadFont();

    if (success==false) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "Cannot open CXF file '%s'.", file.latin1());
		return false;
    }

    g.addVariable("Names",
                         font.getNames().join(","), 0);
    g.addVariable("LetterSpacing", font.getLetterSpacing(), 0);
    g.addVariable("WordSpacing", font.getWordSpacing(), 0);
    g.addVariable("LineSpacingFactor", font.getLineSpacingFactor(), 0);
    g.addVariable("Authors", font.getAuthors().join(","), 0);
    if (!font.getEncoding().isEmpty()) {
        g.addVariable("Encoding", font.getEncoding(), 0);
    }

    RS_BlockList* letterList = font.getLetterList();
    for (uint i=0; i<font.countLetters(); ++i) {
        RS_Block* ch = font.letterAt(i);

        RS_String uCode;
        uCode.setNum(ch->getName().at(0).unicode(), 16);
        while (uCode.length()<4) {
            uCode="0"+uCode;
        }
        //ch->setName("[" + uCode + "] " + ch->getName());
        //letterList->rename(ch, RS_String("[%1]").arg(ch->getName()));
        letterList->rename(ch,
                           RS_String("[%1] %2").arg(uCode).arg(ch->getName().at(0)));

        g.addBlock(ch, false);
        ch->reparent(&g);
    }

    g.addBlockNotification();

	return true;
}



/**
 * Implementation of the method used for RS_Export to communicate
 * with this filter.
 *
 * @param file Full path to the CXF file that will be written.
 */
bool RS_FilterCXF::fileExport(RS_Graphic& g, const RS_String& file, RS2::FormatType /*type*/) {

    RS_DEBUG->print("CXF Filter: exporting file '%s'...", file.latin1());

    // crashes under windoze xp:
    //std::ofstream fout;

    RS_DEBUG->print("RS_FilterCXF::fileExport: open");
    //fout.open((const char*)file.local8Bit());
    FILE* fp;

    if ((fp = fopen((const char*)file.local8Bit(), "wt")) != NULL) {

        RS_DEBUG->print("RS_FilterCXF::fileExport: open: OK");

        RS_DEBUG->print("RS_FilterCXF::fileExport: header");

        // header:
        fprintf(fp, "# Format:            QCad II Font\n");

        fprintf(fp, "# Creator:           %s\n",
                (const char*)RS_SYSTEM->getAppName().local8Bit());
        fprintf(fp, "# Version:           %s\n",
                (const char*)RS_SYSTEM->getAppVersion().local8Bit());

        RS_DEBUG->print("001");
        RS_String ns = g.getVariableString("Names", "");
        if (!ns.isEmpty()) {
            RS_StringList names = RS_StringList::split(',', ns);
            RS_DEBUG->print("002");
            for (RS_StringList::Iterator it = names.begin(); it!=names.end(); ++it) {
                fprintf(fp, "# Name:              %s\n",
                        (const char*)((*it).local8Bit()));
            }
        }

        RS_DEBUG->print("003");

        RS_String es = g.getVariableString("Encoding", "");
        if (!es.isEmpty()) {
            fprintf(fp, "# Encoding:          %s\n",
                    (const char*)es.local8Bit());
        }

        RS_DEBUG->print("004a");

        fprintf(fp, "# LetterSpacing:     %f\n",
                g.getVariableDouble("LetterSpacing", 3.0));
        fprintf(fp, "# WordSpacing:       %f\n",
                g.getVariableDouble("WordSpacing", 6.75));
        fprintf(fp, "# LineSpacingFactor: %f\n",
                g.getVariableDouble("LineSpacingFactor", 1.0));

        RS_String sa = g.getVariableString("Authors", "");
        RS_DEBUG->print("authors: %s", (const char*)sa.local8Bit());
        if (!sa.isEmpty()) {
            RS_StringList authors = RS_StringList::split(',', sa);
            RS_DEBUG->print("006");
            RS_DEBUG->print("count: %d", authors.count());

            RS_String a;
            for (RS_StringList::Iterator it2 = authors.begin();
                    it2!=authors.end(); ++it2) {

                RS_DEBUG->print("006a");
                a = RS_String(*it2);
                RS_DEBUG->print("006b");
                RS_DEBUG->print("string is: %s", a.ascii());
                RS_DEBUG->print("006b0");
                fprintf(fp, "# Author:            ");
                RS_DEBUG->print("006b1");
                fprintf(fp, "%s\n", a.ascii());
                //fout << "# Author:            " << a.ascii() << "\n";
            }
            RS_DEBUG->print("007");
        }

        RS_DEBUG->print("RS_FilterCXF::fileExport: header: OK");

        RS_DEBUG->print("008");
        // iterate through blocks (=letters of font)
        for (uint i=0; i<g.countBlocks(); ++i) {
            RS_Block* blk = g.blockAt(i);

            RS_DEBUG->print("block: %d", i);
            RS_DEBUG->print("001");

            if (blk!=NULL) {
                RS_DEBUG->print("002");
                RS_DEBUG->print("002a: %s",
                                (const char*)(blk->getName().local8Bit()));

                fprintf(fp, "\n%s\n",
                        (const char*)(blk->getName().local8Bit()));


                // iterate through entities of this letter:
                for (RS_Entity* e=blk->firstEntity(RS2::ResolveAll);
                        e!=NULL;
                        e=blk->nextEntity(RS2::ResolveAll)) {

                    if (!e->isUndone()) {

                        RS_DEBUG->print("004");

                        // lines:
                        if (e->rtti()==RS2::EntityLine) {
                            RS_Line* l = (RS_Line*)e;

                            fprintf(fp, "L %f,%f,%f,%f\n",
                                    l->getStartpoint().x,
                                    l->getStartpoint().y,
                                    l->getEndpoint().x,
                                    l->getEndpoint().y);
                        }

                        // arcs:
                        else if (e->rtti()==RS2::EntityArc) {
                            RS_Arc* a = (RS_Arc*)e;

                            if (!a->isReversed()) {
                                fprintf(fp, "A ");
                            } else {
                                fprintf(fp, "AR ");
                            }

                            fprintf(fp, "%f,%f,%f,%f,%f\n",
                                    a->getCenter().x,
                                    a->getCenter().y,
                                    a->getRadius(),
                                    a->getAngle1()*ARAD,
                                    a->getAngle2()*ARAD);
                        }
                        // Ignore entities other than arcs / lines
                        else {}
                    }

                    RS_DEBUG->print("005");
                }
                RS_DEBUG->print("006");
            }
            RS_DEBUG->print("007");
        }
        //fout.close();
        fclose(fp);
    	RS_DEBUG->print("CXF Filter: exporting file: OK");
		return true;
    }
	else {
    	RS_DEBUG->print("CXF Filter: exporting file failed");
	}

	return false;
}



/**
 * Streams a double value to the gien stream cutting away trailing 0's.
 *
 * @param value A double value. e.g. 2.700000
 */
void RS_FilterCXF::stream(std::ofstream& fs, double value) {
    fs << (const char*)RS_Utility::doubleToString(value);
}

