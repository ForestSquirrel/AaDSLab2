#include<iostream>
#include"Map.h"
#include<string>
#include"haffman_algo.h"
using namespace std;



int main() {
	string str;
	string encrypted;
	setlocale(LC_ALL, "RU");
	cout << "������� ������ ��� �����������: ";
	getline(cin, str);
	HaffmanTree* haffmanTree = new HaffmanTree(str);
	Map<char, string>* haffman_codes_map = haffmanTree->get_codes_map();
	List<haffman_pair<char, int>>* list_symbol = haffmanTree->get_list_of_chars();
	cout << "������� �����:" << endl;
	cout << "������ <---> ���" << endl;
	for (int i = 0; i < list_symbol->get_size(); i++)
		cout << "   " << list_symbol->at(i).symbol << "   <---> " << haffman_codes_map->find(list_symbol->at(i).symbol) << " <---> ��������� � ������: " << list_symbol->at(i).num_of_entry << endl;
	cout << "������ ������: " << str << endl;
	for (int i = 0; i < str.size(); i++)
		encrypted += haffman_codes_map->find(str[i]);
	cout << "����� ������: " << encrypted << endl;
	string decoded = haffmanTree->decode_string(encrypted);
	cout << "������ ��������������(��������) ������ = " << decoded.size() * 8 << " ���" << endl;
	cout << "������ �������������� ������ = " << encrypted.size() << " ���" << endl;
	cout << "����������� ������: x" << (((double)(decoded.size() * 8) / (encrypted.size()))) << endl;
	delete haffmanTree;
	return 0;
}