#ifndef __LAYER_H__
#define __LAYER_H__

#include <vector>
#include <utility>
#include <exception>

#include "pixel.h"

class LayerIndexOutOfBounds {

};

class LayerFitDimensionsSmaller {

};

class Layer {
public:
    Layer(int w, int h);
    Layer(std::pair<int, int> dim_);
    Layer(std::vector< std::vector<Pixel> > new_layer_matrix);
    void setOpacity(int x);
    void setActive(bool x) { active = x; }
    int Opacity() const { return opacity; }
    bool Active() const {return active; }

    Pixel& operator[] (std::pair<int, int>);
    const Pixel& operator[] (std::pair<int, int>) const;

    void fitLayer(std::pair<int, int>);
private:
    std::pair<int, int> dimension;
    std::vector< std::vector<Pixel> > layer_matrix;
    
    static const int MIN_OPACITY = 0;
    static const int MAX_OPACITY = 100;
    int opacity;
    bool active=true;

    void initMatrix();
    void checkBounds(std::pair<int, int>) const;

    #ifdef _TEST_
        friend std::ostream& operator<< (std::ostream& os, Layer& l){
            for(int i=0; i<l.dimension.second; i++) {
                for(int j=0; j<l.dimension.first; j++)
                    os << l.layer_matrix[i][j] << " ";
                os << std::endl;
            }
            return os;
        }
    #endif
};

#endif // __LAYER_H__
