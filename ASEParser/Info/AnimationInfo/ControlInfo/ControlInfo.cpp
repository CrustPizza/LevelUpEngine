/********************************
*								*
*	Control Info.cpp			*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "ControlInfo.h"
#include <sstream>
#include <fstream>

void ControlInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_CONTROL_POS_SAMPLE:
		{
			std::stringstream ss(temp);

			ControlCoord pos;

			ss >> temp;
			pos.tick = stof(temp);

			for (int i = 0; i < 3; i++)
			{
				ss >> temp;
				pos.r[i] = stof(temp);
			}

			posSample.push_back(pos);

			break;
		}

		case AseToken::TOKENR_CONTROL_ROT_SAMPLE:
		{
			std::stringstream ss(temp);

			ControlCoord rot;

			ss >> temp;
			rot.tick = stof(temp);

			for (int i = 0; i < 4; i++)
			{
				ss >> temp;
				rot.r[i] = stof(temp);
			}

			rotSample.push_back(rot);

			break;
		}

		}
	}
}