#include "Precompiled.h"
#include "AStar.h"

//http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html

bool AI::AStar::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCostFunc, GetHeuristics getHeuristicsFunc)
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
				if (nbr == nullptr || nbr->bClosed) { continue; }

				if (!nbr->bOpened)
				{
					nbr->bOpened = true;
					nbr->parent = currentNode;
					//Set the cost g
					nbr->g = currentNode->g + getCostFunc(nbr);
					nbr->h = getHeuristicsFunc(nbr, endNode);

					std::list<GridBasedGraph::Node*>::iterator it;
					for (it = mOpenList.begin(); it != mOpenList.end(); ++it)
					{
						auto t = *it;
						if ((t->g + t->h) > (nbr->g + nbr->h))
						{
							break;
						}
					}
					mOpenList.insert(it, nbr);

					//insert in the open list
					//need to sort the open list OR insert sorted
				}
				else if (nbr->g  > currentNode->g + getCostFunc(nbr))//if cost is cheaper
				{
					//	do the edge relaxation
					// updatind the parent and use the new g that is cheaper and then resort the openlist

					nbr->g = currentNode->g + getCostFunc(nbr);
					//nbr->h = currentNode->h;
					nbr->parent = currentNode;
					//mOpenList.sort();
				}
			}
		}

		currentNode->bClosed = true;
		mClosedList.push_back(currentNode);

	}//end while

	return found;
}
