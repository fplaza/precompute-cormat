#ifndef TEXT_MATRIX_READER_HH
#define TEXT_MATRIX_READER_HH

#include "Matrix.hh"
#include <string>

class TextMatrixReader
{
    public:
        static Matrix read(const std::string& matrix_path);
    private:
        static const size_t MAX_LINE_LENGTH;
};

#endif // TEXT_MATRIX_READER_HH
