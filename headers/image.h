#ifndef _image_h_
#define _image_h_

#include <vector>
#include <map>
#include <exception>

#include "layer.h"
#include "operation.h"
#include "selection.h"

class ImageIndexOutOfBounds : public std::exception{
    const char* what() const noexcept override {
        std::cout << "Image index out of bounds" << std::endl;
        return "Image index out of bounds";
    }
};

class Image {
public:
    Image();
    ~Image(); // TODO: remove all operations

    Image& addLayer(int position, std::string name_, std::string path_);
    Image& removeLayer(int position);
    std::vector<std::pair<std::string, std::string>> getLayerNames() const;
    Image& toggleLayer(int pos);
    Image& setOpacity(int position, int val);
    std::vector<int> getLayerMatrix(int) const;
    void swapLayers(int, int);

    Image& addOperation(const Operation& op);
    Image& removeOperation(int i);

    Image& select(RectangleShape r, int position);
    Image& addSelection(std::string name_);
    std::vector<std::pair<std::string, std::string>> getSelectionNames() const;
    Image& removeSelection(int pos);
    Image& clearSelection(int pos);
    Image& toggleSelection(int position);

    Image& applyOperation(int operation_id, int layer_);

    std::pair<int, int> Dimensions() const { return dimensions; };
    std::vector<int> getFinalResult();
private:
    std::pair<int, int> dimensions;

    std::vector<Selection> all_selections;
    std::vector<Operation*> all_operations;
    std::vector<Layer> all_layers;
    std::map< std::string, std::function<int(int, int)> > diadic_functions;

    Layer combineLayers() const;
    void initOperations();
    Layer createLayer(std::string name_, std::string path_);
    void fitAll();
    void updateDim(std::pair<int, int> newDim);
};

#endif // _image_h_