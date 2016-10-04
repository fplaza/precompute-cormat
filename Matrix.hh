#ifndef MATRIX_HH
#define MATRIX_HH

#include <vector>
#include <string>
#include <iostream>

class Matrix
{
    friend class TextMatrixReader;
    friend class BinaryMatrixReader;
    friend class BinaryMatrixWriter;
    friend class MatrixManip;

    public:
        ~Matrix();
        size_t num_vars() const;
        size_t num_obs() const;
        const std::vector<std::string>& vars_names() const;
        const std::vector<std::string>& obs_names() const;
        const std::string& var_name(const size_t var_id) const;
        const std::string& obs_name(const size_t obs_id) const;
        double data(const size_t var_id, const size_t obs_id) const;
        const double* data() const;

    private:
        static const char FILE_TYPE[9];
        size_t num_vars_;
        size_t num_obs_;
        std::vector<std::string> vars_names_;
        std::vector<std::string> obs_names_;
        double* data_;
        Matrix(const size_t num_vars, const size_t num_obs);
        std::string& var_name(const size_t var_id);
        std::string& obs_name(const size_t obs_id);
        double& data(const size_t var_id, const size_t obs_id);
};

inline Matrix::~Matrix()
{
    delete[] data_;
}

inline size_t Matrix::num_vars() const
{
    return num_vars_;
}

inline size_t Matrix::num_obs() const
{
    return num_obs_;
}

inline const std::vector<std::string>& Matrix::vars_names() const
{
    return vars_names_;
}

inline const std::vector<std::string>& Matrix::obs_names() const
{
    return obs_names_;
}

inline const std::string& Matrix::var_name(const size_t var_id) const
{
    return vars_names_[var_id];
}

inline const std::string& Matrix::obs_name(const size_t obs_id) const
{
    return obs_names_[obs_id];
}

inline double Matrix::data(const size_t var_id, const size_t obs_id) const
{
    return data_[var_id*num_obs() + obs_id];
}

inline Matrix::Matrix(const size_t num_vars, const size_t num_obs)
    : num_vars_(num_vars),
    num_obs_(num_obs),
    vars_names_(num_vars),
    obs_names_(num_obs),
    data_(new double[num_vars*num_obs])
{};

inline std::string& Matrix::var_name(const size_t var_id)
{
    return vars_names_[var_id];
}

inline std::string& Matrix::obs_name(const size_t obs_id)
{
    return obs_names_[obs_id];

}

inline double& Matrix::data(const size_t var_id, const size_t obs_id)
{
    return data_[var_id*num_obs() + obs_id];
}

inline const double* Matrix::data() const
{
    return data_;
}

#endif // MATRIX_HH
