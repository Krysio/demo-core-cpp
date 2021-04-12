#pragma once

namespace helper {
    std::string readBuffToHexStr(unsigned char* data, size_t len);
}
namespace LEB128 {
    /**
     * Calculate size encoded unsigned LEB128 data
     * @param value: value to encode
     * @return the number of bytes to allocate
     */
    uintmax_t calcSizeOfUnsigned(
        uintmax_t value
    );
    /**
     * Calculate size encoded LEB128 data
     * @param value: value to encode
     * @return the number of bytes to allocate
     */
    uintmax_t calcSizeOfSigned(
        intmax_t value
    );
    /**
     * Write unsigned LEB128 data
     * @param bufferAddress: the address where the ULEB128 data will stored
     * @param value: value to encode
     * @return the number of written bytes
     */
    uintmax_t writeUnsigned(
        buffer_ptr bufferAddress,
        uintmax_t value
    );
    /**
     * Read unsigned LEB128 data
     * @param bufferAddress: the address where the ULEB128 data is stored
     * @param returnAddress: address to store the result
     * @return the number of bytes read
     */
    uintmax_t readUnsigned(
        buffer_cptr bufferAddress,
        uintmax_t* returnAddress
    );
    /**
     * Write LEB128 data
     * @param bufferAddress: the address where the LEB128 data will stored
     * @param value: value to encode
     * @return the number of written bytes
     */
    uintmax_t writeSigned(
        buffer_ptr bufferAddress,
        intmax_t value
    );
    /**
     * Read LEB128 data
     * @param bufferAddress: the address where the LEB128 data is stored
     * @param returnAddress: address to store the result
     * @return the number of bytes read
     */
    uintmax_t readSigned(
        buffer_cptr bufferAddress,
        intmax_t* returnAddress
    );
}