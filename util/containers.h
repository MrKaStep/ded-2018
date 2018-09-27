//
// Created by step on 27.09.18.
//

#ifndef DED_2018_CONTAINERS_H
#define DED_2018_CONTAINERS_H

#include <algorithm>
namespace Util {

    /**
     * @brief std-like container filtering function
     *
     * @tparam FwdIt iterator type
     * @tparam Predicate
     * @param first begin of the container
     * @param last end of the container
     * @param predicate unary predicate returning whether we should keep the element or not
     * @return
     */
    template<class FwdIt, class Predicate>
    const FwdIt Filter(FwdIt first, FwdIt last, Predicate predicate) {
        FwdIt tail = first;

        for (auto current = first; current != last; ++current) {
            if (predicate(*current)) {
                std::iter_swap(current, tail);
                ++tail;
            }
        }

        return tail;
    }

} /// namespace util

#endif //DED_2018_CONTAINERS_H
