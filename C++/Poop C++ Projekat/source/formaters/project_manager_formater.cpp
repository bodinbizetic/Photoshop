#include "project_manager_formater.h"

Project_Manager_Formater::Project_Manager_Formater(std::string path_, std::string header_name_, std::string body_name_) 
: path(path_), header_name(header_name_), body_name(body_name_){
	doc = new xml::xml_document<>();
}

void Project_Manager_Formater::store(const PM_Formater_info& toStore) {
	storeHeader(toStore.header);
	storeBody(toStore.body);
	std::ofstream file(path);
	file << *doc;
	file.close();
}

void Project_Manager_Formater::storeHeader(const std::map<std::string, std::string>& header) {
	xml::xml_node<char>* root = doc->allocate_node(xml::node_element, doc->allocate_string(header_name.c_str()));
	doc->append_node(root);
	for (auto i : header) {
		char* name = doc->allocate_string(i.first.c_str());
		char* value = doc->allocate_string(i.second.c_str());
		root->append_attribute(doc->allocate_attribute(name, value));
	}
}

void Project_Manager_Formater::storeBody(const std::vector<std::map<std::string, std::string>>& body) {
	xml::xml_node<char>* root = doc->first_node(header_name.c_str());
	char* body_name = doc->allocate_string(this->body_name.c_str());
	for (auto map_attributes : body) {
		xml::xml_node<char>* attr_node = doc->allocate_node(xml::node_element, body_name);
		root->append_node(attr_node);
		for (auto i : map_attributes) {
			char* name = doc->allocate_string(i.first.c_str());
			char* value = doc->allocate_string(i.second.c_str());
			attr_node->append_attribute(doc->allocate_attribute(name, value));
		}
	}
}

PM_Formater_info Project_Manager_Formater::load() {
	PM_Formater_info info;
	loadDocument();
	info.header = loadHeader();
	info.body = loadBody();
	return info;
}

void Project_Manager_Formater::loadDocument() {
	if (!std::filesystem::exists(path))
		throw PMFormaterFileNotExists();
	
	std::ifstream file(path);
	std::stringstream buff;
	buff << file.rdbuf();
	file.close();
	try {
		doc->parse<0>(doc->allocate_string(buff.str().c_str()));
	}
	catch (...) {
		throw FileCorrupted();
	}
}

std::map<std::string, std::string> Project_Manager_Formater::loadHeader() {
	std::map<std::string, std::string> ret_val;
	xml::xml_node<char>* root = doc->first_node(header_name.c_str());
	for (xml::xml_attribute<char>* attr = root->first_attribute(); attr; attr = attr->next_attribute()) {
		ret_val[attr->name()] = attr->value();
	}

	return ret_val;
}

std::vector<std::map<std::string, std::string>> Project_Manager_Formater::loadBody() {
	std::vector<std::map<std::string, std::string>> ret_val;
	xml::xml_node<char>* root = doc->first_node(header_name.c_str());
	xml::xml_node<char>* body = root->first_node(body_name.c_str());

	for (; body; body = body->next_sibling()) {
		std::map<std::string, std::string> node;
		for (xml::xml_attribute<char>* attr = body->first_attribute(); attr; attr = attr->next_attribute())
			node[attr->name()] = attr->value();
		ret_val.push_back(node);
	}
	return ret_val;
}
