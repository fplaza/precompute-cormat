#include "BinaryMatrixWriter.hh"
#include <fstream>

void BinaryMatrixWriter::write(const Matrix& mat, const std::string& output_file)
{
    std::ofstream ofs;
    ofs.open(output_file.c_str(), std::ios_base::binary);

    // Write file type metadata
    ofs.write(Matrix::FILE_TYPE, sizeof(Matrix::FILE_TYPE)-1);

    // Write matrix dimensions
    ofs.write(reinterpret_cast<const char*>(&mat.num_vars_), sizeof(size_t));
    ofs.write(reinterpret_cast<const char*>(&mat.num_obs_), sizeof(size_t));

    // Write variables names
    for (size_t curr_var = 0; curr_var < mat.num_vars(); ++curr_var)
    {
        ofs << mat.var_name(curr_var) << '\0';
    }

    // Write observations names
    for (size_t curr_obs = 0; curr_obs < mat.num_obs(); ++curr_obs)
    {
        ofs << mat.obs_name(curr_obs) << '\0';
    }

    // Write matrix data
    ofs.write(reinterpret_cast<const char*>(mat.data_), sizeof(double)*mat.num_vars()*mat.num_obs());

    ofs.close();
}
