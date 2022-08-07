/********************************
*								*
*	Normal Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "NormalInfo.h"
#include <sstream>
#include <fstream>

void NormalInfo::SetData(std::ifstream& data)
{
	string temp;
	int index = 0;

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

		case AseToken::TOKENR_MESH_VERTEXNORMAL:
		{
			std::stringstream ss(temp);

			ss >> temp;
			normals.back().vertexNormal[index][0] = stoul(temp);

			for (int i = 1; i < 4; i++)
			{
				ss >> temp;
				normals.back().vertexNormal[index][i] = stof(temp);
			}

			index++;

			break;
		}

		case AseToken::TOKENR_MESH_FACENORMAL:
		{
			std::stringstream ss(temp);

			Normal normal;

			ss >> temp;
			normal.faceNormal[0] = stoul(temp);

			for (int i = 1; i < 4; i++)
			{
				ss >> temp;
				normal.faceNormal[i] = stof(temp);
			}

			index = 0;
			normals.push_back(normal);

			break;
		}

		}
	}
}