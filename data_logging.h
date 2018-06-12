//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
//  Copyright (c) 2016-2018 Leonardo Consoni <consoni_2519@hotmail.com>         //
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


/// @file data_logging.h
/// @brief Functions for logging/registering data over time to a text file or terminal


#ifndef DATA_LOGGING_H
#define DATA_LOGGING_H


#include <stddef.h>

#define LOG_FILE_PATH_MAX_LENGTH 256        ///< Maximum length of log file (inside data structure) absolute path string
#define DATA_LOG_MAX_PRECISION 15           ///< Maximum decimal precision for numerical data in a log

#ifdef DEBUG
  /// Alias for printing a formatted string to terminal (like in printf) with source function information
  #define DEBUG_PRINT( formatString, ... ) Log_PrintString( NULL, "%s(%d): " formatString, __func__, __LINE__, __VA_ARGS__ )
#else
  #define DEBUG_PRINT( formatString, ... )
#endif


typedef struct _LogData LogData;        ///< Single log internal data structure
typedef LogData* Log;                   ///< Opaque reference to log internal data structure

/// @brief Initialize data logging to terminal or a specific text file
/// @param[in] logPath path (from base one) to log file or empty string for terminal logging
/// @param[in] dataPrecision decimal precision for numerical data in this log
/// @return reference/pointer to created log profile structure (NULL on errors)
Log Log_Init( const char* logPath, size_t dataPrecision );

/// @brief Deallocate and destroys given data structure
/// @param[in] log reference to log profile
void Log_End( Log log );

/// @brief Overwrite default root file path where logs will be saved
/// @param[in] directoryPath path (absolute or relative) to desired root directory
void Log_SetDirectory( const char* directoryPath );

/// @brief Define a common base (folder) name and time stamp for log files
/// @param[in] baseName name of the folder (inside root path) where new logs will be saved, with current time stamp
void Log_SetBaseName( const char* baseName );

/// @brief Log a numerical values in a variable arguments list format
/// @param[in] log reference to log profile
/// @param[in] valuesNumber number of values being logged
/// @param[in] ... variable list of numerical values to be logged
void Log_RegisterValues( Log log, size_t valuesNumber, ... );

/// @brief Log a numerical values in a array format
/// @param[in] log reference to log profile
/// @param[in] valuesNumber number of values being logged
/// @param[in] ... array/pointer of numerical values to be logged
void Log_RegisterList( Log log, size_t valuesNumber, double* valuesList );

/// @brief Log custom string
/// @param[in] log reference to log profile
/// @param[in] formatString format string (like in printf) to list of values
/// @param[in] ... variable list of values/arguments to be formatted (like in printf)
void Log_PrintString( Log log, const char* formatString, ... );

/// @brief Enter new log line indexed in time
/// @param[in] log reference to log profile
/// @param[in] timeStamp provided time index/stamp for new log line
void Log_EnterNewLine( Log log, double timeStamp );


#endif // DATA_LOGGING_H
