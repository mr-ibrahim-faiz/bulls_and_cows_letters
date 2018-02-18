#pragma once

#include<vector>
using std::vector;

// gets the user guess from input
vector<char> get_user_guess(const int&);

// checks if the user guess is valid
bool is_guess_valid(const vector<char>&, const int&);

// checks if every element of a vector is alphabetic
bool are_elements_alphabetic(const vector<char>&);

// checks if every element of a vector is unique
bool are_elements_unique(const vector<char>&);

// generates a vector of unique alphabetical characters
vector<char> generate_vector(const int&);

// counts the bulls and cows
vector<int> count_bulls_and_cows(const vector<char>&, const vector<char>&, const int&);

// displays results
void display_results(const vector<int>&);