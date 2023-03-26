

main: evalExpr.cpp Expr.hpp ../mylibs/Bector/Bector.tpp
	g++ -o main evalExpr.cpp ../mylibs/Bector/Bector.tpp -std=c++20 && ./main