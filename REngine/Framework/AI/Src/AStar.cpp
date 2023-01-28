#include "Precompiled.h"
#include "AStar.h"

bool AI::AStar::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCostFunc, GetHeuristics getHeuristicsFunc)
{
	graph.ResetSearchParam();
	mOpenList.clear();
	mClosedList.clear();

	// add the start node to the open list
	auto node = graph.GetNode(startX, startY);
	node->bOpened = true;
	mOpenList.push_back(node);

	bool found = false;

	auto endNode = graph.GetNode(endX, endY);

	if (!endNode)
	{
		return found;
	}

	while ((!endNode->bClosed) && (!mOpenList.empty()))
	{
		auto tempNode = mOpenList.front();
		mOpenList.pop_front();

		if (tempNode->column == endX && tempNode->row == endY)
		{
			found = true;
		}
		else
		{
			for (size_t i = 0; i < 8; i++)
			{
				auto nbh = tempNode->neighbors[i];
				if (nbh == nullptr || nbh->bClosed) { continue; }

				if (!nbh->bOpened)
				{
					nbh->bOpened = true;
					nbh->parent = tempNode;
					nbh->g = tempNode->g + getCostFunc(nbh);
					nbh->h = getHeuristicsFunc(nbh, endNode);
					//TODO
					//Set the cost g
					//neighbor->g = currentnode-> + GetCost(node);
					//insert in the open list
					//need to sort the open list OR insert sorted related to G + H
				}
				//else if (new cost is cheaoer)
				//{
				//	do the edge relaxation
				// updatind the parent and use the new g that is cheaper and then resort the openlist
				//Heuristics in this case do not change
				//}
			}
		}

		tempNode->bClosed = true;
		mClosedList.push_back(tempNode);
	}

	return found;
}
