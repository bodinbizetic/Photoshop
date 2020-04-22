#ifndef _image_h_
#define _image_h_

#include <vector>
#include <map>
#include <exception>

#include "layer.h"
#include "operation.h"
#include "project_manager.h"
#include "layer_collection.h"
#include "selection_collection.h"
#include "operation_collection.h"

class ImageIndexOutOfBounds : public std::exception{
    const char* what() const noexcept override {
        std::cout << "Image index out of bounds" << std::endl;
        return "Image index out of bounds";
    }
};

class Image {
public:
    Image(std::string path);
    ~Image(); // TODO: remove all operations

    LayerCollection& getLayerCollection() { return all_layers; }
    SelectionCollection& getSelectionCollection() { return all_selections; }
    OperationCollection& getOperationCollection() { return all_operations; }
    ProjectManager& getProjectManager() { return project_manager;  }

    void useOperation(std::pair<int, int> op_id_arg);

    std::pair<int, int> Dimensions() const { return all_layers.Dimensions(); };
    std::vector<int> getFinalResult();
    
    void saveAll();
    void openProject();
    void createProject(std::string name) { project_manager.createProject(name); }

private:
    SelectionCollection all_selections;
    LayerCollection all_layers;
    OperationCollection all_operations;
    ProjectManager project_manager;

    void applyOperation(const Operation& op);
    void applyOperationCoordinates(const Operation& op, const std::vector<std::pair<int, int>>&);
    OperationalLayer makeOperationalLayer(Layer& l);

    std::vector<LayerInfo> getLayerInfo() const;
    std::vector<SelectionInfo> getSelectionInfo() const;

    void loadLayers(const std::vector<LayerInfo>& all_layer_info);
};

#endif // _image_h_