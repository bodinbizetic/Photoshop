#include <algorithm>
#include "layer.h"

Layer::Layer(int w, int h) : dimension{w, h} {
    initMatrix();
}

Layer::Layer(std::pair<int, int> dim_) : dimension(dim_) {
    initMatrix();
}

Layer::Layer(std::vector< std::vector<Pixel> > new_layer_matrix) : layer_matrix(new_layer_matrix) {
    dimension = {layer_matrix[0].size(), layer_matrix.size()};
}

void Layer::setOpacity(int x) {
    if(x < MIN_OPACITY) opacity = MIN_OPACITY;
    else if(x > MAX_OPACITY) opacity = MAX_OPACITY;
    else opacity = x;
}

Pixel& Layer::operator[] (std::pair<int, int> coordinate) {
    checkBounds(coordinate);
    return layer_matrix[coordinate.second][coordinate.first];
}

const Pixel& Layer::operator[] (std::pair<int, int> coordinate) const {
    return const_cast<Pixel&>(operator[](coordinate));
}

Layer operator+(const Layer& l1, const Layer& l2) {
    if(l1.dimension != l2.dimension)
        throw LayerDimensionMismatch();
    
    Layer newLayer = Layer(l1.dimension);
    for(int i=0; i<l1.dimension.second; i++) {
        for(int j=0; j<l1.dimension.first; j++) {
            Pixel temp1 = l1[{i, j}] + Pixel(0, 0, 0, l1.opacity);
            Pixel temp2 = l2[{i, j}] + Pixel(0, 0, 0, l2.opacity);
            newLayer[{i,j}] = temp1 + temp2;
        }
    }
    return newLayer;
}

void Layer::fitLayer(std::pair<int, int> new_dims) {
    if(new_dims.first < dimension.first || new_dims.second < dimension.second)
        throw LayerFitDimensionsSmaller();
    
    std::vector<Pixel> empty_pixels(dimension.first);
    generate(empty_pixels.begin(), empty_pixels.end(), []()->Pixel {return Pixel(0,0,0,0); });
    for(int i=0; i< new_dims.second - dimension.second; i++)
        layer_matrix.push_back(empty_pixels);
    
    for(std::vector<Pixel>& vp : layer_matrix)
        for(int i=0; i<new_dims.first - dimension.first; i++)
            vp.push_back(Pixel(0,0,0,0));
    
    dimension = new_dims;
}

void Layer::initMatrix() {
    layer_matrix.assign(dimension.second, std::vector<Pixel>(dimension.first));
}

void Layer::checkBounds(std::pair<int, int> coordinates) const{
    if(coordinates.first < 0 || coordinates.first >= dimension.first)
        throw LayerIndexOutOfBounds();
    if(coordinates.second < 0 || coordinates.second >= dimension.second)
        throw LayerIndexOutOfBounds();
}
