#pragma once

#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boykov_kolmogorov_max_flow.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

using namespace boost;

	typedef int EdgeWeightType;

	typedef adjacency_list_traits < vecS, vecS, directedS > Traits;
	typedef adjacency_list < vecS, vecS, directedS,
		property < vertex_name_t, std::string,
		property < vertex_index_t, long,
			property < vertex_color_t, boost::default_color_type,
			property < vertex_distance_t, long,
				property < vertex_predecessor_t, Traits::edge_descriptor > > > > >,
 
		property < edge_capacity_t, EdgeWeightType,
		property < edge_residual_capacity_t, EdgeWeightType,
			property < edge_reverse_t, Traits::edge_descriptor > > > > Graph;
 
	int cutIt();

	Traits::edge_descriptor AddEdge(Traits::vertex_descriptor &v1,
									Traits::vertex_descriptor &v2,
									property_map < Graph, edge_reverse_t >::type &rev,
									const double capacity,
									Graph &g);



