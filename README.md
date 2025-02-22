# indented_output_stream
A boost-iostream filter for outputting multi-line strings with consistent indentation. 

This little helper addresses two use cases for outputting text via C++ `std::iostreams`: 
* Properly indented output of nested data structures using C++ stream insertion operators (i.e. `operator<<(struct&)`) wether for ad-hoc debug output or text file formats like JSON and XML.
* To a lesser extend the ability to output text-files or multi-line strings, i.e. strings containing new-lines (`\n` characters) to a single, fixed indentation level.

The implementation is based on the Boost.Iostreams library and consists of a filter that replaces new-line characters with a new-line followed by a number of spaces according to indentation size (i.e. the number of spaces per indentation level) and the filter's current indentation level. The indentation size is specified at filter-instantion time, the indentation size is controlled via a token-protocol using the zero-character (`\0`) as escape character, followed by either the character `i` or `d` for incrementing and decrementing the indentation level. The protocol tokens can be inserted into the character stream via four manipulators:
1 `inc` manipulator increases the filter's indentation level by one
2 `dec` manipulator decreases the filter's indentation level by one
3 `incn` increases the filter's indentation level like `inc` followed by a new-line (`\n`)
4 `decn` decreases the filter's indentation level like `dec` followed by a new-line (`\n`)

The filter class and the manipulator functions are header-file only, i.e. compilation is not required. To build the project's example and unit-tests, CMake is required. The `CMakeLists.txt` defines two path variables, one for the path to the boost include directory and one for the path to the boost link/library directory.

The example shows how the classes of a typical 3d scene graph could be written do and output stream for debugging purposes. 
