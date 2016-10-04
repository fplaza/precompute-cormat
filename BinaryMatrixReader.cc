#include "BinaryMatrixReader.hh"
#include <fstream>
#include <cstring>
#include <stdexcept>

Matrix BinaryMatrixReader::read(const std::string& input_file)
{
    std::ifstream ifs;
    ifs.open(input_file.c_str());

    char header[sizeof(Matrix::FILE_TYPE)-1];
    ifs.read(header, sizeof(header));

    if (std::memcmp(header, Matrix::FILE_TYPE, sizeof(header)) != 0)
        throw std::invalid_argument(input_file + " is not a valid binary matrix file.");

    // Read dimensions
    size_t num_vars;
    size_t num_obs;
    ifs.read(reinterpret_cast<char*>(&num_vars), sizeof(size_t));
    ifs.read(reinterpret_cast<char*>(&num_obs), sizeof(size_t));

    // Allocate memory
    Matrix mat(num_vars, num_obs);

    // Read variables names
    for (size_t curr_var = 0; curr_var < mat.num_vars(); ++curr_var)
    {
        std::getline(ifs, mat.var_name(curr_var), '\0' );
    }

    // Read observations names
    for (size_t curr_obs = 0; curr_obs < mat.num_obs(); ++curr_obs)
    {
        std::getline(ifs, mat.obs_name(curr_obs), '\0' );
    }

    // Read matrix data
    ifs.read(reinterpret_cast<char*>(mat.data_), sizeof(double)*mat.num_vars()*mat.num_obs());

    ifs.close();

    return mat;
}

