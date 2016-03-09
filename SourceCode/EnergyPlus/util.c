// Methods for Functional Mock-up Unit Export of EnergyPlus.

///////////////////////////////////////////////////////
/// \file   util.c
///
/// \brief  utility functions
///
/// \author Wangda Zuo, Thierry S. Nouidui, Michael Wetter
///         Simulation Research Group,
///         LBNL,
///         WZuo@lbl.gov
///
/// \date   2011-11-02
///
///
/// This file provides utility functions for fmus
///
/// Copyright (c) 2012, The Regents of the University of California, 
/// through Lawrence Berkeley National Laboratory 
/// subject to receipt of any required approvals from the U.S. Dept. of Energy.
/// All rights reserved.
///////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "util.h"

int debug;  // Control for debug information

///////////////////////////////////////////////////////////////////////////////
/// Translate the double variable to string variable.
///
///\param buffer String variable.
///\param r Double variable.
///////////////////////////////////////////////////////////////////////////////
void doubleToCommaString(char* buffer, double r){
    char* comma;
    sprintf(buffer, "%.16g", r);
    comma = strchr(buffer, '.');
    if (comma) *comma = ',';
}

//////////////////////////////////////////////////////////////////////////
/// Delete the temporary folder
///
///\param tmpPat The path of the temporary folder
///\return 0 if no error occurred
/////////////////////////////////////////////////////////////////////////
int deleteTmpDir(char* tmpPat){
	char* cmd;
  struct stat st;

  // Ceck if the folder present
  if(stat(tmpPat,&st) != 0){
    printfError("Folder \"%s\" is not existing.\n", tmpPat);
    return -1;
  }    

	cmd = (char *)calloc(sizeof(char), strlen(tmpPat) +18);
	if (cmd == NULL){
	    printfError("Fail to allocate memory for cmd.\n", tmpPat);
	    return -1;
	  }
  
  if (WINDOWS)
  	sprintf(cmd, "rd %s /S/Q", tmpPat); // Command in windows
  else
  	sprintf(cmd, "rm -r %s", tmpPat); // Command in Linux


	printfDebug("Generated cmd: \"%s\".\n", cmd);
	if ( system(cmd) != 0 ){	
	  printError("Fail to delete the temporary files");
	  return -1;
	}
	printDebug("Deleted temporary files");
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
/// Get temporary path
///
///\param nam Name to be used for temporary path
///\param length Number of characters to be copied from \c nam.
///\return Point of tmpPat if there is no error occurred.
/////////////////////////////////////////////////////////////////////////////
char *getTmpPath(const char *nam, int length)
{
  char *tmpPat;

  tmpPat = (char *)calloc(sizeof(char), length+2);
  
  // Define the temporary folder
  if(strncpy(tmpPat, nam, length) == NULL){
    printError("Fail to allocate memory for temp dir.\n");
    return NULL;    
  }
  if(WINDOWS) strcat(tmpPat, "\\");
  else strcat(tmpPat, "/");

  return tmpPat;
}



//////////////////////////////////////////////////////////////////////////////
/// Set the mode in debug so that the debug information will be printed
///
//////////////////////////////////////////////////////////////////////////////
void setDebug(int value)
{
  debug = 1;
}

//////////////////////////////////////////////////////////////////////////////
/// Print debug message
///
///\param msg Message to be printed for debugging 
//////////////////////////////////////////////////////////////////////////////
void printDebug(const char* msg){
  if (debug == 1)
  {
	  fprintf(stdout, "Debug: ");
	  fprintf(stdout, "%s\n", msg);
  }
}

////////////////////////////////////////////////////////////////////////////////
///// Print formatted debug message
/////
/////\param str1 Message to be printed for debugging 
/////\param str2 String variable to be printed for debugging
////////////////////////////////////////////////////////////////////////////////
//void printfDebug(const char* str1, const char* str2){
//	if (debug == 1)
//	{
//		fprintf(stdout, "Debug: ");
//		fprintf(stdout, str1, str2);
//	}
//}

//////////////////////////////////////////////////////////////////////////////
/// Print formatted debug message with Integer
///
///\param str1 Message to be printed for debugging 
///\param integer Integer variable to be printed for debugging
//////////////////////////////////////////////////////////////////////////////
void printfIntDebug(const char* str1, const int integer){
	if (debug == 1)
	{
		fprintf(stdout, "Debug: ");
		fprintf(stdout, str1, integer);
	}
}

//////////////////////////////////////////////////////////////////////////////
/// Print error message
///
///\param msg Error message to be printed
//////////////////////////////////////////////////////////////////////////////
void printError(const char* msg){
  fprintf(stderr, "*** Error: ");
  fprintf(stderr, "%s\n", msg);
}

//////////////////////////////////////////////////////////////////////////////
/// Print formatted error message
///
///\param str1 Error message to be printed
///\param str2 String variable to be printed
//////////////////////////////////////////////////////////////////////////////
void printfError(const char* str1, const char* str2){
  fprintf(stderr, "*** Error: ");
  fprintf(stderr, str1, str2);
}

/*

***********************************************************************************
Copyright Notice
----------------

Functional Mock-up Unit Export of EnergyPlus �2013, The Regents of 
the University of California, through Lawrence Berkeley National 
Laboratory (subject to receipt of any required approvals from 
the U.S. Department of Energy). All rights reserved.
 
If you have questions about your rights to use or distribute this software, 
please contact Berkeley Lab's Technology Transfer Department at 
TTD@lbl.gov.referring to "Functional Mock-up Unit Export 
of EnergyPlus (LBNL Ref 2013-088)".
 
NOTICE: This software was produced by The Regents of the 
University of California under Contract No. DE-AC02-05CH11231 
with the Department of Energy.
For 5 years from November 1, 2012, the Government is granted for itself
and others acting on its behalf a nonexclusive, paid-up, irrevocable 
worldwide license in this data to reproduce, prepare derivative works,
and perform publicly and display publicly, by or on behalf of the Government.
There is provision for the possible extension of the term of this license. 
Subsequent to that period or any extension granted, the Government is granted
for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable 
worldwide license in this data to reproduce, prepare derivative works, 
distribute copies to the public, perform publicly and display publicly, 
and to permit others to do so. The specific term of the license can be identified 
by inquiry made to Lawrence Berkeley National Laboratory or DOE. Neither 
the United States nor the United States Department of Energy, nor any of their employees, 
makes any warranty, express or implied, or assumes any legal liability or responsibility
for the accuracy, completeness, or usefulness of any data, apparatus, product, 
or process disclosed, or represents that its use would not infringe privately owned rights.
 
 
Copyright (c) 2013, The Regents of the University of California, Department
of Energy contract-operators of the Lawrence Berkeley National Laboratory.
All rights reserved.
 
1. Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:
 
(1) Redistributions of source code must retain the copyright notice, this list 
of conditions and the following disclaimer.
 
(2) Redistributions in binary form must reproduce the copyright notice, this list
of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.
 
(3) Neither the name of the University of California, Lawrence Berkeley 
National Laboratory, U.S. Dept. of Energy nor the names of its contributors 
may be used to endorse or promote products derived from this software without 
specific prior written permission.
 
2. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.
 
3. You are under no obligation whatsoever to provide any bug fixes, patches, 
or upgrades to the features, functionality or performance of the source code
("Enhancements") to anyone; however, if you choose to make your Enhancements
available either publicly, or directly to Lawrence Berkeley National Laboratory, 
without imposing a separate written license agreement for such Enhancements, 
then you hereby grant the following license: a non-exclusive, royalty-free 
perpetual license to install, use, modify, prepare derivative works, incorporate
into other computer software, distribute, and sublicense such enhancements or 
derivative works thereof, in binary and source code form.
 
NOTE: This license corresponds to the "revised BSD" or "3-clause BSD" 
License and includes the following modification: Paragraph 3. has been added.


***********************************************************************************
*/
