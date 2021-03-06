#ifndef BINARY_MATRIX_WRITER_HH
#define BINARY_MATRIX_WRITER_HH

#include "Matrix.hh"

class BinaryMatrixWriter
{
    public:
        static void write(const Matrix& mat, const std::string& output_file);
};

#endif //BINARY_MATRIX_WRITER_HH
