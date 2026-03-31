#ifndef LIBDS_MM_MEMORY_OMANIP_HPP
#define LIBDS_MM_MEMORY_OMANIP_HPP

#include <iomanip>
#include <ostream>
#include <sstream>
#include <bitset>

namespace ds::mm {

/**
 * @brief Base class for formatting and printing the memory content of a pointer byte by byte.
 * @tparam DataType The type of the data pointed to.
 */
template<typename DataType>
class PtrPrint {
public:
    /**
     * @brief Constructs a PtrPrint object and serializes the memory of the object into a string stream.
     * @param ptr Pointer to the data to be visualized.
     * @param base The numeric base to use for output (e.g., 2 for binary, 16 for hex).
     * @param width The minimum width for each byte representation.
     */
    PtrPrint(const DataType *ptr, int base, int width);

    /** @brief Constant pointer to the source memory block. */
    const DataType *m_ptr;
    /** @brief String stream storing the formatted byte-by-byte visualization. */
    std::ostringstream m_oss;
};

// --------------------------------------------------

/**
 * @brief Specialized PtrPrint for binary (base 2) representation of memory.
 * @tparam DataType The type of the data pointed to.
 */
template<typename DataType>
class PtrPrintBin : public PtrPrint<DataType> {
public:
    /**
     * @brief Constructs a PtrPrintBin object with binary formatting (8 bits per byte).
     * @param ptr Pointer to the data to be visualized.
     */
    PtrPrintBin(const DataType *ptr);
};

// --------------------------------------------------

/**
 * @brief Specialized PtrPrint for hexadecimal (base 16) representation of memory.
 * @tparam DataType The type of the data pointed to.
 */
template<typename DataType>
class PtrPrintHex : public PtrPrint<DataType> {
public:
    /**
     * @brief Constructs a PtrPrintHex object with hexadecimal formatting (2 characters per byte).
     * @param ptr Pointer to the data to be visualized.
     */
    PtrPrintHex(const DataType *ptr);
};

// ==================================================

template<typename DataType>
PtrPrint<DataType>::PtrPrint(const DataType *ptr, int base, int width) :
    m_ptr(ptr) {
    
    auto ptrB = reinterpret_cast<const unsigned char*>(m_ptr);

    for (size_t byte = 0; byte < sizeof(DataType); ++byte, ++ptrB) {
        m_oss << "|";

        if (base == 2) {
            m_oss << std::bitset<8>(*ptrB);
        } else {
            m_oss << std::setw(width)
                << std::setfill('0')
                << std::setbase(base)
                << static_cast<unsigned int>(*ptrB);
        }
    }
    m_oss << "|";
}

// --------------------------------------------------

template<typename DataType>
PtrPrintBin<DataType>::PtrPrintBin(const DataType *ptr) :
    PtrPrint<DataType>(ptr, 2, 8) {
}

// --------------------------------------------------

template<typename DataType>
PtrPrintHex<DataType>::PtrPrintHex(const DataType *ptr) :
    PtrPrint<DataType>(ptr, 16, 2) {
}

} // namespace ds::mm

// --------------------------------------------------

/**
 * @brief Stream insertion operator for PtrPrint and its derived classes.
 * @tparam DataType The type of the data being printed.
 * @param os The output stream.
 * @param pp The PtrPrint object containing the formatted memory string.
 * @return Reference to the output stream.
 */
template<typename DataType>
std::ostream &operator<< (
    std::ostream &os,
    const ds::mm::PtrPrint<DataType> &pp
) {
    return os << pp.m_oss.str();
}

#endif
