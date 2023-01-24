#include "Precompiled.h"
#include "DFS.h"

bool AI::DFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{
	graph.ResetSearchParam();
	mOpenList.clear();
	mClosedList.clear();

	// add the start node to the open list
	auto node = graph.GetNode(startX, startY);
	node->bOpened = true;
	mOpenList.push_back(node);

	bool found = false;

	//TODO
	//  while end node not reached && open list isn't empty:
	//  	select node N from open list ----> Depend on your startegy
	//  	if node is end
	//  		found = true
	//  	else expand node N :
	//  		if expanded node isn't in open list nor closed list
	//  			add expanded node to open list, set parent
	//  	Add node N to closed list

	auto endNode = graph.GetNode(endX, endY);


	while ((!endNode->bClosed) && (!mOpenList.empty()))
	{
		auto tempNode = mOpenList.back();
		mOpenList.pop_back();

		if (tempNode->column == endX && tempNode->row == endY)
		{
			found = true;
		}
		else
		{
			for (size_t i = 0; i < 8; i++)
			{
				auto nbh = tempNode->neighbors[i];
				if (nbh != nullptr && !nbh->bClosed && !nbh->bOpened)
				{
					mOpenList.push_back(nbh);
					nbh->bOpened = true;
					nbh->parent = tempNode;
				}
			}
		}

		mClosedList.push_back(tempNode);
		tempNode->bClosed = true;
	}

	return found;
}
