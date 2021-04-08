#include <iostream>
#include <vector>
#include <fstream>
#include <casmutils/definitions.hpp>
#include <casmutils/xtal/structure.hpp>
#include <casmutils/xtal/structure_tools.hpp>
#include <casmutils/xtal/coordinate.hpp>
#include <casmutils/xtal/lattice.hpp>
#include <casmutils/xtal/symmetry.hpp>
#include <casmutils/sym/group-io.hpp>
#include <casmutils/sym/symgroup.hpp>
#include <CLI/CLI.hpp>

namespace cu=casmutils;
namespace std;

//Do we want to make this with a CLI? or just as a function that can be accessed?


int main(int argc, char* argv[]) {
    //CLI take in path to group (in form of a vector of CartOps) and a POSCAR/lattice

    //read group from file
    vector<cu::sym::CartOp> input_group = 
    //reads lattice
    cu::xtal::Lattice input_lattice = 
    
    //make mult table its own function: 
    mult_table = make_mult_table(input_group, (comparator), input_lattice);

    //print mult table (using function)
    print_very_nicely(mult_table);

    return 0;
}

//general template for making mult table
template <typename SymOpType, typename Compare>
vector<vector<int>> make_mult_table(vector<SymOpType>& group, take a comparator, cu::xtal::Lattice& lattice) { //use comparator as an input to make this more general
    //make vector of vectors
    vector<vector<int>> output;

    //match labels to group

    //loop everything
    for(int i=0,i<group.size(),i++) {
        vector<int> temp;
        for(int j=0,j<group.size(),j++) {
            product = group[i] * group[j]; //TODO::fix mult function, make sure 
            
            //map product to an existing element (or throw error otherwise)

            // unitary compare function (input:product) compare to everything in group and output the label from group
            // findif()

            //output index to int (dont need if int but useful if this is a char or something)
            int identity; //the mapped index of the new symop
            temp.pushback(identity); //
        }
        output.pushback(temp);
    }
    return output;
}

void print_very_nicely(vector<vector<int>>* mult_table) {
    //print out mult_table - using ptr to save memory
    //iterate through and print nicely
}