#include "BinaryMatrixWriter.hh"
#include <fstream>

void BinaryMatrixWriter::write(const Matrix& mat, const std::string& precomputed_cormat_path)
{
	std::ofstream ofs;
	ofs.open(precomputed_cormat_path.c_str(), std::ios_base::binary);

	ofs.write(Matrix::FILE_TYPE, sizeof(Matrix::FILE_TYPE)-1);
	ofs.write(reinterpret_cast<const char*>(&mat.num_vars_), sizeof(uint64_t));
	ofs.write(reinterpret_cast<const char*>(&mat.num_obs_), sizeof(uint64_t));
	ofs.write(reinterpret_cast<const char*>(mat.vars_ids_), sizeof(uint32_t)*mat.num_vars());
	ofs.write(reinterpret_cast<const char*>(mat.vars_data_), sizeof(double)*mat.num_vars()*mat.num_obs());

	ofs.close();
}
