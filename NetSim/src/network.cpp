#include "network.h"
#include "random.h"

void Network :: resize (const size_t& new_size) {
	values.clear();
	for (size_t i(0); i < new_size; ++i) {
	values.push_back(RNG.normal());
	}
}

size_t Network :: size() const {
	return values.size();
}

size_t Network :: set_values (const std::vector<double>& new_values) {
	values.clear();
	values = new_values;
	return values.size();
}

double Network :: value(const size_t& n) const {
	return values[n];
}

size_t Network :: degree(const size_t& n) const {
	std::vector<size_t> counteur; 
	for (auto element : links) {
		if (element.first == n) {
			counteur.push_back(n);
		}
	}
	return counteur.size();		 
}

std::vector<size_t> Network :: neighbors(const size_t& hint) const {
	std::vector<size_t> neighbors;
	for (auto neighbor : links) {
		if (neighbor.first == hint)  { 
			neighbors.push_back(neighbor.second);
			}
	}
	return neighbors;	
}

std::vector<double> Network :: sorted_values() const {
	std::vector<double> values_copy(values);
	std::sort(values_copy.begin(), values_copy.end());
	std::reverse(values_copy.begin(), values_copy.end());
	return values_copy;
}

size_t Network :: random_connect(const double& n) {
		links.clear();
		size_t links_nb(0);
	for (size_t i(0); i<values.size(); ++i){
		bool link_creation;
		links_nb = RNG.poisson(n);
		for (size_t j(1); j <= links_nb; ++j){
			size_t counter(0);
			do { 
				link_creation = add_link(i, RNG.uniform_double(0,values.size()));
				++counter;
			} while (!link_creation and counter < (size()-1));
		}
	}
	return (links.size() / 2 );
}

bool Network :: add_link(const size_t& node1, const size_t& node2) {
	if ((node1 != node2) and (node1 < values.size()) and (node2 < values.size())) {
		for (auto nodes : links) {
			if ((nodes.first == node1) and (nodes.second == node2)) {
				return false;
			}
		}
	links.insert(std::make_pair(node1, node2));
	links.insert(std::make_pair(node2, node1));
	return true;
	}
	else {
		return false; 
	}	 
} 	
