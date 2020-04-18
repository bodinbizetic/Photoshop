#ifndef __LAYER_COLLECTION_H__
#define __LAYER_COLLECTION_H__

#include "layer.h"

class LayerCollection {
public:
    std::pair<int, int> Dimensions() const { return dimensions; }

    void addLayer(int position, std::string name_, std::string path_);
    void addLayer(std::pair<int, int> dimensions_, std::string name_);
    void removeLayer(int position);
    std::vector<std::pair<std::string, std::string>> getLayerNames() const;
    void toggleLayer(int pos);
    void setOpacity(int position, int val);
    std::vector<int> getLayerMatrix(int) const;
    void swapLayers(int, int);

    Layer combineLayers() const;

    void convertGray(const std::vector<std::pair<int, int>>&);
    void convertBlackWhite(const std::vector<std::pair<int, int>>&);
    void convertMedianBlur(const std::vector<std::pair<int, int>>&);
private:
    std::vector<Layer> all_layers;
    std::pair<int, int> dimensions;

    Layer createLayer(std::string name_, std::string path_);
    void fitAll();
    void updateDim(std::pair<int, int> newDim);
    
    std::vector<Layer>::iterator begin() { return all_layers.begin(); }
    std::vector<Layer>::iterator end() { return all_layers.end(); }

    friend class Image;
};

#endif // __LAYER_COLLECTION_H__
