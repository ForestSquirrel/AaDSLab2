#pragma once
#include"list.h"
#include"map.h"
#include"haffman_pair.h"
#include<string>
class HaffmanTree
{
	class Node {
	public:
		Node(haffman_pair<char, int> h_pair = haffman_pair<char, int>(), Node* left = NULL, Node* right = NULL) :h_pair(h_pair), left(left), right(right) {}
		haffman_pair<char, int> h_pair;
		Node* left;
		Node* right;
	};
public:
	~HaffmanTree() {
		this->clear_tree(Top);
	}
	HaffmanTree(string str) {
		Map<char, int>* map_of_chars = new Map<char, int>();
		list_of_chars = new List<haffman_pair<char, int>>();
		for (int i = 0; i < str.size(); i++) {
			if (!map_of_chars->is_in_map(str[i]))  //if the symbol is not in map then add symbol to map else increase the number of entries
				map_of_chars->insert(str[i], 1);
			else
				map_of_chars->add_entry(str[i]);
		}
		list_of_chars = map_of_chars->get_pairs();
		map_of_chars->clear();
		list_of_chars->sort();
		//----------------build haffman tree------------------------
		List<Node>* list_of_haffman_nodes = new List<Node>();
		for (int i = 0; i < list_of_chars->get_size(); i++)
			list_of_haffman_nodes->push_back(Node(list_of_chars->at(i)));
		build_tree(list_of_haffman_nodes);
	}
	List<haffman_pair<char, int>>* get_list_of_chars() {
		return list_of_chars;
	}
	Map<char, string>*& get_codes_map() {
		Map<char, string>* haffman_codes_map = new Map<char, string>();
		string current;
		add_codes(haffman_codes_map, Top, current);
		return haffman_codes_map;
	}
	string decode_string(string& encrypted) {
		string decoded;
		int pos = 0;
		decode(Top, encrypted, decoded, pos);
		return decoded;
	}
private:
	void decode(Node* root, string& encrypted, string& decoded, int& position) {
		if (encrypted.size() > position) {
			while (root->right != NULL && root->left != NULL) {
				if (encrypted[position] == '0')
					root = root->left;
				else
					root = root->right;
				position++;
			}
			decoded += root->h_pair.symbol;
			if (Top->left == NULL && Top->right == NULL)
				position++;
			decode(Top, encrypted, decoded, position);
		}
	}
	void build_tree(List<Node>*& list_of_haffman_nodes) {
		Top = NULL;
		if (list_of_haffman_nodes->get_size() > 1) {
			while (list_of_haffman_nodes->get_size() != 0) {
				Node* current = new Node();
				current->left = new Node(list_of_haffman_nodes->at(0));
				current->right = new Node(list_of_haffman_nodes->at(1));
				current->h_pair.num_of_entry = list_of_haffman_nodes->at(0).h_pair.num_of_entry + list_of_haffman_nodes->at(1).h_pair.num_of_entry;
				list_of_haffman_nodes->pop_front();
				list_of_haffman_nodes->pop_front();
				int i = 0;
				for (; i < list_of_haffman_nodes->get_size() && list_of_haffman_nodes->at(i).h_pair.num_of_entry < current->h_pair.num_of_entry; i++);
				if (list_of_haffman_nodes->get_size() != 0 && list_of_haffman_nodes->get_size() != i)
					list_of_haffman_nodes->insert(*current, i);
				else
					if (list_of_haffman_nodes->get_size() == i && list_of_haffman_nodes->get_size() != 0)
						list_of_haffman_nodes->push_back(*current);
				if (list_of_haffman_nodes->get_size() == 0) {
					Top = current;
				}
			}
		}
		else {
			Top = new Node(haffman_pair<char, int>(list_of_haffman_nodes->at(0).h_pair.symbol, list_of_haffman_nodes->at(0).h_pair.num_of_entry));
		}
	}
	void add_codes(Map<char, string>* haffman_codes_map, Node* root, string current) {
		if (Top->left != NULL && Top->right != NULL) {
			if (root->left != NULL && root->right != NULL) {
				add_codes(haffman_codes_map, root->left, current + '0');
				add_codes(haffman_codes_map, root->right, current + '1');
			}
			else
			{
				haffman_codes_map->insert(root->h_pair.symbol, current);
			}
		}
		else {
			haffman_codes_map->insert(root->h_pair.symbol, current + '0');
		}
	}
	void clear_tree(Node* tree) {
		if (tree != NULL) {
			clear_tree(tree->left);
			clear_tree(tree->right);
			delete tree;
		}
	}
	Node* Top;
	List<haffman_pair<char, int>>* list_of_chars;
};