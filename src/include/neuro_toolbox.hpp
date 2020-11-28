/*! 
 * \author Abolfazl Ziaeemehr
 * \version 0.1
 * \date Nov. 2020
 * \copyright GNU Public License
 * \mainpage HEADER FILES only C++ library for analysis of neurophysiological and simulated data. 
 * \section intro_sec Introduction
 * 
 * # installation 
 * 
 * There is no need for installation. It's a header file only library. You just need to put the header files in a directory and pass the address of the directory to the make file or directly pass it to the terminal using `-I PATH_TO_HEADER_FILES` and also include the header file 
 * 
 * ```c++
 * #include "neuro_toolbox.hpp"
 * ```
 * 
 * and access to the content with `NTB::`  namespace.
 * 
 * # testing 
 * 
 * neuro_toolbox use [catch2](https://github.com/catchorg/Catch2) unittest. To use tests 
 * 
 * ```shell
 * cd src/tests
 * make clean
 * make all
 * 
 * # or test each header file seperately
 * make signal_proccesing
 * make random_generators
 * make IO 
 *
 * ```
 * 
 * for auto-generated **documentation** you need to have `doxygen` installed on your machine.
 * ```shell
 * # on linux machines use
 * sudo apt-get install doxygen
 * cd doc
 * doxygen 
 * ```
 * 
 * which produce `html` file. 

*/

#ifndef NEURO_TOOLBOX
#define NEURO_TOOLBOX

#include "IO.hpp"
#include "utility.hpp"
#include "random_generators.hpp"
#include "signal_processing.hpp"

#endif // !NEURO_TOOLBOX