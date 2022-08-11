/********************************
*								*
*	Map Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "MapInfo.h"
#include <sstream>
#include <fstream>

void MapInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_MAP_NAME:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				mapName += temp;

			break;
		}

		case AseToken::TOKENR_MAP_CLASS:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				className += temp;

			break;
		}

		case AseToken::TOKENR_MAP_SUBNO:
		{
			subNumber = stoi(temp);

			break;
		}

		case AseToken::TOKENR_MAP_AMOUNT:
		{
			amount = stof(temp);

			break;
		}

		case AseToken::TOKENR_BITMAP:
		{
			int index = 0;

			while (temp.back() == '\"' || temp.back() == ' ' || temp.back() == '\t')
				temp.pop_back();

			while (temp[index] == '\"' || temp[index] == ' ')
				index++;

			if (index != 0)
				bitmap = temp.substr(index);
			else
				bitmap = temp;

			break;
		}

		case AseToken::TOKENR_MAP_TYPE:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				mapType += temp;

			break;
		}

		case AseToken::TOKENR_UVW_U_OFFSET:
		{
			uOffset = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_V_OFFSET:
		{
			vOffset = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_U_TILING:
		{
			uTiling = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_V_TILING:
		{
			vTiling = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_ANGLE:
		{
			angle = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_BLUR:
		{
			blur = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_BLUR_OFFSET:
		{
			blufOffset = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_NOUSE_AMT:
		{
			noUseAmt = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_NOISE_SIZE:
		{
			noiseSize = stof(temp);

			break;
		}

		case AseToken::TOKENR_UVW_NOISE_LEVEL:
		{
			noiseLevel = stoi(temp);

			break;
		}

		case AseToken::TOKENR_UVW_NOISE_PHASE:
		{
			noisePhase = stof(temp);

			break;
		}

		case AseToken::TOKENR_MAP_GENERIC:
		{
			if (genericMap == nullptr)
				genericMap = new MapInfo;

			genericMap->SetData(data);

			break;
		}

		}
	}
}