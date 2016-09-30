#include "BinaryMatrixReader.hh"

    BinaryMatrixReader::BinaryMatrixReader(const std::string& matrix_path)
: matrix_path_(matrix_path), matrix_ifs_(matrix_path_.c_str(), std::ios_base::binary)
{
    // Read matrix dimensions once for all
    matrix_ifs_.read(reinterpret_cast<char*>(&matrix_num_vars_), sizeof(uint64_t));
    matrix_ifs_.read(reinterpret_cast<char*>(&matrix_num_obs_), sizeof(uint64_t));
    vars_ids_off_ = matrix_ifs_.tellg();
    vars_data_off_ = vars_ids_off_ + sizeof(uint32_t)*matrix_num_vars_;
}

bool BinaryMatrixReader::get_matrix_vars_ids(uint64_t block_start, uint64_t block_end, std::vector<uint32_t>& vars_ids_block)
{
    if ((block_start > block_end) || (block_end >= matrix_num_vars_))
        return false;

    vars_ids_block.resize(block_end-block_start);

    matrix_ifs_.seekg(vars_ids_off_+sizeof(uint32_t)*block_start);
    matrix_ifs_.read(reinterpret_cast<char*>(vars_ids_block.data()), sizeof(uint32_t)*vars_ids_block.size());

    return true;
}

bool BinaryMatrixReader::get_matrix_vars_data(uint64_t block_start, uint64_t block_end, std::vector<double>& vars_data_block)
{
    if ((block_start > block_end) || (block_end >= matrix_num_vars_))
        return false;

    vars_data_block.resize((block_end-block_start)*matrix_num_obs_);

    matrix_ifs_.seekg(vars_data_off_+sizeof(double)*block_start*matrix_num_obs_);
    matrix_ifs_.read(reinterpret_cast<char*>(vars_data_block.data()), sizeof(double)*vars_data_block.size());

    return true;

}
