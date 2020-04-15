#include <algorithm>
#include "layer.h"

const std::string Layer::DEFAULT_LAYER_NAME = "layer";

Layer::Layer(int w, int h, std::string name_) : dimension{w, h}, name(name_) {
    initMatrix();
}

Layer::Layer(std::pair<int, int> dim_, std::string name_) : dimension(dim_), name(name_) {
    initMatrix();
}

Layer::Layer(std::pair<int, int> dim_, std::vector<Pixel> new_layer_matrix, std::string name_) : layer_matrix(new_layer_matrix), name(name_) {
    dimension = dim_;
}

void Layer::setOpacity(int x) {
    if(x < MIN_OPACITY) opacity = MIN_OPACITY;
    else if(x > MAX_OPACITY) opacity = MAX_OPACITY;
    else opacity = x;
}

Pixel& Layer::operator[] (std::pair<int, int> coordinateXY) {
    checkBounds(coordinateXY);
    return layer_matrix[coordinateXY.second * dimension.first + coordinateXY.first];
}

const Pixel& Layer::operator[] (std::pair<int, int> coordinate) const {
    checkBounds(coordinate);
    return const_cast<Pixel&>(layer_matrix[coordinate.second * dimension.first + coordinate.first]);
}    

Layer operator+(const Layer& l1, const Layer& l2) {
    if(l1.dimension != l2.dimension)
        throw LayerDimensionMismatch();
    
    Layer newLayer = Layer(l1.dimension);
    for(int i=0; i<l1.dimension.second; i++) {
        for(int j=0; j<l1.dimension.first; j++) {
            Pixel temp1 = l1[{j, i}];
            Pixel temp2 = l2[{j, i}];
            temp2.setAlfa(temp2.Alfa() * l2.opacity / Layer::MAX_OPACITY);
            newLayer[{j,i}] = temp1 + temp2;
        }
    }
    return newLayer;
}

void Layer::convertGray() {
    for(Pixel& p: layer_matrix)
        p = p.getGray();
}

void Layer::convertBlackWhite() {
    for(Pixel& p : layer_matrix)
        p = p.getBlackWhite();
}

void Layer::fitLayer(std::pair<int, int> new_dims) {
    if(new_dims.first < dimension.first && new_dims.second < dimension.second)
        return;
    
    std::vector<Pixel> new_Layer(new_dims.first * new_dims.second, Pixel(255,255,255,0));
    for(int i=0; i<dimension.second; i++){
        for(int j=0; j<dimension.first; j++) {
            new_Layer[i*new_dims.first + j] = layer_matrix[i*dimension.first + j];
        }
    }
    layer_matrix = new_Layer;
    dimension = new_dims;
}

void Layer::initMatrix() {
    layer_matrix.assign(dimension.second * dimension.first, 0);
}

void Layer::checkBounds(std::pair<int, int> coordinates) const{
    if(coordinates.first < 0 || coordinates.first >= dimension.first)
        throw LayerIndexOutOfBounds();
    if(coordinates.second < 0 || coordinates.second >= dimension.second)
        throw LayerIndexOutOfBounds();
}

Pixel Layer::getMedian(std::pair<int, int> coord) const {
    int sumR = operator[]({coord.first, coord.second}).Red();
    int sumB = operator[]({coord.first, coord.second}).Blue();
    int sumG = operator[]({coord.first, coord.second}).Green();
    int alfa = operator[]({coord.first, coord.second}).Alfa();
    int cnt=1;
    auto add = [&](const Pixel& l) {
        sumR += l.Red();
        sumG += l.Green();
        sumB += l.Blue();
        cnt++;
    };
    auto check = [this](std::pair<int, int> coordinates) -> bool {
        if(coordinates.first < 0 || coordinates.first >= dimension.first)
            return false;
        if(coordinates.second < 0 || coordinates.second >= dimension.second)
            return false;
        return true;
    };
    auto val = [this] (std::pair<int, int> coordinates) -> int {
        return coordinates.second * dimension.first + coordinates.first;
    };
    // add(layer_matrix[val(coord)]);
    if(check({coord.first-1, coord.second}))
        add(layer_matrix[val({coord.first-1, coord.second})]);

    if(check({coord.first+1, coord.second}))
        add(layer_matrix[val({coord.first+1, coord.second})]);

    if(check({coord.first, coord.second+1}))
        add(layer_matrix[val({coord.first, coord.second+1})]);

    if(check({coord.first, coord.second-1}))
        add(layer_matrix[val({coord.first, coord.second-1})]);
    // add(layer_matrix[val(coord)].Red());
    return {sumR/cnt, sumG/cnt, sumB/cnt, alfa};
}