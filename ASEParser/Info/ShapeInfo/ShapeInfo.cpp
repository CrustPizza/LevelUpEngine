/********************************
*								*
*	Shape Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "ShapeInfo.h"
#include <sstream>
#include <fstream>

void ShapeInfo::SetData(std::ifstream& data)
{
	string temp;

	while (data.eof() != true)
	{
		data >> temp;

		AseToken tokenNum = AseToken::TOKENR_END;

		if (temp[0] == '*')
			tokenNum = static_cast<AseToken>(GetToken(temp));
		else if (temp[0] == '}')
			break;
		else
			continue;

		std::getline(data, temp);

		switch (tokenNum)
		{
		// Target Name
		case AseToken::TOKENR_NODE_NAME:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				currentNode += temp;

			break;
		}

		// Parent Name
		case AseToken::TOKENR_NODE_PARENT:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				parentNode += temp;

			break;
		}

		// Node Info
		case AseToken::TOKENR_NODE_TM:
		{
			nodeList[currentNode].SetData(data);

			break;
		}

		// Animation Info
		case AseToken::TOKENR_TM_ANIMATION:
		{
			animationInfo.SetData(data);

			break;
		}

		}
	}
}