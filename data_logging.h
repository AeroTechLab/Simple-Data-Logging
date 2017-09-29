////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Copyright (c) 2016-2017 Leonardo Consoni <consoni_2519@hotmail.com>       //
//                                                                            //
//  This file is part of Platform Utils.                                      //
//                                                                            //
//  Platform Utils is free software: you can redistribute it and/or modify    //
//  it under the terms of the GNU Lesser General Public License as published  //
//  by the Free Software Foundation, either version 3 of the License, or      //
//  (at your option) any later version.                                       //
//                                                                            //
//  Platform Utils is distributed in the hope that it will be useful,         //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of            //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the              //
//  GNU Lesser General Public License for more details.                       //
//                                                                            //
//  You should have received a copy of the GNU Lesser General Public License  //
//  along with Platform Utils. If not, see <http://www.gnu.org/licenses/>.    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


#ifndef DATA_LOGGING_H
#define DATA_LOGGING_H


#include <stddef.h>

#define LOG_FILE_PATH_MAX_LEN 256

#define DATA_LOG_MAX_PRECISION 15

#define DEBUG_PRINT( formatString, ... ) Log_PrintString( NULL, "%s: " formatString, __func__, __VA_ARGS__ ) 


typedef struct _LogData LogData;
typedef LogData* Log;


Log Log_Init( const char* filePath, size_t dataPrecision );

void Log_End( Log log );

void Log_SetBaseDirectory( const char* directoryPath );

void Log_RegisterValues( Log log, size_t valuesNumber, ... );

void Log_RegisterList( Log log, size_t valuesNumber, double* valuesList );

void Log_PrintString( Log log, const char* formatString, ... );

void Log_EnterNewLine( Log log, double timeStamp );


#endif // DATA_LOGGING_H
