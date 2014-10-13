#ifndef PARAMETERS_HH
#define PARAMETERS_HH

#include <string>
#include <stdint.h>

struct Parameters
{
	std::string matrix_path;
	std::string precomputed_cormat_path;
	bool with_header;
	std::string cor_method;
	uint64_t min_non_zero;

	static Parameters parse(int argc, char* argv[]);
	static void check_file_is_readable(const std::string& filepath);
	static void check_file_is_writable(const std::string& filepath);
};

#endif // PARAMETERS_HH
