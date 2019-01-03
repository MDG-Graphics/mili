/*
 * $Log: SiloLib_Write_Multimat.c,v $
 * Revision 1.5  2011/05/26 21:43:14  durrenberger1
 * fixed a few errant return values which were still declared as int and standardized the indentation of the code to 3 spaces
 *
 * Revision 1.4  2008/11/14 00:08:52  corey3
 * Continued development of MiliSilo
 *
 * Revision 1.3  2008/09/24 18:36:02  corey3
 * New update of Passit source files
 *
 * Revision 1.2  2007/07/05 22:03:50  corey3
 * Adding more functionality to Silo Library Interface
 *
 * Revision 1.1  2007/06/25 17:58:32  corey3
 * New Mili/Silo interface
 *
 *
*/


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                                                              */
/*                   Copyright (c) 2007                         */
/*         The Regents of the University of California          */
/*                     All Rights Reserved                      */
/*                                                              */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/****************************************************************/
/*  Revision History                                            */
/*  ----------------                                            */
/*                                                              */
/*  20-Apr-2007 IRC  Initial version.                           */
/*                                                              */
/****************************************************************/

/*  Include Files  */
#include "silo.h"
#include "SiloLib_Internal.h"

int SiloLIB_Write_Multimat (int    famid,
                            int    filetype,
                            char   *name,
                            int    nmat,
                            char   **matnames,
                            int    nmatnos,
                            int    *matnos,
                            int    cycle,
                            double time
                           )

/****************************************************************/
/*  Routine SiloLib_Write_Multimat writes a multi-block mat     */
/*  object to a Silo file                                       */
/****************************************************************/
/****************************************************************/
/*  Revision History                                            */
/*  ----------------                                            */
/*                                                              */
/*  07-Jun-2007  IRC  Initial version.                          */
/****************************************************************/
{
   DBfile    *db=NULL;
   DBoptlist *optlist;
   int status=OK;
   char *mrgname = "mrg_tree";

   db = SiloLIB_getDBid(famid, filetype);

   /* Make the mesh option list */
   optlist = DBMakeOptlist(16) ;

   DBAddOption(optlist, DBOPT_CYCLE,        (void *)&cycle) ;
   DBAddOption(optlist, DBOPT_DTIME,        (void *)&time) ;
   DBAddOption(optlist, DBOPT_NMATNOS,      (void *)&nmatnos) ;
   DBAddOption(optlist, DBOPT_MATNOS,       (void *)matnos) ;
   DBAddOption(optlist, DBOPT_MRGTREE_NAME, mrgname);

   if (db != NULL)
   {
      status = DBPutMultimat(db,
                             name,
                             nmat,
                             matnames,
                             optlist
                            );
   }

   DBFreeOptlist(optlist);
   return (status);
}

/* End SiloLIB_Write_Multimat.c */
