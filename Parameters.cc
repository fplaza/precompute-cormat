#include "Parameters.hh"
#include <iostream>
#include <fstream>
#include <exception>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

Parameters Parameters::parse(int argc, char* argv[])
{
    Parameters pars;

    // Create options decription
    po::options_description all_parameters("");
    po::options_description io_parameters("Input/Output parameters");
    po::options_description computation_parameters("Computation parameters");
    po::options_description misc_parameters("Miscellaneous parameters");

    io_parameters.add_options()
        ("input-file,i", po::value<std::string>(&pars.input_file), "Text file containing the variables and their respective observations.")
        ("with-header", boost::program_options::bool_switch(&pars.with_header), "Set if the input matrix has an with header")
        ("output-file,o", po::value<std::string>(&pars.output_file), "Generated binary file containing the precomputed correlation matrix.")
        ;

    computation_parameters.add_options()
        ("cor-method,m", po::value<std::string>(&pars.cor_method)->default_value("pearson"), "Indicates which correlation coefficient ('pearson' or 'spearman') is to be computed.")
        ("min-non-zero", po::value<uint64_t>(&pars.min_non_zero)->default_value(3), "Discard variables which have fewer than 'arg' non-zero observations.")
        ;

    misc_parameters.add_options()
        ("help,h", "display this help and exit.")
        ;

    all_parameters.add(io_parameters).add(computation_parameters).add(misc_parameters);

    // Retrieve and parse command line parameters
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(all_parameters).run(), vm);

    // Print help
    if (argc == 1 || vm.count("help"))
    {
        std::cout << all_parameters << std::endl;
        std::exit(0);
    }

    po::notify(vm);

    check_file_is_readable(pars.input_file);
    check_file_is_writable(pars.output_file);

    if (pars.cor_method != "pearson" && pars.cor_method != "spearman")
        throw (std::invalid_argument("error: '" + pars.cor_method + "' is not a valid correlation coefficient."));


    return pars;
}

void Parameters::check_file_is_readable(const std::string& filepath)
{
    std::ifstream ifs;
    ifs.open(filepath.c_str());

    if (ifs.good())
    {
        ifs.close();
    }
    else
    {
        throw (std::invalid_argument("error: " + filepath +
                    " cannot be opened. Check that the path is valid and that you have read permissions."));
    }
}

void Parameters::check_file_is_writable(const std::string& filepath)
{
    std::ofstream ofs;
    ofs.open(filepath.c_str());

    if (ofs.good())
    {
        ofs.close();
    }
    else
    {
        throw (std::invalid_argument("error: " + filepath +
                    " cannot be created. Check that the path is valid and that you have write permissions."));
    }
}

