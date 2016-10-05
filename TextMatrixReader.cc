#include "TextMatrixReader.hh"
#include <fstream>
#include <algorithm>
#include <limits>

// Should be sufficient for the biggest matrices currently processed
const size_t TextMatrixReader::MAX_LINE_LENGTH = 100000;

Matrix TextMatrixReader::read(const std::string& input_file, const bool with_header)
{
    char line[MAX_LINE_LENGTH];

    std::ifstream ifs;
    ifs.open(input_file.c_str());

    // FIRST PASS: get the dimensions of the matrix
    // Get the number of observations
    std::string header;
    std::getline(ifs, header);
    const boost::uint64_t num_obs = std::count_if(header.begin(), header.end(), static_cast<int(*)(int)>(std::isspace));

    // Get the number of variables
    boost::uint64_t num_vars = 0;
    while (ifs.getline(line, MAX_LINE_LENGTH))
        ++num_vars;

    if (!with_header)
        ++num_vars;

    // Allocate memory to store the matrix
    Matrix mat(num_vars, num_obs);

    //SECOND PASS: fill the matrix
    ifs.clear();
    ifs.seekg(0);

    // Skip potential header
    if (with_header)
        ifs.getline(line, MAX_LINE_LENGTH);

    // Get vars ids and data
    for (boost::uint64_t curr_var = 0; curr_var < mat.num_vars(); ++curr_var)
    {
        ifs.getline(line, MAX_LINE_LENGTH);
        char* pos = line;

        mat.var_name(curr_var) = strtoul(pos, &pos, 10);

        for (boost::uint64_t curr_obs = 0; curr_obs < mat.num_obs(); ++curr_obs)
        {
            mat.data(curr_var, curr_obs) = strtod(pos, &pos);
        }
    }

    ifs.close();

    return mat;

}

