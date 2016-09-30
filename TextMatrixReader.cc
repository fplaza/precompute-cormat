#include "TextMatrixReader.hh"
#include <fstream>
#include <algorithm>

// Should be sufficient for the biggest matrices currently processed
const uint64_t TextMatrixReader::MAX_LINE_LENGTH = 100000;

Matrix TextMatrixReader::read(const std::string& matrix_path, bool with_header)
{
    char line[MAX_LINE_LENGTH];

    std::ifstream ifs;
    ifs.open(matrix_path.c_str());

    // FIRST PASS: get the dimensions of the matrix
    // Skip header if necessary
    if (with_header)
        ifs.getline(line, MAX_LINE_LENGTH);

    // Get the number of samples
    ifs.getline(line, MAX_LINE_LENGTH);
    char* pos = line;

    uint64_t num_obs = 0;
    while (*pos != '\0')
    {
        if (std::isspace(*pos))
            num_obs++;
        pos++;
    }

    uint64_t num_vars = 1;
    while (ifs.getline(line, MAX_LINE_LENGTH))
        num_vars++;

    // Allocate memory to store the count matrix
    Matrix mat(num_vars, num_obs);

    //SECOND PASS: fill the matrix
    ifs.clear();
    ifs.seekg(0);

    // Skip header if necessary
    if (with_header)
        ifs.getline(line, MAX_LINE_LENGTH);

    // Get genes ids and genes counts
    for (uint64_t curr_var = 0; curr_var < mat.num_vars(); curr_var++)
    {
        ifs.getline(line, MAX_LINE_LENGTH);
        char* pos = line;

        mat.var_id(curr_var) = strtoul(pos, &pos, 10);

        for (uint64_t curr_obs = 0; curr_obs < mat.num_obs(); curr_obs++)
        {
            // Data is read as single precision float to speed up the process
            // If necessary, replace strtof by strtod
            mat.data(curr_var, curr_obs) = strtof(pos, &pos);
        }
    }

    ifs.close();

    return mat;
}

