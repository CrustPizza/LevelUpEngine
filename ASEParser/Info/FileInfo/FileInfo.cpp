/********************************
*								*
*	File Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "FileInfo.h"
#include <fstream>
#include <sstream>

void FileInfo::SetData(std::ifstream& data, AseToken type)
{
	string temp;

	std::getline(data, temp);

	switch (type)
	{

	case AseToken::TOKENR_3DSMAX_ASCIIEXPORT:
	{
		std::stringstream ss(temp);
		
		while (ss >> temp)
			exportVer = stoi(temp);

		break;
	}

	case AseToken::TOKENR_COMMENT:
	{
		std::stringstream ss(temp);

		while (ss >> temp)
			comment += temp;

		break;
	}

	}
}