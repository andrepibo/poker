#pragma once
#include <iostream>
#include <string>

#include "poker_input.hpp"
#include "poker_output.hpp"
#include "solver.hpp"


class PokerApplication
{
public:
	void run()
	{
		while(true)
		{
			if(std::cin.eof())
				break;

			std::string strInput;
			std::getline(std::cin, strInput);			

			PokerInput input(strInput);

			if(!input.isValid())
			{
				input.printReason();
				continue;
			}

			Solver solver(input);
			PokerOutput output = solver.solve();
			output.print();
		}
	}
};