#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }

    // RPN calc;
    // int result = calc.evaluate(argv[1]);
    // std::cout <<  result << std::endl;
    // -> programm crasht wenn in evaluate was schief laeuft, deswegen try catch

    try
    {
        RPN calc;
        int result = calc.evaluate(argv[1]);
        std::cout << result << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
}