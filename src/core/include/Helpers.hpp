#ifndef HELPERS_HPP
#define HELPERS_HPP

namespace ci {

/*
 * @brief Compare class to avoid comparing shared_ptrs stered for example in sets
 */
template<typename T>
struct PointerCompare {
    bool operator()(const T& lhs, const T& rhs) const {
        return *lhs < * rhs;
    }
};

} // namespace ci

#endif

