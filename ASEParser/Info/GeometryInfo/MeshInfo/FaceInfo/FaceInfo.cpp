/********************************
*								*
*	Face Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "FaceInfo.h"
#include <fstream>
#include <sstream>

void FaceInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_MESH_FACE:
		{
			std::stringstream ss(temp);

			faces.push_back({});

			for (int i = 0; i < 4; i++)
			{
				ss >> temp;

				faces.back().index[i] = stoul(temp);
				ss >> temp;
			}

			while (temp[0] != '*')
				ss >> temp;

			// smoothing
			ss >> temp;

			if (temp[0] != '*')
			{
				faces.back().smoothing = stoi(temp);

				while (temp[0] != '*')
					ss >> temp;
			}

			// Material ID
			ss >> temp;

			if (temp[0] != '*')
				faces.back().materialID = stoi(temp);

			break;
		}

		case AseToken::TOKENR_MESH_TFACE:
		{
			std::stringstream ss(temp);

			ss >> temp;

			unsigned int index = stoul(temp);
			faces[index].tIndex[0] = index;

			for (int i = 0; i < 3; i++)
			{
				ss >> temp;
				faces[index].tIndex[i + 1] = stoul(temp);
			}

			break;
		}

		case AseToken::TOKENR_MESH_CFACE:
		{

			break;
		}

		case AseToken::TOKENR_MESH_SMOOTHING:
		{
			break;
		}

		case AseToken::TOKENR_MESH_MTLID:
		{
			break;
		}

		}
	}
}