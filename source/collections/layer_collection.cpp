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

void LayerCollection::addLayer(std::pair<int, int> dimensions_, std::string name_) {
    Layer newLayer(dimensions_, name_);
    all_layers.push_back(newLayer);
    updateDim(dimensions_);
    fitAll();
}

void LayerCollection::removeLayer(int position) {
    if(position >= all_layers.size() || position < 0)
       throw LayerIndexOutOfBounds();
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
    for(const Layer& l : all_layers)
        if(l.Active())
            l1 = l1 + l;

    return l1;
}

Layer LayerCollection::createLayer(std::string name_, std::string path_) {
    if(path_ == "")
        return Layer(dimensions, name_);
    else {
        Formater &f = * new Formater_BMP(path_);
        std::vector<int> vi = f.load();
        std::vector<Pixel> vp;
        for(int i : vi) { // TODO: Add constructor from vi to vp
            vp.push_back((Pixel) i);
        }
        std::pair<int, int> dim = f.Dimensions();
        Layer newLayer(dim, vp, name_);
        // TODO: call fit layers
        updateDim(dim);
        delete &f;
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

void LayerCollection::saveAllLayersBMP(std::string workind_dir) {
    for(int i=0; i<all_layers.size(); i++)
        saveLayerBMP(i, workind_dir);
}

void LayerCollection::saveLayerBMP(int pos, std::string working_dir) {
    if(pos < 0 || pos >= all_layers.size())
        throw LayerIndexOutOfBounds();
    const Layer& curr_layer = all_layers[pos];
    Formater_BMP formater(working_dir + OS_SEP + curr_layer.getName() + ".bmp");
    
    std::vector<int> vi;
    for(auto i : curr_layer.Matrix())
        vi.push_back(i);

    formater.store(vi, curr_layer.Dimension());
}

/*
1
1
1
name
resource/leopard.bmp
9
*/