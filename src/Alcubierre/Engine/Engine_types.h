#pragma once
#include <stdlib.h>

namespace ALCBE
{

	struct Vector3D
	{
		float x;
		float y;
		float z;
	};

	struct Node_3DTransform
	{
		Vector3D translation;
		Vector3D rotation;
		Vector3D scale;
	};

	class Node_Base
	{
		Node_3DTransform transform;

	};

	class SceneNode
	{

	};

	class Node_List
	{
		SceneNode* addNode(SceneNode _node);
		bool removeNode(SceneNode* _node);
		std::vector<SceneNode*> listNodes();
	};

	
}