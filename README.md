# neuro_toolbox
*HEADER FILES* only C++ library for analysis of *neurophysiological* and *simulated* data.

The online [documentation](https://ziaeemehr.github.io/neuro_toolbox/)  is also available. 

## installation 

There is no need for installation. It's a header file only library. You just need to put the header files in a directory and pass the address of the directory to the make file or directly pass it to the terminal using `-I PATH_TO_HEADER_FILES` and also include the header file 

```c++
#include "neuro_toolbox.hpp"
```

and access to the content with `NTB::`  namespace.

### testing 

neuro_toolbox use [catch2](https://github.com/catchorg/Catch2) unittest. To use tests 

```shell
cd src/tests
make clean

make all # to run all tests

# or test each header file seperately
make signal_proccesing
make random_generators
make IO
```

### Dependencies

- fftw3

  ```shell
  # on ubuntu machines
  sudo apt-get update -y
  sudo apt-get install -y fftw3
  ```

To generate documents you need to have `doxygen` installed on your machine.

```shell
# on linux machines use
sudo apt-get install doxygen
cd doc
doxygen 
```

which produce `html` file.   







