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
    Image();
    ~Image(); // TODO: remove all operations

    Image& addLayer(int position, std::string name_, std::string path_);
    Image& removeLayer(int position);
    std::vector<std::pair<std::string, std::string>> getLayerNames() const;
    Image& toggleLayer(int pos);

    Image& addOperation(const Operation& op);
    Image& removeOperation(int i);

    Image& select(RectangleShape r) { current_selection.add(r); return *this;};
    Image& clearSelection() { current_selection.deselectAll(); return *this;}
    Image& toggleSelection() { current_selection.setActive(!current_selection.isActive()); return *this; }

    Image& applyOperation(int operation_id, int layer_);
private:
    std::pair<int, int> dimensions;

    Selection current_selection;
    std::vector<Operation*> all_operations;
    std::vector<Layer> all_layers;
    std::map< std::string, std::function<int(int, int)> > diadic_functions;

    void fittAll();
    Layer combineLayers() const;
    void initOperations();
};

#endif // _image_h_