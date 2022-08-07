/********************************
*								*
*	Scene Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "SceneInfo.h"
#include <sstream>
#include <fstream>

void SceneInfo::SetData(std::ifstream& data)
{
	string temp;

	while (data.eof() != true)
	{
		data >> temp;

		AseToken tokenNum = AseToken::TOKENR_END;

		if (temp[0] == '*')
			tokenNum = static_cast<AseToken>(GetToken(temp));
		else if (temp[0] == '}')
			break;
		else
			continue;

		std::getline(data, temp);

		switch (tokenNum)
		{

		case AseToken::TOKENR_SCENE_FILENAME:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				sceneName += temp;

			break;
		}

		case AseToken::TOKENR_SCENE_FIRSTFRAME:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				firstFrame = stoi(temp);

			break;
		}

		case AseToken::TOKENR_SCENE_LASTFRAME:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				LastFrame = stoi(temp);

			break;
		}

		case AseToken::TOKENR_SCENE_FRAMESPEED:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				frameSpeed = stoi(temp);

			break;
		}

		case AseToken::TOKENR_SCENE_TICKSPERFRAME:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				tick = stoi(temp);

			break;
		}

		case AseToken::TOKENR_SCENE_BACKGROUND_STATIC:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				bgStatic[i] = stof(temp);

			break;
		}

		case AseToken::TOKENR_SCENE_AMBIENT_STATIC:
		{
			std::stringstream ss(temp);

			for (int i = 0; ss >> temp; i++)
				ambientStatic[i] = stof(temp);

			break;
		}

		}
	}
}