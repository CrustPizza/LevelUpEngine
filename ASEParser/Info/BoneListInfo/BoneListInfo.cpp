/********************************
*								*
*	Bone List Info.cpp			*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "BoneListInfo.h"
#include <sstream>
#include <fstream>

void BoneListInfo::SetData(std::ifstream& data)
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

		// Bone Info
		case AseToken::TOKENR_BONE:
		{
			std::stringstream ss(temp);

			ss >> temp;

			unsigned int index = stoul(temp);

			if (boneList.size() <= index)
				boneList.resize(index + 1);

			boneList[index].SetData(data);

			break;
		}

		// Weight Info
		case AseToken::TOKENR_MESH_WEIGHT:
		{
			std::stringstream ss(temp);

			ss >> temp;

			unsigned int index = stoul(temp);

			if (weightList.size() <= index)
				weightList.resize(index + 1);

			weightList[index].SetData(data);

			break;
		}

		}
	}
}