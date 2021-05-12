#include <iostream>
#include <vector>
#include <fstream>
#include "casmutils/misc.hpp"
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
//currently works for only point groups

//general template for making mult table
template <typename SymOpType>
//assumes a unitary comparator
vector<vector<int>> make_mult_table(const vector<SymOpType>& group, const cu::xtal::Lattice& lattice) { //use comparator as an input to make this more general
    vector<vector<int>> output; //the multiplication table output

    for(int i=0;i<group.size();i++) {
        vector<int> temp;
        for(int j=0,j<group.size(),j++) {
            product = group[i] * group[j];
            
            /* point groups only
            // unitary compare function (input:product) compare to everything in group and output the label from group
            cu::sym::CartOpCompare_f comparator(product, 1e-5); //will need a different comparator bc lattice
            */
            //binary -> unary comparator (in cu/misc.hpp)
            cu::sym::BinaryCartOpPeriodicCompare_f binary_comp(lattice, 1e-5);
            cu::misc::UnaryComparator_f<cu::sym::BinaryCartOpPeriodicCompare_f> CartOp_unary_comparator(product, tol);
            
            //findif() returns an iterator to the spot in group
            auto iter = findif(group.begin(), group.end(), comparator(product,1e-5)) 
            int identity = distance(group.begin(),iter); //the mapped index of the new symop

            //output index to output row
            temp.pushback(identity);
        }
        output.pushback(temp);
    }
    return output; //output is an array of ints corresponding to the group elements
}

void print_nicely(const vector<vector<int>>& mult_table) {
    //print multiplication table with nice headers on row/col
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
    cu::fs::path input_lattice_path;

    //TODO::actually read in the input_group 
    vector<cu::sym::CartOp> input_group = ;
    
    //reads lattice
    //TODO::actually read in the lattice
    cu::xtal::Lattice input_lattice=cu::xtal::Structure::from_poscar(input_lattice_path);
    
    //make mult table its own function: 
    mult_table = make_mult_table(input_group, cu::sym::CartOpCompare_f comparator, input_lattice);

    //print mult table
    //formatted version w/ headers
    print_very_nicely(mult_table);
    //no headers
    print_raw_output(mult_table);

    return 0;
}