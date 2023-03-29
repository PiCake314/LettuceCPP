

main: evalExpr.cpp Expr.hpp ../Bector/Bector.tpp
	g++ -o main evalExpr.cpp ../Bector/Bector.tpp -std=c++20 && ./main