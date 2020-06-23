#ifndef __OPERATION_COLLECTION_H__
#define __OPERATION_COLLECTION_H__

#include <vector>
#include <functional>
#include <exception>
#include "operation.h"

class CollectionIndexOutOfBounds : public std::exception{

};

class OperationCollection {
public:
    OperationCollection() { initOperations(); }
    ~OperationCollection();
    std::vector<std::string> getOperationNames() const;
    std::vector<std::pair<std::string, std::string>> getOperationMode() const;

    void createOperation(std::vector<std::pair<int, int>> op_arg, std::string name_);
    void addOperation(const Operation& op);
    void removeOperation(int i);
    Operation* getOperation(int pos);

    void toggleModeColor(std::string c);
    int getModeBinary();
    int getDefaultOpNum() const { return default_op_num; }

    std::vector<Operation*>::const_iterator begin() const { return all_operations.cbegin(); }
    std::vector<Operation*>::const_iterator end() const { return all_operations.cend(); }

private:
    std::map<std::string, bool> operation_mode{{"Red", true}, {"Green", true}, {"Blue", true}, {"Alfa", false}};
    std::vector<Operation*> all_operations;
    unsigned int default_op_num = 0;

    void initOperations();
    void initOperationsTransformations();
    void initOperationsTransformationsGray();
    void initOperationsTransformationsBlackWhite();
    void initOperationsTransformationsMedian();
};

#endif // __OPERATION_COLLECTION_H__
