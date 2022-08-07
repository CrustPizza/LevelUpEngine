/********************************
*								*
*	Material Info.cpp			*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "MaterialInfo.h"
#include <sstream>
#include <fstream>

void MaterialInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_MATERIAL_NAME:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				materialName += temp;

			break;
		}

		case AseToken::TOKENR_MATERIAL_CLASS:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				className += temp;

			break;
		}

		case AseToken::TOKENR_MATERIAL_AMBIENT:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				ambient[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_DIFFUSE:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				diffuse[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_SPECULAR:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				specular[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_SHINE:
		{
			shine = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_SHINESTRENGTH:
		{
			shineStrength = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_TRANSPARENCY:
		{
			transparency = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_WIRESIZE:
		{
			wireSize = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_SHADING:
		{
			shading = temp;

			break;
		}

		case AseToken::TOKENR_MATERIAL_XP_FALLOFF:
		{
			xpFallOff = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_SELFILLUM:
		{
			selfIllumination = stof(temp);

			break;
		}

		case AseToken::TOKENR_MATERIAL_FALLOFF:
		{
			fallOff = temp;

			break;
		}

		case AseToken::TOKENR_MATERIAL_XP_TYPE:
		{
			xpType = temp;

			break;
		}

		case AseToken::TOKENR_MAP_DIFFUSE:
		{
			MapInfo tempMap;

			tempMap.type = MapType::DIFFUSE;
			tempMap.SetData(data);

			maps.push_back(tempMap);

			break;
		}

		case AseToken::TOKENR_MAP_SPECULAR:
		{
			MapInfo tempMap;

			tempMap.type = MapType::SPECULAR;
			tempMap.SetData(data);

			maps.push_back(tempMap);

			break;
		}

		case AseToken::TOKENR_MAP_SHINE:
		{
			MapInfo tempMap;

			tempMap.type = MapType::SHINE;
			tempMap.SetData(data);

			maps.push_back(tempMap);

			break;
		}

		case AseToken::TOKENR_MAP_BUMP:
		{
			MapInfo tempMap;

			tempMap.type = MapType::NORMAL;
			tempMap.SetData(data);

			maps.push_back(tempMap);

			break;
		}

		case AseToken::TOKENR_SUBMATERIAL:
		{
			std::stringstream ss(temp);

			ss >> temp;

			MaterialInfo subMat;

			subMat.SetData(data);

			subMaterial[stoi(temp)] = subMat;

			break;
		}

		}
	}
}