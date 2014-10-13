#include "MatrixManip.hh"
#include <cmath>
#include <algorithm>

void MatrixManip::discard_vars_with_too_few_obs(uint64_t min_non_zero, Matrix& mat)
{
	uint64_t num_vars_kept = 0;

	for (uint64_t curr_var = 0; curr_var < mat.num_vars(); curr_var++)
	{
		uint64_t num_non_zero = 0;
		uint64_t curr_obs = 0;

		while (curr_obs < mat.num_obs() && num_non_zero < min_non_zero)
		{
			if (mat.data(curr_var, curr_obs) != 0.0)
				num_non_zero++;
			curr_obs++;
		}

		if (num_non_zero >= min_non_zero)
		{
			for (uint64_t curr_obs = 0; curr_obs < mat.num_obs(); curr_obs++)
			{
				mat.data(num_vars_kept, curr_obs) = mat.data(curr_var, curr_obs);
				mat.var_id(num_vars_kept) = mat.var_id(curr_var);
			}

			num_vars_kept++;
		}
	}

	mat.num_vars_ = num_vars_kept;
}

void MatrixManip::compute_ranks(Matrix& mat)
{
	#pragma omp parallel
	{
		std::vector<uint64_t> var_ranks(mat.num_obs());

		#pragma omp for
		for (uint64_t curr_var = 0; curr_var < mat.num_vars(); curr_var++)
		{
			for (uint64_t curr_obs = 0; curr_obs < mat.num_obs(); curr_obs++)
				var_ranks[curr_obs] = curr_obs;

			std::sort(var_ranks.begin(), var_ranks.end(), RankCmp(&mat.data(curr_var, 0)));

			for(uint64_t i = 0; i < mat.num_obs(); i++)
			{

				const uint64_t start = i;
				while(i < (mat.num_obs()-1) && 
						(mat.data(curr_var, var_ranks[i]) == mat.data(curr_var, var_ranks[i+1])))
				{
					i++;
				}
				const uint64_t end = i;


				double final_rank = (start+end)/2.0;

				for (uint64_t j = start; j <= end;j++)
					mat.data(curr_var, var_ranks[j]) = final_rank;
			}        
		}
	}

}
void MatrixManip::precompute_cors(Matrix& mat)
{
#pragma omp parallel for
	for (uint64_t curr_var = 0; curr_var < mat.num_vars(); curr_var++)
	{

		//Calculate sum and average 
		double sum = 0.0;
		for(uint64_t curr_obs = 0; curr_obs < mat.num_obs(); curr_obs++)
			sum += mat.data(curr_var, curr_obs);

		double avg = sum / mat.num_obs();

		//Calculate factor sum
		double factor_sum = 0.0;
		for(uint64_t curr_obs = 0; curr_obs < mat.num_obs(); curr_obs++)
			factor_sum += std::pow(mat.data(curr_var, curr_obs) - avg,2);

		// Store precomputed cor
		double sqrt_factor_sum = std::sqrt(factor_sum);
		for (uint64_t curr_obs = 0; curr_obs < mat.num_obs(); curr_obs++)
			mat.data(curr_var, curr_obs) = (mat.data(curr_var, curr_obs) - avg)/sqrt_factor_sum;
	}
}



