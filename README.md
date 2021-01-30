# SoboUtils
SoboUtils is a set of utilities helping doing the everyday programmer's work in C.
It contains functions for string, file and time manipulation, as well as the interface
making it easier to generate HTTP requests and parse data using libCurl.

# Copyright
© Copyright by Krzysztof Sobolewski 2020-2021.
SoboUtils is Open Source software, licensed under the MIT license available here:
https://opensource.org/licenses/mit-license.php

# Contact
You can contact the author using the email:
<krzysztof.sobolewski@gmail.com>
I'm looking for cooperation in the further development of this software.

# Compilation and Installation
## Build without tests:
```make``` or ```make all```
In the root directory of the project. 
The binaries will be built into ./bin. 
The binaries are:
```libsoboutils.a```

## Build with tests:
```make alltest```
In the same directory will do the same + build tests. 
The binaries will be built into ./bin.
The binaries are:
```libsoboutils.a```
```test_utils_file```
```test_utils_string```
```test_utils_time```

## Install in the common paths:
After ```make```, ```make all```  or ```make alltest``` has been done, call:
```make install```
in the root directory of the project.
**WARNING: requires the sudo access**.

The library (libsoboutils.a) and the header file will be put in the target 
common directories, defined into the makefile in the variables:
SOBOUTILS_INCLUDE_PATH ?= '/usr/local/share/soboutils'
SOBOUTILS_LIB_PATH     ?= '/usr/local/lib/soboutils'

You may change those paths to conform with your system configuration. 

# Usage and Examples
```TODO```
