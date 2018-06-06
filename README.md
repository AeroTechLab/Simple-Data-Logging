# Simple Data Logging

Utility functions and data structures for saving/printing application logs

Output time-indexed numeric variables or custom strings to a terminal or text file, in a flexible format defined by code, e.g:

    "Custom string 1"
    <time_stamp_0> <variable_0> <variable_1> <variable_2> <variable_3>
    <time_stamp_1> <variable_0> <variable_1> <variable_2> <variable_3>
    <time_stamp_2> <variable_0> <variable_1> <variable_2> <variable_3>
    <time_stamp_3> <variable_0> <variable_1> <variable_2> <variable_3>
    "Custom string 2"
    <time_stamp_4> <variable_4>
    <time_stamp_5> <variable_1> <variable_2> <variable_3>
    <time_stamp_6> <variable_1> <variable_2> <variable_3>

## Usage

On a terminal, get the [GitHub code repository](https://github.com/LabDin/Simple-Data-Logging) with:

    $ git clone https://github.com/LabDin/Simple-Data-Logging [<my_project_folder>]

With dependencies set, you can now build the library to a separate build directory with [CMake](https://cmake.org/):

    $ mkdir build && cd build
    $ cmake ..
    $ make

For building it manually e.g. with [GCC](https://gcc.gnu.org/) in a system without **CMake** available, the following shell command (from project directory) would be required:

    $ gcc data_logging.c -I. -shared -fPIC -o libdatalogging.{so,dll}

## Documentation

Descriptions of how the functions and data structures work are available at the [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)-generated [documentation pages](https://labdin.github.io/Simple-Data-Logging/data__logging_8h.html)
