#pragma once

#include "GridBasedGraph.h"
//1h6m
namespace AI
{

	using NodeList = std::list<GridBasedGraph::Node*>;
	using GetCost = std::function<float(const GridBasedGraph::Node*)>;// to get the value from outside of AI

	class Dijkstra
	{
	public:

		//if the node if found return true
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCostFunc);
		const NodeList& GetClosedList()const { return mClosedList; }

	private:

		NodeList mOpenList;
		NodeList mClosedList;
	};
}