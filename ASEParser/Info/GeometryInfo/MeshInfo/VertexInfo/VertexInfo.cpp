/********************************
*								*
*	Vertex Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "VertexInfo.h"
#include <sstream>
#include <fstream>

void VertexInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_MESH_VERTEX:
		{
			std::stringstream ss(temp);

			Vertex vertex;

			vertex.next = -1;

			for (int i = 0; i < 4; i++)
			{
				ss >> temp;
				vertex.r[i] = stof(temp);
			}

			vertices.push_back(vertex);

			break;
		}

		}
	}
}