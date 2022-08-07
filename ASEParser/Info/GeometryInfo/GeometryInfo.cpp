/********************************
*								*
*	Geometry Info.cpp			*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "GeometryInfo.h"
#include <sstream>
#include <fstream>

void GeometryInfo::SetData(std::ifstream& data)
{
	string temp;
	isSkin = false;

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

		// Node Info
		case AseToken::TOKENR_NODE_TM:
		{
			nodeList[currentNode].SetData(data);

			break;
		}

		// Mesh Info
		case AseToken::TOKENR_MESH:
		{
			meshInfo.SetData(data);

			break;
		}

		// ETC Properties
		case AseToken::TOKENR_PROP_MOTIONBLUR:
		{
			motionBlur = stoi(temp);

			break;
		}

		case AseToken::TOKENR_PROP_CASTSHADOW:
		{
			castShadow = stoi(temp);

			break;
		}

		case AseToken::TOKENR_PROP_RECVSHADOW:
		{
			recvShadow = stoi(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_REF:
		{
			materialRef = stoi(temp);

			break;
		}

		case AseToken::TOKENR_WIREFRAME_COLOR:
		{
			std::stringstream ss(temp);

			for (int i = 0; i < 3; i++)
			{
				ss >> temp;
				wireframeColor[i] = stof(temp);
			}

			break;
		}

		// Animation Info
		case AseToken::TOKENR_TM_ANIMATION:
		{
			animationInfo.SetData(data);

			break;
		}

		case AseToken::TOKENR_BONE_LIST:
		case AseToken::TOKENR_MESH_WVERTEXS:
		{
			boneInfo.SetData(data);
			isSkin = true;

			break;
		}

		}
	}
}