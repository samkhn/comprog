#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static constexpr std::string_view kUsage = R"Usage(Sudoku Solver

  Usage: sudoku-solver.exe C:/path/to/puzzle1
  Generate a solution file as /path/to/puzzle1-solution

  Input format: 9 lines, each line has 9 characters of [0-9],
    where 0 represents `nil`.
  Output format: 9 lines, each line has 9 characters of [1-9].
    Named {input-file}.solution.
)Usage";
const std::size_t kPuzzleSize = 9;

using Row = std::vector<unsigned int>;
using Puzzle = std::vector<Row>;

void Initialize(Puzzle *p)
{
	if (!p) return;
	p->reserve(kPuzzleSize);
	for (std::size_t i = 0; i < kPuzzleSize; ++i)
		p->push_back(Row(kPuzzleSize, 0));
}

// `in` points to a file that contains a 9 by 9 sudoku puzzle.
// `puzzle` points to an initialized puzzle (has had Initialize() called on it).
int Read(std::ifstream& in, Puzzle *puzzle)
{
	if (!puzzle)
		return -1;
	std::size_t row = 0;
	std::size_t column = 0;
	char c;
	int val;
	while (!in.eof()) {
		in >> c;
		val = (int)c - '0';
		if (val < 0 || val > 9) {
			std::cout << "Illegal character in file: " << c << "\n";
			return -1;
		}
		puzzle->at(row).at(column) = val;
		column = (column + 1) % kPuzzleSize;
		if (column == 0) {
			if (row == kPuzzleSize-1) return 0;
			row = (row + 1) % kPuzzleSize;
		}
	}
	return 0;
}

// Assumes puzzle is at least initialized to a 9 by 9 matrix.
int Write(Puzzle *puzzle, std::ostream& out)
{
	if (!puzzle)
		return -1;
	for (std::size_t i = 0; i < kPuzzleSize; ++i) {
		for (std::size_t j = 0; j < kPuzzleSize; ++j)
			out << puzzle->at(i).at(j) << " ";
		out << "\n";
	}
	return 0;
}

// Assumes `in` and `out` are at least initialized.
int Solve(Puzzle *in, Puzzle *out)
{
	if (!in || !out)
		return -1;
	// sdas
	return 0;
}


int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Invalid call to sudoku solver\n" << kUsage;
		return -1;
	}
	std::ifstream in(argv[1]);
	if (!in.is_open()) {
		std::cout << std::format("Failed to open file {0}\n", argv[1]);
		return -1;
	}
	Puzzle p;
	Initialize(&p);
	if (Read(in, &p)) {
		std::cout << std::format("Failed to read input {0}\n", argv[1]);
		return -1;
	}
	Puzzle solution;
	Initialize(&solution);
	if (Solve(&p, &solution)) {
		std::cout << "Could not solve\n";
		return -1;
	}
	std::string out_filepath = std::string(argv[1]) + ".solution";
	std::ofstream out(out_filepath);
	if (Write(&solution, std::cout)) {
		std::cout << std::format("Failed to write output to {0}.\n",
					out_filepath);
		return -1;
	}
	in.close();
	out.close();
	return 0;
}
