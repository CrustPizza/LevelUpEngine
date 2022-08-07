/********************************
*								*
*	Texture Info.cpp			*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "TextureInfo.h"
#include <sstream>
#include <fstream>

void TextureInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_MESH_TVERT:
		{
			std::stringstream ss(temp);

			TVertex tVer;

			ss >> temp;

			for (int i = 0; i < 3; i++)
			{
				ss >> temp;
				tVer.r[i] = stof(temp);
			}

			tVertex.push_back(tVer);

			break;
		}

		}
	}
}