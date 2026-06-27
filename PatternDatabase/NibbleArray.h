#ifndef NIBBLEARRAY_H
#define NIBBLEARRAY_H

#include <cstdint>
#include <vector>

using namespace std;

class NibbleArray {
private:
    size_t logicalSize;
    vector<uint8_t> values;

public:
    explicit NibbleArray(size_t size, uint8_t fillValue = 0xFF);

    uint8_t get(size_t index) const;
    void set(size_t index, uint8_t value);

    uint8_t *data();
    const uint8_t *data() const;

    size_t storageSize() const;
    void inflate(vector<uint8_t> &out) const;
    void reset(uint8_t value = 0xFF);
};

#endif
