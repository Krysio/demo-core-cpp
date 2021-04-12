#include "main.h"

namespace helper {
    constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

    std::string readBuffToHexStr(buffer_ptr data, size_t len)
    {
        std::string s(len * 2, ' ');
        for (size_t i = 0; i < len; ++i) {
            s[2 * i] = hexmap[(data[i] & 0xf0) >> 4];
            s[2 * i + 1] = hexmap[data[i] & 0x0f];
        }
        return s;
    }
}
namespace LEB128 {
    const uintmax_t uintmax_t_bits = sizeof(uintmax_t) * CHAR_BIT;

    uintmax_t calcSizeOfUnsigned(
        uintmax_t value
    ) {
        uintmax_t countOfBytes = 0;

        do {
            value >>= 7;
            ++countOfBytes;
        } while (value != 0);

        return countOfBytes;
    }

    uintmax_t calcSizeOfSigned(
        intmax_t value
    ) {
        uintmax_t countOfBytes = 0;
        intmax_t sign = value >> (8 * sizeof(value) - 1);
        intmax_t more;

        do {
            unsigned char byte = value & 0x7f;
            value >>= 7;
            more = value != sign || ((byte ^ sign) & 0x40) != 0;
            ++countOfBytes;
        } while (more);

        return countOfBytes;
    }

    uintmax_t writeUnsigned(
        buffer_ptr bufferAddress,
        uintmax_t value
    ) {
        uintmax_t countOfBytes = 0;
        uintmax_t shift = 0;

        do {
            unsigned char byte = value & 0x7f;
            buffer_ptr byteAddress = reinterpret_cast<buffer_ptr>(bufferAddress);

            value >>= 7;

            if (value != 0) {
                byte |= 0x80;
            }

            *byteAddress = byte;
            bufferAddress++;
            countOfBytes++;
        } while (value != 0);

        return countOfBytes;
    }

    uintmax_t readUnsigned(
        buffer_cptr bufferAddress,
        uintmax_t* returnAddress
    ) {
        uintmax_t result = 0;
        uintmax_t shift = 0;
        uintmax_t countOfReadBytes = 0;

        while (1) {
            unsigned char byte = *reinterpret_cast<buffer_cptr>(bufferAddress++);
            
            countOfReadBytes++;
            result |= (byte & static_cast<uintmax_t>(0x7f)) << shift;
            shift += 7;

            if (!(byte & 0x80)) {
                break;
            }
        }

        *returnAddress = result;
        return countOfReadBytes;
    }

    uintmax_t writeSigned(
        buffer_ptr bufferAddress,
        intmax_t value
    ) {
        size_t countOfBytes = 0;
        intmax_t more;

        do {
            unsigned char byte = value & 0x7f;
            buffer_ptr byteAddress = reinterpret_cast<buffer_ptr>(bufferAddress);

            value >>= 7;

            more = !(
                (
                    (value == 0)
                    && ((byte & 0x40) == 0)
                ) || (
                    (value == -1)
                    && ((byte & 0x40) != 0)
                )
            );

            if (more) {
                byte |= 0x80;
            }

            countOfBytes++;
            *byteAddress = byte;
            bufferAddress++;
        } while (more);

        return countOfBytes;
    }

    uintmax_t readSigned(
        buffer_cptr bufferAddress,
        intmax_t* returnAddress
    ) {
        unsigned char byte;
        intmax_t result = 0;
        uintmax_t shift = 0;
        uintmax_t countOfReadBytes = 0;
        intmax_t more;

        do {
            byte = *reinterpret_cast<buffer_cptr>(bufferAddress++);

            countOfReadBytes++;
            result |= (byte & static_cast<uintmax_t>(0x7f)) << shift;
            shift += 7;
            more = byte & 0x80;
        } while (more);

        if (byte & 0x40 && shift < uintmax_t_bits) {
            result |= static_cast<uintmax_t>(~0U) << shift;
        }

        *returnAddress = result;
        return countOfReadBytes;
    }
}