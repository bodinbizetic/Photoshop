#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <iostream>
#define _TEST_
#include "formater_pam.h"
#include "menu_main.h"
#include "utilities.h"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using std::cout;
using std::endl;


using namespace rapidxml;
void xmlTest() {
    xml_document<> doc;
    std::ofstream file_stored("xml_file.xml");
    xml_node<>* root = doc.allocate_node(node_element, "Project");
    root->append_attribute(doc.allocate_attribute("Name", "Hello"));
    doc.append_node(root);

    xml_node<>* layers = doc.allocate_node(node_element, "Layers");
    xml_node<>* layer = doc.allocate_node(node_element, "Layer");
    layer->append_attribute(doc.allocate_attribute("name", "Jej name"));
    layer->append_attribute(doc.allocate_attribute("path", "\\googlee"));
    layer->append_attribute(doc.allocate_attribute("opacity", "100"));

    layers->append_node(layer);
    root->append_node(layers);

    
    file_stored << doc;
    file_stored.close();
    doc.clear();

}

int main(int argc, char const *argv[])
{
    Menu &m = *new Menu_Main();
    m.start();
    delete &m;
    /*Formater& g = *Formater::getFormater("C:\\Users\\Dinbo\\Desktop\\temp\\sample_640426.pam");
    Formater& f = *Formater::getFormater("C:\\Users\\Dinbo\\Desktop\\temp\\copy2.bmp");*/
    // f.load();
    /*auto p = f.load();
    auto dim = f.Dimensions();
    consoleDraw(p, dim);
    g.store(p, dim);*/
    //xmlTest();
    
    // system("pause");
    return 0;
}