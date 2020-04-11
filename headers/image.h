#ifndef _image_h_
#define _image_h_

#include <vector>

#include "layer.h"
#include "operation.h"
#include "selection.h"

class Image {
public:
    Image() {}
    ~Image() {}

    void addLayer(int position);
    void removeLayer(int position);

    void addOperation(Operation* op);
    void removeOperation(int i);

    void applyOperation(int operation_id, int layer_, int selection_id);
private:
    std::pair<int, int> dimensions;
    
    std::vector<Selection> all_selections;
    std::vector<Operation*> all_operations;
    std::vector<Layer> all_layers;

    void fittAll();
    Layer combineLayers() const;
};

#endif // _image_h_