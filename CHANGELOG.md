-## [0.9.9] - 2023-09-01
### Added
- Written in C language for postgraduate entrance examination.

## [1.0.0] - 2024-07-13
### Features
- Matply first version officially released.

### Added
- Completed the first version of C language conversion to Dart.

## [1.0.1] - 2024-07-14
### Fixed
- Fixed the problem of matply.dll not being found. The solution is to splice the pub-cache path. If the user customizes the cache path, the user can reassign the path through pubCacheDir.

## [1.0.2] - 2024-07-15
### Refactored
- The underlying API is completely oriented to two-dimensional arrays rather than matrix objects, making it easier and more flexible to use Dart features to extend the base class itself（like list's extension in Dart）.
- Use linked lists to detect and manage the memory requested by each newly created matrix instance to prevent memory leaks. This is implemented in C language at the bottom level and controlled by a global linked list instance. When the user decides to create a matrix instance, he can selectively use the initMp method to initialize it, and then use the freeMp method to manually release all recorded matrix instances at the end of the program.
- Added some other useful matrix methods.

## [1.0.3] - 2024-07-15 
### Fixed
- Function not imported problem.

## [1.0.4] - 2024-07-15
### Fixed
- Function not imported problem.

## [1.0.5] - 2024-07-24
### Added
- Added some useful matrix methods.Most of them trigger behaviors based on the passed conditional functions.

### Fixed
- Some C API errors are fixed.

### Optimized
- Clearer function file structure.

### Warning
- Suspend the expansion of List functions and do not recommend using list expansion.

## [1.0.6] - 2024-08-01
### Added
- Added some useful matrix methods.

### Fixed
- Some C API errors are fixed and optimized.

## [1.0.7] - 2024-08-15
### Added
- Added some useful matrix methods，especially on Probability Theory and Mathematical Statistics.
- Linux and Android platform support.
- Preview version of extension by using C++.

### Fixed
- Fixed various bugs left over from using the matrix class before the refactoring version.
- Some other C API errors are fixed and optimized.

### Optimized
- Optimized some functions.

## [1.0.8] - 2024-09-02
### Added
- Added some useful matrix methods and properties.
- Added preview of DataFrame data types.
- Simple csv format reading and MatrixType conversion.

### Optimized
- Optimized the underlying memory management solution.Considering that each instance created by MatPly will be released uniformly by the memory pool at the end of the program, and the only automatic operation is to add the instance to the memory pool, a bidirectional linked list is used to implement it.
- Optimized some functions.
- Confirmed the expansion of the list.

