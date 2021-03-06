#include "stdafx.h"

#include<iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::streamsize;

#include<limits>
using std::numeric_limits;

#include<stdexcept>
using std::exception;
using std::runtime_error;

#include<cctype>
using std::isalpha;

#include<algorithm>
using std::random_shuffle;

#include<chrono>
using std::chrono::system_clock;

#include "bulls_and_cows_letters.h"

// gets the user guess from input
vector<char> get_user_guess(const int& n = 4)
// reads the user guess from input (e.g. 1fg2)
// attempts to make a vector of n characters out of it and returns it
// returns an empty vector if it fails to read n characters or
// if the input is considered invalid (e.g. contains spaces as in "1 f g   2")
{
	vector<char> vec;

	while(cin.peek() != '\n' && !isspace(cin.peek())) {
		char c { '?' };
		cin >> c;
		if (cin)
			vec.push_back(c);
	}

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (vec.size() != n)
		vec.clear();

	return vec;
}

// checks if the user guess is valid
bool is_guess_valid(const vector<char>& guess, const int& n = 4) 
// checks if a guess is valid that is:
// - its size is n
// - its elements are alphabetic
// - its elements are unique
{
	return guess.size() == n && are_elements_alphabetic(guess) && are_elements_unique(guess);
}

// checks if every element of a vector is alphabetic
bool are_elements_alphabetic(const vector<char>& vec) 
// checks if every element of a vector of char is alphabetic
// returns true if it is the case
// returns false otherwise
{
	for (char c : vec)
		if (!isalpha(c))
			return false;
	return true;
}

// checks if every element of a vector is unique
bool are_elements_unique(const vector<char>& vec)
// checks if elements of a vector are unique
// returns true if it is the case
// returns false otherwise
{
	for (char c : vec) {
		int count { 0 };
		for (char i : vec)
			if (i == c)
				++count;
		if (count > 1)
			return false;
	}
	return true;
}

// generates a vector of unique alphabetical characters
vector<char> generate_vector(const int& n = 4) 
// generates a vector of n unique letters (e.g. milk)
// n must be greater or equal to 4 and less than 27
// returns a vector of n elements
{
	if (n > 26)
		throw runtime_error("unable to generate vector: invalid argument.");

	unsigned seed = (unsigned) system_clock().now().time_since_epoch().count();
	srand(seed);

	vector<char> vec = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	random_shuffle(vec.begin(), vec.end());
	vec.resize(n);
	if (vec.size() != n)
		throw runtime_error("unable to generate vector: wrong size.");
	return vec;
}

// counts the bulls and cows
vector<int> count_bulls_and_cows(const vector<char>& chosen, const vector<char>& guess, const int& n = 4) 
// compares two vectors and counts the bulls and cows
// the vectors must be of the same size
// returns a vector of int containing the results
{
	if (chosen.size() != guess.size())
		throw runtime_error("invalid arguments: sizes don't match.");
	vector<int> results(2, 0);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if(chosen[i] == guess[j])
				if (i == j)
					++results[0];
				else
					++results[1];
	if (results.size() != 2)
		throw runtime_error("invalid output: wrong size.");
	return results;
}

// displays results
void display_results(const vector<int>& results) 
// displays the results of the bulls and cows game
// the argument is a vector of int containing two numbers: the number of bulls and the number of cows
{
	if (results.size() != 2)
		throw runtime_error("unable to display results: invalid argument.");
	cout << results[0] << ((results[0] > 1) ? " bulls" : " bull") << " and " << results[1] << ((results[1] > 1) ? " cows. " : " cow.") << endl;
}

int main()
try
{
	// fixes the number of characters to guess
	const int n { 4 };

	while (true) {
		vector<char> chosen = generate_vector(n); // a vector of unique characters is randomly chosen

		//// debug: displays word
		//for (char c : chosen)
		//	cout << c;
		//cout << endl;

		cout << "A word of " << n << " unique characters has been chosen !" << endl;
		cout << "What is your guess?";

		while (true) {
			cout << "\n> ";
			vector<char> guess = get_user_guess(n); // gets the user guess from input

			//if (guess.size() != n)
			//	throw runtime_error("invalid guess: size.");

			if (is_guess_valid(guess, n)) {

				if (guess == chosen) {
					cout << "You got it !" << endl;
					cout << endl;
					break;
				}
				else {
					//cout << "You guessed wrong." << endl;
					vector<int> results = count_bulls_and_cows(chosen, guess);
					display_results(results);
				}
					
			}
			else
				cout << "invalid input: Try again." << endl;
		}
	}

    return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Error: unknown exception caught." << endl;
	return 2;
}
