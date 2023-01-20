#include "Precompiled.h"
#include "BFS.h"

bool AI::BFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
{

	graph.ResetSearchParam();
	mOpenList.clear();
	mClosedList.clear();

	// add the start node to the open list
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->bOpened = true;

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



	return false;
}
