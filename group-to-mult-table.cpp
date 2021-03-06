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

//TODO:: turn these into headers instead of keeping it in the main.cpp
//Do we want to make this with a CLI? or just as a function that can be accessed?

//general template for making mult table
template <typename SymOpType, typename ComparatorType>
//assumes a unitary comparator for now
vector<vector<int>> make_mult_table(const vector<SymOpType>& group, ComparatorType comparator, const cu::xtal::Lattice& lattice) { //use comparator as an input to make this more general
    //make vector of vectors
    vector<vector<int>> output;

    //loop everything
    for(int i=0;i<group.size();i++) {
        vector<int> temp;
        for(int j=0,j<group.size(),j++) {
            product = group[i] * group[j]; //SymOpType must have * defined for multiplication
            
            // unitary compare function (input:product) compare to everything in group and output the label from group
            //cu::sym::CartOpCompare_f comparator(product, 1e-5); //will need a different comparator bc lattice
            //we have something that converts binary to unary comparator - cu/misc/hpp
            //currently works for only point groups
            //findif() returns an iterator to the spot in group
            auto iter = findif(group.begin(), group.end(), comparator(product,1e-5)) 
            int identity = distance(group.begin(),iter); //the mapped index of the new symop

            //output index to output row
            temp.pushback(identity); //
        }
        output.pushback(temp);
    }
    return output; //output is an array of ints corresponding to the group elements
}

void print_nicely(const vector<vector<int>>& mult_table) {
    //print out mult_table - using ptr to save memory
    //iterate through and print nicely
    //print with nice headers on row/col
    //leave as numbers
    /*
    input:5 4 3 2 1
            4 3 2 1 5
            3 2 1 5 4
            2 1 5 4 3
            1 5 4 3 2
    output:
    *| 0 2 3 4 5
    -----------
    0| 5 4 3 2 1
    2| etc
    3|
    4|
    5|
    */

    cout << "*| ";
    for(int k=0; k<mult_table[0].size(); k++) { cout << k << " "; }
    cout << endl << "---";
    for(int k=0; k<mult_table[0].size(); k++) { cout << "--"; }
    cout << endl;
    for(int i=0;i<mult_table.size();i++) {
        cout << i << "| ";
        for(int j=0; j<mult_table[i].size(); j++) {
            cout << mult_table[i][j] << " ";
        }
        cout << endl;
    }
}

void print_raw_output(const vector<vector<int>>& mult_table) {
    for(int i=0;i<mult_table.size();i++) {
    for(int j=0; j<mult_table[i].size(); j++) {
        cout << mult_table[i][j] << " ";
    }
    cout << endl;
    }
}

int main(int argc, char* argv[]) {
    //CLI take in path to group (in form of a vector of CartOps) and a POSCAR/lattice
    CLI::App app;

    //read group from file
    cu::fs::path input_group_path;

    //TODO::actually read in the input_group 
    vector<cu::sym::CartOp> input_group;
    
    //reads lattice
    //TODO::actually read in the lattice
    cu::xtal::Lattice input_lattice;
    
    //make mult table its own function: 
    mult_table = make_mult_table(input_group, cu::sym::CartOpCompare_f comparator, input_lattice);

    //print mult table
    //formatted version w/ headers
    print_very_nicely(mult_table);
    //no headers
    print_raw_output(mult_table);

    return 0;
}