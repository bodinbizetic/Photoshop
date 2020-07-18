#include <algorithm>
#include <memory>
#include "project_manager.h"
#include "formater_bmp.h"
#include "layer_collection.h"
#include "utilities.h"

void LayerCollection::addLayer(int position, std::string name_, std::string path_) {
    Layer newLayer = createLayer(name_, path_);

    if(position >= all_layers.size() || position < 0)
        all_layers.push_back(newLayer);
    else 
        all_layers.insert(all_layers.begin() + position, newLayer);

    fitAll();
}

void LayerCollection::addLayer(std::string name_, std::string path_, int opacity, int active) {
    Layer newLayer = createLayer(name_, path_);
    newLayer.setOpacity(opacity);
    newLayer.setActive(active);
    all_layers.push_back(newLayer);
    updateDim(newLayer.Dimension());
    fitAll();
}

void LayerCollection::addLayer(std::pair<int, int> dimensions_, std::string name_) {
    updateDim(dimensions_);
    Layer newLayer = createLayer(name_, "");
    all_layers.push_back(newLayer);
    updateDim(dimensions_);
    fitAll();
}

void LayerCollection::removeLayer(int position) {
    if(position >= all_layers.size() || position < 0)
       throw LayerIndexOutOfBounds();
    layer_paths.erase(layer_paths.find(all_layers[position].getName()));
    all_layers.erase(all_layers.begin() + position);
    if(all_layers.size() == 0)
        dimensions = {0,0};
}

std::vector<std::pair<std::string, std::string>> LayerCollection::getLayerNames() const {
    std::vector<std::pair<std::string, std::string>> names;
    for(const Layer& l: all_layers) {
        names.push_back({l.getName(), (l.Active() ? "True" : "False")});
    }
    return names;
}

void LayerCollection::toggleLayer(int position) {
    if(position >= all_layers.size() || position < 0)
       throw LayerIndexOutOfBounds();
    
    all_layers[position].setActive(!all_layers[position].Active());
}

void LayerCollection::setOpacity(int position, int val) {
    if(position >= all_layers.size() || position < 0)
       throw LayerIndexOutOfBounds();
    
    all_layers[position].setOpacity(val);
}

std::vector<int> LayerCollection::getLayerMatrix(int position) const {
    if(position >= all_layers.size() || position < 0)
       throw LayerIndexOutOfBounds();
    
    auto matrix = all_layers[position].Matrix();
    std::vector<int> ret;
    for(auto m : matrix)
        ret.push_back((int)m);
    
    return ret;
}

void LayerCollection::swapLayers(int position1, int position2) {
    if(position1 >= all_layers.size() || position1 < 0)
       throw LayerIndexOutOfBounds();
    if(position2 >= all_layers.size() || position2 < 0)
       throw LayerIndexOutOfBounds();
    
    std::swap(all_layers[position1], all_layers[position2]);
}

Layer LayerCollection::combineLayers() const {
    Layer l1(dimensions);
    std::for_each(all_layers.rbegin(), all_layers.rend(), [&l1](const Layer& l) {
        if (l.Active())
            l1 = l1 + l;
    });

    return l1;
}

Layer LayerCollection::createLayer(std::string name_, std::string path_) {
    if(path_ == "") {
        layer_paths[name_] = ProjectManager::resource_folder + OS_SEP + name_ + ".bmp";
        return Layer(dimensions, name_);
    }
    else {
        std::shared_ptr<Formater> f(Formater::getFormater(path_));
        std::vector<int> vi = f->load();
        std::vector<Pixel> vp;
        for(int i : vi) {
            vp.push_back((Pixel) i);
        }
        std::pair<int, int> dim = f->Dimensions();
        layer_paths[name_] = path_;
        Layer newLayer(dim, vp, name_);
        updateDim(dim);
        return newLayer;
    }
}

void LayerCollection::fitAll() {
    for(Layer& l : all_layers)
        l.fitLayer(dimensions);
}

void LayerCollection::updateDim(std::pair<int, int> newDim) {
    dimensions.first = std::max(dimensions.first, newDim.first);
    dimensions.second = std::max(dimensions.second, newDim.second);
}

void LayerCollection::saveAllLayers(std::string workind_dir) {
    for(const Layer& l : all_layers)
        saveLayer(l, workind_dir);
}

void LayerCollection::saveLayer(const Layer& layer, std::string working_dir) {
    std::shared_ptr<Formater> formater(Formater::getFormater(layer_paths[layer.getName()])); 
    std::vector<int> vi;
    for(auto i : layer.Matrix())
        vi.push_back(i);

    formater->store(vi, layer.Dimension());
}