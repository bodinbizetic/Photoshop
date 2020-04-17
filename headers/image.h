#ifndef _image_h_
#define _image_h_

#include <vector>
#include <map>
#include <exception>

#include "layer.h"
#include "operation.h"
#include "selection_collection.h"

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
    Image& addLayer(std::pair<int, int> dimensions_, std::string name_);
    Image& removeLayer(int position);
    std::vector<std::pair<std::string, std::string>> getLayerNames() const;
    Image& toggleLayer(int pos);
    Image& setOpacity(int position, int val);
    std::vector<int> getLayerMatrix(int) const;
    void swapLayers(int, int);

    SelectionCollection& getSelectionCollection() { return all_selections; }

    std::vector<std::string> getDiadicNames() const;
    std::vector<std::string> getOperationNames() const;
    std::vector<std::pair<std::string, std::string>> getOperationMode() const;
    Image& useDiadic(std::string name, int arg);
    Image& useOperation(int pos);
    void createOperation(std::vector<std::pair<int, int>> op_arg, std::string name_);
    Image& addOperation(const Operation& op);
    Image& removeOperation(int i);


    std::pair<int, int> Dimensions() const { return dimensions; };
    std::vector<int> getFinalResult();
    void toggleModeColor(std::string c);

    void toGray();
    void toBlackWhite();
    void invert();
    void blur();
private:
    SelectionCollection all_selections;
    std::map<std::string, bool> operation_mode{{"Red", true}, {"Green", true}, {"Blue", true}, {"Alfa", false}};
    
    std::pair<int, int> dimensions;
    
    std::vector<Operation*> all_operations;
    std::vector<Layer> all_layers;
    std::map< std::string, std::function<int(int, int)> > diadic_functions;

    int transformOneDimension(std::pair<int, int> p) { return p.second * dimensions.first + p.first; }
    Layer combineLayers() const;
    void initOperations();
    Layer createLayer(std::string name_, std::string path_);
    void fitAll();
    void updateDim(std::pair<int, int> newDim);

    Image& applyOperationSelection(const Operation& op);
    Image& applyOperation(const Operation& op);
    Image& applyOperationCoordinates(const Operation& op, std::vector<std::pair<int, int>>);
    std::vector<std::pair<int, int>> getActiveCoordinates();
};

#endif // _image_h_