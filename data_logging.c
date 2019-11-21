//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
//  Copyright (c) 2016-2019 Leonardo Consoni <leonardojc@protonmail.com>        //
//                                                                              //
//  This file is part of Simple Data Logging.                                   //
//                                                                              //
//  Simple Data Logging is free software: you can redistribute it and/or modify //
//  it under the terms of the GNU Lesser General Public License as published    //
//  by the Free Software Foundation, either version 3 of the License, or        //
//  (at your option) any later version.                                         //
//                                                                              //
//  Simple Data Logging is distributed in the hope that it will be useful,      //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of              //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                //
//  GNU Lesser General Public License for more details.                         //
//                                                                              //
//  You should have received a copy of the GNU Lesser General Public License    //
//  along with Simple Data Logging. If not, see <http://www.gnu.org/licenses/>. //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////


#include "data_logging.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
  #include <windows.h>
  #define GET_FULL_PATH( relativePath, fullPathBuffer ) GetFullPathName( relativePath, MAX_PATH, fullPathBuffer, NULL )
  #define MAKE_DIRECTORY( directoryPath ) CreateDirectory( directoryPath, NULL )
#else
  #include <limits.h>
  #include <stdlib.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #define GET_FULL_PATH( relativePath, fullPathBuffer ) realpath( relativePath, fullPathBuffer )
  #define MAKE_DIRECTORY( directoryPath ) mkdir( directoryPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH )
#endif

#define DATE_TIME_STRING_LENGTH 32

#ifdef _CVI_
  #define TERMINAL_OUTPUT (FILE*) stderr
#else
  #define TERMINAL_OUTPUT (FILE*) stdout
#endif

struct _LogData
{
  FILE* file;
  int dataPrecision;
};

static char rootDirectoryPath[ LOG_FILE_PATH_MAX_LENGTH ] = "";
static char baseFileName[ LOG_FILE_PATH_MAX_LENGTH ] = "";
static char timeStampString[ DATE_TIME_STRING_LENGTH ] = "";


Log Log_Init( const char* logPath, size_t dataPrecision )
{
  static char filePathExt[ LOG_FILE_PATH_MAX_LENGTH ];

  if( logPath == NULL ) return NULL;

  Log newLog = (Log) malloc( sizeof(LogData) );

  if( strlen( logPath ) == 0 ) newLog->file = TERMINAL_OUTPUT;
  else
  {
    snprintf( filePathExt, LOG_FILE_PATH_MAX_LENGTH, "%s/%s%s%s.log", rootDirectoryPath, baseFileName, logPath, timeStampString );
    if( (newLog->file = fopen( filePathExt, "w+" )) == NULL )
    {
      perror( "error opening file" );
      Log_End( newLog );
      return NULL;
    }
  }

  newLog->dataPrecision = ( dataPrecision < DATA_LOG_MAX_PRECISION ) ? dataPrecision : DATA_LOG_MAX_PRECISION;

  return newLog;
}

void Log_End( Log log )
{
  if( log == NULL ) return;

  if( log->file != NULL )
  {
    fflush( log->file );
    fclose( log->file );
  }

  free( log );
}

void Log_SetDirectory( const char* directoryPath )
{
  (void) GET_FULL_PATH( ( directoryPath != NULL ) ? directoryPath : ".", rootDirectoryPath );
  //strncpy( baseDirectoryPath, ( directoryPath != NULL ) ? directoryPath : "", LOG_FILE_PATH_MAX_LENGTH / 2 );
  (void) MAKE_DIRECTORY( rootDirectoryPath );
}

void Log_SetBaseName( const char* baseName )
{
  snprintf( baseFileName, LOG_FILE_PATH_MAX_LENGTH / 2, "%s-", ( baseName != NULL ) ? baseName : "" );
  if( strlen( baseFileName ) < 2 ) strcpy( baseFileName, "" );
}
  
void Log_SetTimeStamp( void )
{
  timeStampString[ 0 ] = '-';
  time_t timeStamp = time( NULL );
  strncpy( timeStampString + 1, asctime( localtime( &timeStamp ) ), DATE_TIME_STRING_LENGTH );
  for( size_t charIndex = 1; charIndex < DATE_TIME_STRING_LENGTH; charIndex++ )
  {
    char c = timeStampString[ charIndex ];
    if( c == ' ' ) timeStampString[ charIndex ] = '-';
    else if( c == ':' ) timeStampString[ charIndex ] = '_';
    else if( c == '\n' || c == '\r' ) timeStampString[ charIndex ] = '\0';
  }
}

void Log_RegisterValues( Log log, size_t valuesNumber, ... )
{
  if( log == NULL ) return;

  va_list logValues;

  va_start( logValues, valuesNumber );

  for( size_t valueListIndex = 0; valueListIndex < valuesNumber; valueListIndex++ )
    fprintf( log->file, "\t%.*lf", log->dataPrecision, va_arg( logValues, double ) );

  va_end( logValues );
}

void Log_RegisterList( Log log, size_t valuesNumber, double* valuesList )
{
  if( log == NULL ) return;

  for( size_t valueListIndex = 0; valueListIndex < valuesNumber; valueListIndex++ )
    fprintf( log->file, "\t%.*lf", log->dataPrecision, valuesList[ valueListIndex ] );
}

void Log_PrintString( Log log, const char* formatString, ... )
{
  FILE* outputPath = ( log != NULL ) ? log->file : TERMINAL_OUTPUT;

  va_list logValues;

  va_start( logValues, formatString );

  vfprintf( outputPath, formatString, logValues );

  va_end( logValues );

  fprintf( outputPath, "\n" );
}

void Log_EnterNewLine( Log log, double timeStamp )
{
  if( log == NULL ) return;

  if( ftell( log->file ) > 0 ) fprintf( log->file, "\n" );

  fprintf( log->file, "%g", timeStamp );
}
