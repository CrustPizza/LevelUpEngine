/********************************
*								*
*	Material List Info.cpp		*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "MaterialListInfo.h"
#include <sstream>
#include <fstream>

void MaterialListInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_MATERIAL_COUNT:
		{

			break;
		}

		case AseToken::TOKENR_MATERIAL:
		{
			std::stringstream ss(temp);

			ss >> temp;

			materials[stoi(temp)].SetData(data);

			break;
		}

		}
	}
}