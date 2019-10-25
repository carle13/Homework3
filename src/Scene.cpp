#include "Scene.h"
#include <fstream>
#include "ShaderEyelight.h"
#include "ShaderPhong.h"

#include "PrimTriangle.h"
#include "PrimSphere.h"

using namespace std;

void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	// --- PUT YOUR CODE HERE ---
	vector<Vec3f> vertices;
	string face = "";
	string vert = "";
	string currLine = "";
	ifstream file(fileName);

	if (!file)
	{
		//end execution because file couldn't be opened
		return;
	}

	while (!file.eof())
	{
		getline(file, currLine);

		if (currLine[0] == 'v')
		{
			Vec3f vertex;
			istringstream(currLine) >> vert >> vertex[0] >> vertex[1] >> vertex[2];
			for (int i = 0; i < 3; i++)
			{
				vertex[i] *= 100.0f;
			}
			vertices.push_back(vertex);
		}
		else if (currLine[0] == 'f')
		{
			int x = 0;
			int y = 0;
			int z = 0;
			istringstream(currLine) >> face >> x >> y >> z;
			Add(make_shared<CPrimTriangle>(vertices[x - 1], vertices[y - 1], vertices[z - 1], pShader));
		}
	}
	file.close();

	std::cout << "Finished Parsing" << std::endl;
}

