#include "TextMatrixReader.hh"
#include <fstream>
#include <algorithm>
#include <limits>

// Should be sufficient for the biggest matrices currently processed
const size_t TextMatrixReader::MAX_LINE_LENGTH = 100000;

Matrix TextMatrixReader::read(const std::string& matrix_path)
{
    char line[MAX_LINE_LENGTH];

    std::ifstream ifs;
    ifs.open(matrix_path.c_str());

    // FIRST PASS: get the dimensions of the matrix
    // Get the number of samples
    std::string header;
    std::getline(ifs, header);
    size_t num_obs = std::count_if(header.begin(), header.end(), static_cast<int(*)(int)>(std::isspace));

    // Get the number of genes
    size_t num_vars = 0;
    while (ifs.getline(line, MAX_LINE_LENGTH))
        ++num_vars;

    // Allocate memory to store the count matrix
    Matrix mat(num_vars, num_obs);

    //SECOND PASS: fill the matrix
    ifs.clear();
    ifs.seekg(0);

    // Skip potential "gene_id" or "fragment_id" string
    while (!std::isspace(ifs.get()))
        ;

    // Get samples names
    for (size_t curr_obs = 0; curr_obs < mat.num_obs(); ++curr_obs)
    {
        ifs >> mat.obs_name(curr_obs);
    }
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Get genes ids and genes counts
    for (size_t curr_var = 0; curr_var < mat.num_vars(); ++curr_var)
    {
        ifs.getline(line, MAX_LINE_LENGTH);
        char* pos = line;

        while (*pos != '\0' && !std::isspace(*pos))
            ++pos;

        const std::string gene_name(line, pos-line);
        mat.var_name(curr_var) = gene_name;

        for (size_t curr_obs = 0; curr_obs < mat.num_obs(); ++curr_obs)
        {
            mat.data(curr_var, curr_obs) = strtod(pos, &pos);
        }
    }

    ifs.close();

    return mat;

}

