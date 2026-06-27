#include "NibbleArray.h"

#include <algorithm>
#include <cassert>

NibbleArray::NibbleArray(size_t size, uint8_t fillValue)
        : logicalSize(size), values(size / 2 + 1, fillValue) {}

uint8_t NibbleArray::get(size_t index) const {
    assert(index < logicalSize);
    uint8_t packed = values[index / 2];
    if (index % 2 == 0) return packed >> 4;
    return packed & 0x0F;
}

void NibbleArray::set(size_t index, uint8_t value) {
    assert(index < logicalSize);
    value &= 0x0F;
    uint8_t &packed = values[index / 2];

    if (index % 2 == 0) packed = static_cast<uint8_t>((packed & 0x0F) | (value << 4));
    else packed = static_cast<uint8_t>((packed & 0xF0) | value);
}

uint8_t *NibbleArray::data() {
    return values.data();
}

const uint8_t *NibbleArray::data() const {
    return values.data();
}

size_t NibbleArray::storageSize() const {
    return values.size();
}

void NibbleArray::inflate(vector<uint8_t> &out) const {
    out.clear();
    out.reserve(logicalSize);
    for (size_t i = 0; i < logicalSize; i++) out.push_back(get(i));
}

void NibbleArray::reset(uint8_t value) {
    fill(values.begin(), values.end(), value);
}
