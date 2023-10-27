# bash functions for competitive programming

# Usage (assuming problem1.cpp exists in current directory)
# $ cpcc problem1
cpcc() {
      g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -Wconversion -o $1 $1.cpp;
}

# Usage (assuming problem1.cpp exists in current directory)
# $ cpr problem1
cpr() {
      cpcc $1 && ./$1;
      rm $1;
}
