%: %.cpp
	g++ -std=c++14 -g -Wall -Werror -Wextra -pedantic $< -o $@