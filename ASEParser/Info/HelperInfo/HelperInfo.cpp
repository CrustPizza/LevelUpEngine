/********************************
*								*
*	Helper Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "HelperInfo.h"
#include <sstream>
#include <fstream>

void HelperInfo::SetData(std::ifstream& data)
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

		// Helper Name
		case AseToken::TOKENR_HELPER_CLASS:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				helperName += temp;

			break;
		}

		// Node Info
		case AseToken::TOKENR_NODE_TM:
		{
			nodeList[currentNode].SetData(data);

			break;
		}

		// Bounding Box Min
		case AseToken::TOKENR_BOUNDINGBOX_MIN:
		{
			std::stringstream ss(temp);

			for (int i = 0; i < 3; i++)
			{
				ss >> temp;
				boundingBoxMin[i] = stof(temp);
			}

			break;
		}

		// Bounding Box Max
		case AseToken::TOKENR_BOUNDINGBOX_MAX:
		{
			std::stringstream ss(temp);

			for (int i = 0; i < 3; i++)
			{
				ss >> temp;
				boundingBoxMax[i] = stof(temp);
			}

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