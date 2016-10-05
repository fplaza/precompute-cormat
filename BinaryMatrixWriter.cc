#include "BinaryMatrixWriter.hh"
#include <fstream>

void BinaryMatrixWriter::write(const Matrix& mat, const std::string& output_file)
{
    std::ofstream ofs;
    ofs.open(output_file.c_str(), std::ios_base::binary);

    // Write file type metadata
    ofs.write(Matrix::FILE_TYPE, sizeof(Matrix::FILE_TYPE)-1);

    // Write matrix dimensions
    ofs.write(reinterpret_cast<const char*>(&mat.num_vars_), sizeof(boost::uint64_t));
    ofs.write(reinterpret_cast<const char*>(&mat.num_obs_), sizeof(boost::uint64_t));

    // Write variables names
    ofs.write(reinterpret_cast<const char*>(mat.vars_names_), sizeof(boost::uint32_t)*mat.num_vars());

    // Write matrix data
    ofs.write(reinterpret_cast<const char*>(mat.data_), sizeof(double)*mat.num_vars()*mat.num_obs());

    ofs.close();
}
