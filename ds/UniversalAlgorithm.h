#pragma once

class UniversalAlgorithm {
public:
    template<typename Iterator, typename Predicate, typename Processor>
    void process(Iterator begin, Iterator end, Predicate pred, Processor proc) {
        for (Iterator it = begin; it != end; ++it) {
            if (pred(*it)) {
                proc(*it);
            }
        }
    }
};