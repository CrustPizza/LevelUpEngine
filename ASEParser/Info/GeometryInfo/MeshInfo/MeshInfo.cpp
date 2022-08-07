/********************************
*								*
*	Mesh Info.cpp				*
*								*
*	Created : 2022/07/06		*
*	Updated : 2022/07/06		*
*********************************/

#include "MeshInfo.h"
#include <sstream>
#include <fstream>

void MeshInfo::SetData(std::ifstream& data)
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

		case AseToken::TOKENR_TIMEVALUE:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				timeValue = stof(temp);

			break;
		}

		case AseToken::TOKENR_MESH_NUMVERTEX:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				vertexInfo.verticesSize = stoi(temp);

			break;
		}

		case AseToken::TOKENR_MESH_NUMFACES:
		{
			std::stringstream ss(temp);

			while (ss >> temp)
				faceInfo.facesSize = stoi(temp);

			break;
		}

		case AseToken::TOKENR_MESH_NUMTVERTEX:
		{

			break;
		}

		case AseToken::TOKENR_MESH_NUMTVFACES:
		{

			break;
		}

		case AseToken::TOKENR_MESH_NUMCVERTEX:
		{

			break;
		}

		case AseToken::TOKENR_MESH_NUMCVFACES:
		{

			break;
		}

		case AseToken::TOKENR_MESH_VERTEX_LIST:
		{
			vertexInfo.SetData(data);

			break;
		}

		case AseToken::TOKENR_MESH_FACE_LIST:
		case AseToken::TOKENR_MESH_TFACELIST:
		case AseToken::TOKENR_MESH_CFACELIST:
		{
			faceInfo.SetData(data);

			break;
		}

		case AseToken::TOKENR_MESH_TVERTLIST:
		{
			textureInfo.SetData(data);

			break;
		}

		case AseToken::TOKENR_MESH_CVERTLIST:
		{
			colorInfo.SetData(data);

			break;
		}

		case AseToken::TOKENR_MESH_NORMALS:
		{
			normalInfo.SetData(data);

			break;
		}

		}
	}
}