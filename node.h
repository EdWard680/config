#ifndef _NODE_H_
#define _NODE_H_

#include <map>
#include <string>

namespace config
{

template<class T,
		template<class Key,
				class Value,
				class Compare = std::less<Key> > NodeMap = std::map,
		template<class Key,
				class Value,
				class Compare = std::less<Key> > LeafMap = NodeMap>,
		class K = std::string>
class Node
{
public:
	using data_t = T;
	using key_t = K;
	using self_t = Node<T, NodeMap, LeafMap, K>;
	using node_map_t = NodeMap<key_t, self_t>;
	using leaf_map_t = LeafMap<key_t, data_t>;
	
public:
	Node() = default;
	
	Node(const Node&) = default;  // expensive
	Node& operator= (const Node&) = default;
	
	Node(Node&&) = default;
	Node& operator= (Node&&) = default;
	
	~Node() = default;
	
public:
	// perfectly forwards argument to access operators
	template<class U>
	self_t& operator[] (U&& key) {return children_[std::forward<U>(key)];}
	
	template<class U>
	const self_t& operator[] (U&& key) const
	{return children_[std::forward<U>(key)];}
	
	template<class U>
	data_t& operator() (U&& key) {return leaves_[std::forward<U>(key)];}
	
	template<class U>
	const data_t& operator() (U&& key) const
	{return leaves_[std::forward<U>(key)];}
	
private:
	node_map_t children_;
	leaf_map_t leaves_;
};

}


#endif /* _NODE_H_ */
