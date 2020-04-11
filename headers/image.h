#ifndef _image_h_
#define _image_h_

#include <vector>
#include <map>

#include "layer.h"
#include "operation.h"
#include "selection.h"

class Image {
public:
    Image() {} // TODO: initialize operations
    ~Image() {} // TODO: remove all operations

    void addLayer(int position, std::string name_);
    void removeLayer(int position);

    void addOperation(Operation* op);
    void removeOperation(int i);

    void applyOperation(int operation_id, int layer_, int selection_id);
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