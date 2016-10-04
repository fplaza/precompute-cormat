#include "TextMatrixWriter.hh"
#include <fstream>

void TextMatrixWriter::write(const Matrix& mat, const std::string& output_file)
{
    std::ofstream ofs(output_file.c_str());

    for (size_t curr_obs = 0; curr_obs < mat.num_obs(); ++curr_obs)
    {
        ofs << '\t' << mat.obs_name(curr_obs);
    }
    ofs << '\n';

    for (size_t curr_var = 0; curr_var < mat.num_vars(); ++curr_var)
    {
        ofs << mat.var_name(curr_var);

        for (size_t curr_obs = 0; curr_obs < mat.num_obs(); ++curr_obs)
            ofs << '\t' << mat.data(curr_var, curr_obs);

        ofs << '\n';
    }

    ofs.close();
}
