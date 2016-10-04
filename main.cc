#include <iostream>
#include <new>
#include <cstdlib>
#include "TimeProfiler.hh"
#include "Parameters.hh"
#include "TextMatrixReader.hh"
#include "TextMatrixWriter.hh"
#include "BinaryMatrixWriter.hh"
#include "BinaryMatrixReader.hh"
#include "MatrixManip.hh"

void no_more_memory()
{
    std::cerr << "error: memory allocation failed." << std::endl;
    std::exit (1);
}

int main(int argc, char *argv[])
{
    std::set_new_handler(no_more_memory);

    try
    {
        TimeProfiler time_profiler;
        time_profiler.start_new_timer("Total");

        const Parameters& pars = Parameters::parse(argc, argv);

        std::cout << "Reading matrix..." << std::endl;
        time_profiler.start_new_timer("Reading matrix");
        Matrix mat = TextMatrixReader::read(pars.input_file);
        time_profiler.stop_last_timer();
        std::cout << "Done." <<
            "The matrix has "  << mat.num_vars() << " variables with " << mat.num_obs() << " observations.\n" << std::endl;

        std::cout << "Filtering variables with less than " << pars.min_non_zero << " observations." << std::endl;
        time_profiler.start_new_timer("Filtering variables");
        MatrixManip::discard_vars_with_too_few_obs(pars.min_non_zero, mat);
        time_profiler.stop_last_timer();
        std::cout << "Done. " << mat.num_vars() << " variables remaining.\n" << std::endl;

        if (pars.cor_method == "spearman")
        {
            std::cout << "Computing ranks..." << std::endl;
            time_profiler.start_new_timer("Computing ranks");
            MatrixManip::compute_ranks(mat);
            time_profiler.stop_last_timer();
            std::cout << "Done\n" << std::endl;
        }

        std::cout << "Precomputing correlations..." << std::endl;
        time_profiler.start_new_timer("Precomputing correlations");
        MatrixManip::precompute_cors(mat);
        time_profiler.stop_last_timer();
        std::cout << "Done\n" << std::endl;

        std::cout << "Writing precomputed correlation matrix..." << std::endl;
        time_profiler.start_new_timer("Writing precomputed correlation matrix");
        BinaryMatrixWriter::write(mat, pars.output_file);
        time_profiler.stop_last_timer();
        std::cout << "Done\n" << std::endl;

        time_profiler.stop_last_timer();
        std::cout << time_profiler << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
