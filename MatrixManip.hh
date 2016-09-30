#ifndef MATRIX_MANIP_HH
#define MATRIX_MANIP_HH

#include "Matrix.hh"

class MatrixManip
{
    private:
        class RankCmp
        {
            private:
                const double* var_data_;
            public:
                RankCmp(const double* var_data)
                    : var_data_(var_data)
                {};
                bool operator()(const uint64_t lhs, const uint64_t rhs)
                {
                    return var_data_[lhs] < var_data_[rhs];
                }
        };

    public:
        static void discard_vars_with_too_few_obs(uint64_t min_non_zero, Matrix& mat);
        static void compute_ranks(Matrix& mat);
        static void precompute_cors(Matrix& mat);
};

#endif // MATRIX_MANIP_HH
