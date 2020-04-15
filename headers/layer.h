#ifndef __LAYER_H__
#define __LAYER_H__

#include <vector>
#include <utility>
#include <exception>

#include "pixel.h"

class LayerIndexOutOfBounds : public std::exception {
    const char* what() const noexcept override {
        std::cout << "LayerIndexOutOfBounds" << std::endl;
        return "LayerIndexOutOfBounds";
    }
};

class LayerFitDimensionsSmaller : public std::exception {
    const char* what() const noexcept override {
        std::cout << "LayerFitDimensionsSmaller" << std::endl;
        return "LayerFitDimensionsSmaller";
    }
};

class LayerDimensionMismatch : public std::exception {
    const char* what() const noexcept override {
        std::cout << "LayerDimensionMismatch" << std::endl;
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


    Pixel& operator[] (std::pair<int, int>);
    const Pixel& operator[] (std::pair<int, int>) const;

    friend Layer operator+(const Layer& l1, const Layer& l2); // TODO: Implement

    void convertGray();
    void convertBlackWhite();
    void fitLayer(std::pair<int, int>);
    Pixel getMedian(std::pair<int, int>) const;
private:
    std::string name = DEFAULT_LAYER_NAME;
    std::pair<int, int> dimension;
    std::vector<Pixel> layer_matrix;
    std::string path = "";
    int opacity = MAX_OPACITY;
    bool active=true;

    void initMatrix();
    void checkBounds(std::pair<int, int>) const;
    #ifdef _TEST_
        friend std::ostream& operator<< (std::ostream& os, Layer& l){
            for(int i=0; i<l.dimension.second; i++) {
                for(int j=0; j<l.dimension.first; j++)
                    // os << l.layer_matrix[i * j] << " ";
                os << std::endl;
            }
            return os;
        }
    #endif
};

#endif // __LAYER_H__
