#ifndef _image_h_
#define _image_h_

#include <vector>
#include <map>

#include "layer.h"
#include "operation.h"
#include "selection.h"

class ImageIndexOutOfBounds {

};

class Image {
public:
    Image() {} // TODO: initialize operations
    ~Image() {} // TODO: remove all operations

    Image& addLayer(int position, std::string name_);
    Image& removeLayer(int position);

    Image& addOperation(Operation* op);
    Image& removeOperation(int i);

    Image& applyOperation(int operation_id, int layer_, int selection_id);
private:
    std::pair<int, int> dimensions;
    
    std::vector<Selection> all_selections;
    std::vector<Operation*> all_operations;
    std::vector<Layer> all_layers;
    std::map< std::string, std::function<int(int, int)> > diadic_functions;

    void fittAll();
    Layer combineLayers() const;
    void initOperations();
};

#endif // _image_h_