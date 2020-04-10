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

void Layer::initMatrix() {
    layer_matrix.assign(dimension.second, std::vector<Pixel>(dimension.first));
}

void Layer::checkBounds(std::pair<int, int> coordinates) const{
    if(coordinates.first < 0 || coordinates.first >= dimension.first)
        throw LayerIndexOutOfBounds();
    if(coordinates.second < 0 || coordinates.second >= dimension.second)
        throw LayerIndexOutOfBounds();
}
