#include "Precompiled.h"
#include "Dijkstra.h"


bool AI::Dijkstra::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCostFunc)
{
	graph.ResetSearchParam();
	mOpenList.clear();
	mClosedList.clear();

	// add the start node to the open list
	auto nodeA = graph.GetNode(startX, startY);
	nodeA->bOpened = true;
	nodeA->g = 0.0f;
	nodeA->parent = nullptr;
	mOpenList.push_back(nodeA);

	bool found = false;

	auto endNode = graph.GetNode(endX, endY);

	if (!endNode)
	{
		return found;
	}

	while ((!endNode->bClosed) && (!mOpenList.empty()))
	{
		auto currentNode = mOpenList.front();
		mOpenList.pop_front();

		if (currentNode->column == endX && currentNode->row == endY)
		{
			found = true;
		}
		else
		{
			for (size_t i = 0; i < 8; i++)
			{
				auto nbr = currentNode->neighbors[i];
				if (nbr == nullptr || nbr->bClosed){continue;}

				if (!nbr->bOpened)
				{
					nbr->bOpened = true;
					nbr->parent = currentNode;
					//TODO
					//Set the cost g
					nbr->g = currentNode->g + getCostFunc(nbr);

					//std::cout << getCostFunc(nbr)<<std::endl;

					std::list<GridBasedGraph::Node*>::iterator it;
					for (it = mOpenList.begin(); it != mOpenList.end(); ++it)
					{
						auto t = *it;
						if (t->g > nbr->g)
						{
							break;
						}
					}
					mOpenList.insert(it, nbr);


					//insert in the open list
					//need to sort the open list OR insert sorted
				}
				else if (nbr->g > currentNode->g + getCostFunc(nbr))//if cost is cheaper
				{
				//	do the edge relaxation
				// updatind the parent and use the new g that is cheaper and then resort the openlist

					nbr->g = currentNode->g + getCostFunc(nbr);
					nbr->parent = currentNode;
				}
			}
		}

		currentNode->bClosed = true;
		mClosedList.push_back(currentNode);

	}//end while

	return found;
}
