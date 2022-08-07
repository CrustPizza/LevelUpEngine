/********************************
*								*
*	Bone Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "BoneInfo.h"
#include <sstream>
#include <fstream>

void BoneInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_BONE_NAME:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				boneName += temp;

			break;
		}

		}
	}
}
