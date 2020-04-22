#include <set>
#include <math.h>
#include <algorithm>

#include "formater_bmp.h"
#include "image.h"
#include "simple_operation.h"
#include "rapidxml_print.hpp"

Image::Image(std::string path) : project_manager(path) {

}

Image::~Image() {
    
}

void Image::useOperation(std::pair<int, int> op_id_arg) {
    Operation* operation_to_use = all_operations.getOperation(op_id_arg.first)->copy();
    operation_to_use->setParam(op_id_arg.second);
    applyOperation(*operation_to_use);
    delete operation_to_use;
}

void Image::applyOperation(const Operation& op) {
    std::vector<std::pair<int, int>> selected = all_selections.getActiveCoordinates(Dimensions());
    applyOperationCoordinates(op, selected);
}

void Image::applyOperationCoordinates(const Operation& op, const std::vector<std::pair<int, int>>& selected) {
    for(Layer& l : all_layers) {
        OperationalLayer operational = makeOperationalLayer(l);
        op(operational, selected);
        for(std::pair<int, int> s : selected) {
            l[s].setAlfa(operational.matrix[operational.dimensions.first * s.second + s.first].alfa);
            l[s].setRed(operational.matrix[operational.dimensions.first * s.second + s.first].red);
            l[s].setBlue(operational.matrix[operational.dimensions.first * s.second + s.first].blue);
            l[s].setGreen(operational.matrix[operational.dimensions.first * s.second + s.first].green);
        }
    }
}

OperationalLayer Image::makeOperationalLayer(Layer& l) {
    std::vector<OperationalPixel> operational;
    for(Pixel p : l)
        operational.push_back({p.Red(), p.Green(), p.Blue(), p.Alfa()});
    return {operational, l.Dimension()};
}


std::vector<int> Image::getFinalResult() {
    auto vp = all_layers.combineLayers().Matrix();
    std::vector<int> vi;
    for(Pixel& p : vp)
        vi.push_back((int)p);
    return vi;
}

void Image::saveAll() {
    auto doc = project_manager.createProjectFile();
    std::vector<LayerInfo> layer_information = getLayerInfo();
    project_manager.saveLayers(doc, layer_information);

    std::vector<PM_Formater_info> selection_info = getSelectionInfo();
    project_manager.saveSelections(doc, selection_info);
    
    std::vector<PM_Formater_info> operation_info = getOperationInfo();
    project_manager.saveOperations(doc, operation_info);

    std::ofstream xml_file(ProjectManager::project_file_name);
    xml_file << *doc;
    xml_file.close();
}

std::vector<LayerInfo> Image::getLayerInfo() const {
    std::vector<LayerInfo> all_info;
    for (const Layer& l : all_layers) {
        LayerInfo newInfo;
        newInfo.name = l.getName();
        newInfo.path = all_layers.getLayerPaths().at(newInfo.name);
        newInfo.opacity = l.Opacity();
        newInfo.active = l.Active();

        all_info.push_back(newInfo);
    }
    return all_info;
}

std::vector<PM_Formater_info> Image::getSelectionInfo() const {
    std::vector<PM_Formater_info> all_info;
    for (const Selection& s : all_selections) {
        PM_Formater_info info;
        info.name = s.Name();
        info.header["name"] = s.Name();
        info.header["active"] = (s.isActive() ? "true" : "false");
        auto rectangles = s.getRectangles();
        for (auto r : rectangles) {
            std::map<std::string, std::string> rectangle;
            rectangle["width"] = std::to_string(r.Dimensions().first);
            rectangle["height"] = std::to_string(r.Dimensions().second);
            rectangle["x"] = std::to_string(r.Coordinates().first);
            rectangle["y"] = std::to_string(r.Coordinates().second);
            info.body.push_back(rectangle);
        }
        all_info.push_back(info);
    }
    return all_info;
}

std::vector<PM_Formater_info> Image::getOperationInfo() const {
    std::vector<PM_Formater_info> all_info;
    int i = 0;
    for (const Operation* const & op : all_operations) {
        if (i < all_operations.getDefaultOpNum()) {
            i++;
            continue;
        }
        PM_Formater_info info;
        info.header["name"] = op->Name();
        info.name = op->Name();
        auto op_all = op->copyVector();
        for (const Operation* const& one_op : op_all) {
            std::map<std::string, std::string> one_op_info;
            one_op_info["name"] = one_op->Name();
            one_op_info["arg"] = std::to_string(one_op->getParam());
            info.body.push_back(one_op_info);
        }
        all_info.push_back(info);
    }

    return all_info;
}

void Image::openProject() {
    ProjectInfo project_info = project_manager.openProject();
    loadLayers(project_info.layer_info);
    loadSelections(project_info.selection_info);
    loadOperations(project_info.operation_info);
}

void Image::loadLayers(const std::vector<LayerInfo>& all_layer_info) {
    for (const LayerInfo& info : all_layer_info)// TODO: check paths
        all_layers.addLayer(info.name, info.path, info.opacity, info.active);
}
void Image::loadSelections(const std::vector<PM_Formater_info>& all_selection_info) {
    int failed = 0;
    
    for (const auto& one_sel : all_selection_info) {
        try {
            std::vector<RectangleShape> rect;
            for (auto i : one_sel.body) {
                std::function<void(const std::string&)> check = [&i](const std::string& s) {
                    if (i.find(s) == i.end())
                        throw SelectionCorruption();
                };
                check("width");
                check("height");
                check("x");
                check("y");
                std::pair<int, int> dimension;
                
                rect.push_back({ atoi(i["x"].c_str()), atoi(i["y"].c_str()), atoi(i["width"].c_str()), atoi(i["height"].c_str()) });
            }
            Selection s(rect);
            s.setActive((one_sel.header.at("active") == "true" ? true : false));
            s.setName(one_sel.header.at("name"));
            all_selections.addSelection(s);
        }
        catch (std::exception& s) { failed++; }
    }

}
void Image::loadOperations(const std::vector<PM_Formater_info>& all_operations_info) {
    int failed = 0;
    for (const PM_Formater_info& one_op : all_operations_info) {
        try {
            std::vector<std::pair<int, int>> op_arg;
            for (const auto& i : one_op.body) {
                std::function<void(const std::string&)> check = [&i](const std::string& s) {
                    if (i.find(s) == i.end())
                        throw OperationCorruption();
                };
                check("arg");
                check("name");
                std::string name = i.at("name");
                int arg = atoi(i.at("arg").c_str());
                int id = std::find_if(all_operations.begin(), all_operations.end(), [&name](const Operation* const& iter_op) {
                    return name == iter_op->Name();
                }) - all_operations.begin();
                op_arg.push_back({ id, arg });
            }
            std::string name = one_op.header.at("name");
            all_operations.createOperation(op_arg, name);
        }
        catch (std::exception&) {
            failed++;
        }
    }
}
/*
2
C:\Users\Dinbo\Desktop\MyProj\MojProj\MojProj\
1
1
a
C:\Users\Dinbo\Desktop\MyProj\MojProj\MojProj\resource\a.bmp

0
4
1

*/