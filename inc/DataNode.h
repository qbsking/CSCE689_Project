#include <vector>

class DataNode
{
public:
	DataNode()
	{
		parent = nullptr;
	}

	DataNode *parent; 
	int reward;
	int types[3];
	int agents[2];
	std::vector<int> data;

	~DataNode(){};

};