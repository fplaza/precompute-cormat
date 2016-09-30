#ifndef BINARY_MATRIX_READER_HH
#define BINARY_MATRIX_READER_HH

#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>

class BinaryMatrixReader
{
    private:
        const std::string& matrix_path_;
        std::ifstream matrix_ifs_;
        uint64_t matrix_num_vars_;
        uint64_t matrix_num_obs_;
        std::streamoff vars_ids_off_;
        std::streamoff vars_data_off_;
    public:
        BinaryMatrixReader(const std::string& matrix_path);
        uint64_t get_matrix_num_vars() const;
        uint64_t get_matrix_num_obs() const;
        bool get_matrix_vars_ids(uint64_t block_start, uint64_t block_end, std::vector<uint32_t>& vars_ids_block);
        bool get_matrix_vars_data(uint64_t block_start, uint64_t block_end, std::vector<double>& vars_data_block);
};

inline uint64_t BinaryMatrixReader::get_matrix_num_vars() const
{
    return matrix_num_vars_;
}

inline uint64_t BinaryMatrixReader::get_matrix_num_obs() const
{
    return matrix_num_obs_;
}


#endif
