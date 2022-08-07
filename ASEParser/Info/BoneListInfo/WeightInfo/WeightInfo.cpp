/********************************
*								*
*	Weight Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "WeightInfo.h"
#include <sstream>
#include <fstream>

void WeightInfo::SetData(std::ifstream& data)
{
	string temp;

	while (data.eof() != true)
	{
		data >> temp;

		AseToken tokenNum = AseToken::TOKENR_END;

		if (temp[0] == '*')
			tokenNum = GetToken(temp);
		else if (temp[0] == '}')
			break;
		else
			continue;

		std::getline(data, temp);

		switch (tokenNum)
		{

		case AseToken::TOKENR_BONE_BLENGING_WEIGHT:
		{
			std::stringstream ss(temp);

			WeightData weight;

			ss >> temp;
			weight.index = stoul(temp);

			ss >> temp;
			weight.weight = stof(temp);

			weights.push_back(weight);

			break;
		}

		}
	}
}