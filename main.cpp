#include "Conversion.hpp"
#include "kdtree.hpp"
#include "Point.hpp"
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>

typedef int32_t s32;
typedef int64_t s64;

void printErrorFileFormat();

int main(int argc, char** argv)
{
	using namespace std;
	
	s32 count = 0;
	string str = "";
	std::list<Point<s64>> points(0);
	
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " <filename>" << endl;
		return EXIT_FAILURE;
	}
	
	ifstream inputFile(argv[1]);
	
	if (!inputFile.good()) {
		cerr << "Couldn't open input file: " << argv[1] << endl;
		return EXIT_FAILURE;
	}
	
	inputFile >> str;
	try {
		count = stringToNumber<s32>(str);
	} catch (...) {
		printErrorFileFormat();
		return EXIT_FAILURE;
	}
	
	while (inputFile >> str) {
		try {
			string lhs = str.substr(0, str.find(','));
			string rhs = str.substr(str.find(',')+1);
			s64 x = stringToNumber<s64>(lhs);
			s64 y = stringToNumber<s64>(rhs);
			Point<s64> p(x,y);
			points.push_back(p);
			
			cout << "x: " << x << '\n';
			cout << "y: " << y << '\n' << endl;
		} catch (...) {
			cerr << "Couldn't convert number.\n" << endl;
			printErrorFileFormat();
			return EXIT_FAILURE;
		}
	}
	
	Kdtree<Point<s64>> kdtree;
	kdtree.buildTree(points);
	Point<s64> test(2,2);
	kdtree.nearestNeighbor(test, 3);
	return EXIT_SUCCESS;
}

void printErrorFileFormat()
{
	using namespace std;
	cerr << "File formating:\n";
	cerr << "<PointCount>\n";
	cerr << "<X_1>,<Y_1>\n";
	cerr << "<X_2>,<Y_2>\n";
	cerr << "...\n";
	cerr << "<X_n>,<Y_n>" << endl;
}
