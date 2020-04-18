#ifndef __LAYER_H__
#define __LAYER_H__

#include <vector>
#include <utility>
#include <exception>

#include "pixel.h"

class LayerIndexOutOfBounds : public std::exception {
    const char* what() const noexcept override {
        return "Layer index out of bounds";
    }
};

class LayerFitDimensionsSmaller : public std::exception {
    const char* what() const noexcept override {
        return "LayerFitDimensionsSmaller";
    }
};

class LayerDimensionMismatch : public std::exception {
    const char* what() const noexcept override {
        return "LayerDimensionMismatch";
    }
};

class Layer {
public:
    static const std::string DEFAULT_LAYER_NAME;
    static const int MIN_OPACITY = 0;
    static const int MAX_OPACITY = 100;

    Layer(int w, int h, std::string name_ = DEFAULT_LAYER_NAME);
    Layer(std::pair<int, int> dim_, std::string name_ = DEFAULT_LAYER_NAME);
    Layer(std::pair<int, int> dim_, std::vector<Pixel> new_layer_matrix, std::string name_ = DEFAULT_LAYER_NAME);
    void setOpacity(int x);
    void setActive(bool x) { active = x; }
    int Opacity() const { return opacity; }
    bool Active() const { return active; }
    std::string getName() const { return name; }
    std::vector<Pixel> Matrix() const { return layer_matrix; }


    Pixel& operator[] (const std::pair<int, int>& coordinateXY);
    const Pixel& operator[] (const std::pair<int, int>& coordinateXY) const;

    friend Layer operator+(const Layer& l1, const Layer& l2); // TODO: Implement

    void convertGray(const std::pair<int, int>& coordinate);
    void convertBlackWhite(const std::pair<int, int>& coordinate);
    void convertMedianBlur(const std::pair<int,int>& coordinate);

    void fitLayer(std::pair<int, int>);
    std::pair<int, int> Dimension() const { return dimension; }
    std::vector<Pixel>::iterator begin() { return layer_matrix.begin(); }
    std::vector<Pixel>::iterator end() { return layer_matrix.end(); }
private:
    std::string name = DEFAULT_LAYER_NAME;
    std::pair<int, int> dimension;
    std::vector<Pixel> layer_matrix;
    std::string path = "";
    int opacity = MAX_OPACITY;
    bool active=true;


    void initMatrix();
    void checkBounds(const std::pair<int, int>& coordinate) const;
    Pixel getMedian(std::pair<int, int>) const;
};

#endif // __LAYER_H__
