/********************************
*								*
*	Node Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "NodeInfo.h"
#include <sstream>
#include <fstream>

void NodeInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_INHERIT_POS:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				inheritPosition[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_INHERIT_ROT:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				inheritRotation[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_INHERIT_SCL:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				inheritScale[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_TM_ROW0:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				transform[0][i] = stof(temp);

			transform[0][3] = 0.0f;

			break;
		}

		case AseToken::TOKENR_TM_ROW1:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				transform[1][i] = stof(temp);

			transform[1][3] = 0.0f;

			break;
		}

		case AseToken::TOKENR_TM_ROW2:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				transform[2][i] = stof(temp);

			transform[2][3] = 0.0f;

			break;
		}

		case AseToken::TOKENR_TM_ROW3:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				transform[3][i] = stof(temp);

			transform[3][3] = 1.0f;

			break;
		}

		case AseToken::TOKENR_TM_POS:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				position[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_TM_ROTAXIS:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				rotation[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_TM_ROTANGLE:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				rotationAngle = stof(temp);

			break;
		}

		case AseToken::TOKENR_TM_SCALE:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				scale[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_TM_SCALEAXIS:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				scaleAxis[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_TM_SCALEAXISANG:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				scaleAxisAngle = stof(temp);

			break;
		}

		}
	}
}