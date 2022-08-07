/********************************
*								*
*	Animation Info.cpp			*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "AnimationInfo.h"
#include <fstream>

void AnimationInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_CONTROL_POS_TRACK:
		case AseToken::TOKENR_CONTROL_ROT_TRACK:
		{
			controlInfo.SetData(data);

			break;
		}

		}
	}
}