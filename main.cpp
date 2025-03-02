/* Orienteering
 *
 * Desc:
 * This is a program that first reads information concerning
 * orienteering routes from the input file, stores them into
 * a suitable data structure, and then permits the user to
 * make searches in the data structure in question.
 *
 * Program authors
 *
 * Name: Zannatul Ferdous
 * Student number: 150164676
 * UserID: hczafe
 * E-Mail: zannatul.2.ferdous@tuni.fi
 *
 * Name: Truong Thanh Tuyen
 * Student number: 153156296
 * UserID: hmm638
 * E-Mail: thanhtuyen.truong@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 *
 * */

#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include <iostream>

int main()
{
    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


