## [0.9.9] - 2023-09-01
### Added
- Written in C language for postgraduate entrance examination

## [1.0.0] - 2024-07-13
### Features
- Matply first version officially released

### Added
- Completed the first version of C language conversion to Dart

## [1.0.1] - 2024-07-14
### Fixed
- Fixed the problem of matply.dll not being found. The solution is to splice the pub-cache path. If the user customizes the cache path, the user can reassign the path through pubCacheDir.

## [1.0.2] - 2024-07-15
### Refactored
- The underlying API is completely oriented to two-dimensional arrays rather than matrix objects, making it easier and more flexible to use Dart features to extend the base class itself（like list's extension in Dart）.
- Use linked lists to detect and manage the memory requested by each newly created matrix instance to prevent memory leaks. This is implemented in C language at the bottom level and controlled by a global linked list instance. When the user decides to create a matrix instance, he can selectively use the initMp method to initialize it, and then use the freeMp method to manually release all recorded matrix instances at the end of the program.
- Added some other useful matrix methods
