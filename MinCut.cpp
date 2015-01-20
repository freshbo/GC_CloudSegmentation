#include "MinCut.h"
 

int cutIt()
{
	using namespace boost;

	std::cout<<"CUT IT"<<std::endl;
	Graph g; //a graph with 0 vertices
 
	property_map < Graph, edge_reverse_t >::type rev = get(edge_reverse, g);
 
	//ADD NODES TO GRAPH
//	for (int i_point = 0; i_point < cloud->size() + 2; i_point++)
		//cloud->points[i_point] = add_vertex (g);
		//add_vertex(g);

	std::vector< Traits::vertex_descriptor> vertices_;
	Traits::vertex_descriptor vertex_descriptor(0);

	int size = 10000000;
	vertices_.clear ();
	vertices_.resize (size + 2, vertex_descriptor);
	
	for (int i=0;i<size;i++)
	{
		vertices_[i] = add_vertex(g);
	}
	for (int i=0;i<size;i++)
	{
		vertices_[i] = add_vertex (g);
	}
	for (int i=0; i<size;i++)
	{
		AddEdge(vertices_[i],vertices_[i+1],rev, 0.1 ,g);
	}
	Traits::vertex_descriptor source = add_vertex(g);
	Traits::vertex_descriptor sink = add_vertex(g);

	AddEdge(source,vertices_[0],rev,10.5,g);
	AddEdge(vertices_[size],sink,rev,2.4,g);
	
	/*
	Traits::vertex_descriptor v0 = add_vertex(g);
	Traits::vertex_descriptor v1 = add_vertex(g);
	Traits::vertex_descriptor v2 = add_vertex(g);
	Traits::vertex_descriptor v3 = add_vertex(g);

	
	AddEdge(source,v0,rev,10,g);
	AddEdge(sink,v3,rev,10,g);
	AddEdge(v0, v1, rev, 1, g);
	AddEdge(v0, v2, rev, 1, g);
	AddEdge(v1, v3, rev, 1, g);
	AddEdge(v2, v3, rev, 1, g);
	*/
	//find min cut
	double flow = boykov_kolmogorov_max_flow(g, source, sink); // a list of sources will be returned in s, and a list of sinks will be returned in t
	//EdgeWeightType flow = push_relabel_max_flow(g, v0, v3); // a list of sources will be returned in s, and a list of sinks will be returned in t
	//EdgeWeightType flow = edmunds_karp_max_flow(g, v0, v3); // a list of sources will be returned in s, and a list of sinks will be returned in t
 
	std::cout << "Max flow is: " << flow << std::endl;
 
	property_map<Graph, edge_capacity_t>::type
			capacity = get(edge_capacity, g);
	property_map<Graph, edge_residual_capacity_t>::type
			residual_capacity = get(edge_residual_capacity, g);
 
 
	graph_traits<Graph>::vertex_iterator u_iter, u_end;
	graph_traits<Graph>::out_edge_iterator ei, e_end;


	return 0;
}

Traits::edge_descriptor AddEdge(Traits::vertex_descriptor &v1,
	Traits::vertex_descriptor &v2, 
	property_map < Graph, edge_reverse_t >::type &rev, 
	const double capacity, Graph &g)
{
	Traits::edge_descriptor e1 = add_edge(v1, v2, g).first;
	Traits::edge_descriptor e2 = add_edge(v2, v1, g).first;
	put(edge_capacity, g, e1, capacity);
	put(edge_capacity, g, e2, capacity);
 
	rev[e1] = e2;
	rev[e2] = e1;

	return e1;
}