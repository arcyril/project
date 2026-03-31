#ifndef LIBDS_TESTS_ADT_TABLE_TEST_HPP
#define LIBDS_TESTS_ADT_TABLE_TEST_HPP

#include <libds/adt/table.hpp>

#include <libstest/test.hpp>

#include <algorithm>
#include <memory>
#include <random>
#include <type_traits>
#include <unordered_set>

namespace ds::tests {

namespace details {

class TableTestBase : public stest::LeafTest {
public:
    TableTestBase(const std::string &name, size_t seed) :
        LeafTest(name),
        rngKey_(seed) {
    }

protected:
    std::vector<int> generateKeys(int count) {
        auto keys = std::vector<int>();
        for (auto i = 0; i < count; ++i) {
            keys.push_back(i);
        }
        std::shuffle(begin(keys), end(keys), rngKey_);
        return keys;
    }

    template<class TableT>
    static bool hasKeys(TableT &table, const std::vector<int> &keys) {
        for (const auto key : keys) {
            if (! table.contains(key)) {
                return false;
            }
        }
        return true;
    }

protected:
    std::mt19937_64 rngKey_;
};

} // namespace details

/**
 * @brief Tests the insert operation
 * @tparam TableT Table type
 */
template<class TableT>
class TableTestInsert : public details::TableTestBase {
public:
    TableTestInsert() : details::TableTestBase("insert", 123) {
    }

protected:
    void test() override {
        constexpr auto n = 100;
        auto table = TableT();
        const auto keys = this->generateKeys(n);
        for (const auto key : keys) {
            try {
                table.insert(key, key);
            } catch (...) {
                this->fail("Insert should not throw on an unique key!");
            }
        }
        this->assert_equals(static_cast<size_t>(keys.size()), table.size());

        for (const auto key : keys) {
            try {
                table.insert(key, key);
                this->fail("Table should throw on a duplicate key");
            } catch (...) {
            }
        }
    }
};

/**
 * @brief Tests the find, tryFind, and contains operations
 * @tparam TableT Table type
 */
template<class TableT>
class TableTestLookup : public details::TableTestBase {
public:
    TableTestLookup() : details::TableTestBase("find-tryFind-contains", 456) {
    }

protected:
    void test() override {
        constexpr auto n = 100;
        auto table = TableT();
        const auto keys = this->generateKeys(n);
        for (const auto key : keys) {
            table.insert(key, key);
        }

        for (const auto key : keys) {
            try {
                const auto &data = table.find(key);
                this->assert_equals(key, data);
            } catch (...) {
                this->fail("Table should not throw on an existing key lookup!");
            }

            {
                auto *data = static_cast<int *>(nullptr);
                if (! table.tryFind(key, data)) {
                    this->fail("Table should find an existing key!");
                } else {
                    this->assert_equals(key, *data);
                }
            }

            if (! table.contains(key)) {
                this->fail("Table should contain an existing key!");
            }
        }

        for (auto i = 0; i < 10; ++i) {
            const auto key = n + i;
            try {
                (void)table.find(key);
                this->fail("Table should throw on an non-existing key lookup!");
            } catch (...) {
            }

            {
                auto *data = static_cast<int *>(nullptr);
                if (table.tryFind(key, data)) {
                    this->fail("Table should not find a non-existing key!");
                }
            }

            if (table.contains(key)) {
                this->fail("Table should not contain a non-existing key!");
            }
        }
    }
};

/**
 * @brief Tests the remove operation
 * @tparam TableT Table type
 */
template<class TableT>
class TableTestRemove : public details::TableTestBase {
public:
    TableTestRemove() : details::TableTestBase("remove", 789) {
    }

protected:
    void test() override {
        constexpr auto n = 100;
        auto table = TableT();
        const auto keys = this->generateKeys(n);
        for (const auto key : keys) {
            table.insert(key, key);
        }

        for (auto i = 0; i < 10; ++i) {
            const auto key = n + i;
            try {
                (void)table.remove(key);
                this->fail("Table should not remove non-existing key!");
            } catch (...) {
            }
        }

        for (const auto key : keys) {
            const auto data = table.remove(key);
            this->assert_equals(key, data);
        }

        this->assert_true(table.isEmpty(), "Table is empty");
    }
};

/**
 * @brief Tests the clear operation
 * @tparam TableT Table type
 */
template<class TableT>
class TableTestClear : public details::TableTestBase {
public:
    TableTestClear() : details::TableTestBase("clear", 147) {
    }

protected:
    void test() override {
        constexpr auto n = 100;
        auto table = TableT();
        const auto keys = this->generateKeys(n);
        for (const auto key : keys) {
            table.insert(key, key);
        }

        table.clear();
        this->assert_true(table.isEmpty(), "Cleared table is empty");
        this->assert_equals(static_cast<size_t>(0), table.size());
    }
};

/**
 * @brief Tests the copy constructor and assign operation
 * @tparam TableT Table type
 */
template<class TableT>
class TableTestCopyAssign : public details::TableTestBase {
public:
    TableTestCopyAssign() : details::TableTestBase("copy-assign", 258) {
    }

protected:
    void test() override {
        using base = details::TableTestBase;

        constexpr auto n = 100;
        auto table1 = TableT();
        auto keys = this->generateKeys(n);
        for (const auto key : keys) {
            table1.insert(key, key);
        }

        auto table2 = TableT(table1);
        this->assert_true(
            base::hasKeys(table2, keys),
            "Copy constructed table is the same"
        );

        table2.remove(keys.back());
        this->assert_true(
            base::hasKeys(table1, keys),
            "Original does not share items with the copy"
        );
        this->assert_false(
            base::hasKeys(table2, keys),
            "Modified copy is different"
        );

        table1.clear();
        keys.pop_back();
        this->assert_true(
            base::hasKeys(table2, keys),
            "Original does not share anything with the copy"
        );

        table2.clear();
        for (const auto key : keys) {
            table2.insert(key, key);
        }
        this->assert_true(base::hasKeys(table2, keys), "Copy still works");

        auto table3 = TableT();
        for (auto i = 0; i < static_cast<int>(keys.size()) / 5; ++i) {
            table3.insert(keys[i], keys[i]);
        }
        table3.assign(table2);

        this->assert_true(
            base::hasKeys(table3, keys),
            "Copy assigned table is the same"
        );
        table3.remove(keys.back());
        this->assert_true(
            base::hasKeys(table2, keys),
            "Original does not share anything with the copy assigned"
        );
        this->assert_false(
            base::hasKeys(table3, keys),
            "Modified copy assign is different"
        );
    }
};

/**
 * @brief Tests table iterator
 * @tparam TableT Table type
 */
template<class TableT>
class TableTestIterator : public details::TableTestBase {
public:
    TableTestIterator() : details::TableTestBase("iterator", 214) {
    }

protected:
    void test() override {
        constexpr auto n = 100;
        auto table = TableT();
        const auto keys = this->generateKeys(n);
        for (const auto key : keys) {
            table.insert(key, key);
        }

        auto setOfKeys = std::unordered_set<int>();
        auto it1 = table.begin();

        for (std::size_t i = 0; i < table.size() / 2; ++i) {
            setOfKeys.insert((*it1).key);
            ++it1;
        }

        const auto endIt = table.end();
        auto it2 = decltype(it1)(it1);
        while (it2 != endIt) {
            setOfKeys.insert((*it2).key);
            ++it2;
        }

        while (it1 != endIt) {
            setOfKeys.insert((*it1).key);
            ++it1;
        }

        this->assert_equals(keys.size(), setOfKeys.size());
    }
};

/**
 * @brief Tests table equality
 * @tparam TableT Table type
 */
template<class TableT>
class TableTestEquals : public details::TableTestBase {
public:
    TableTestEquals() : details::TableTestBase("equals", 874) {
    }

protected:
    void test() override {
        constexpr auto n = 100;
        auto table1 = TableT();
        auto table2 = TableT();
        auto keys = this->generateKeys(n);
        for (const auto key : keys) {
            table1.insert(key, key);
        }

        std::shuffle(
            keys.begin(),
            keys.begin() + keys.size() / 2,
            this->rngKey_
        );
        for (const auto key : keys) {
            table2.insert(key, key);
        }

        this->assert_true(table1.equals(table2), "Tables are equal.");
        table1.remove(keys.front());
        this->assert_true(! table1.equals(table2), "Tables are not equal.");
    }
};

/**
 * @brief Tests Table::equals for type checking
 */
template<class FirstTableT>
class TableTestEqualsTypes : public details::TableTestBase {
public:
    TableTestEqualsTypes() : details::TableTestBase("equals-types", 997) {
    }

protected:
    void test() override {
        constexpr bool IsTreap
            = std::is_same<FirstTableT, ds::adt::Treap<int, int>>::value;
        using SecondTableT = std::conditional<
            IsTreap,
            ds::adt::HashTable<int, int>,
            ds::adt::Treap<int, int>>::type;

        auto table1 = FirstTableT();
        auto table2 = SecondTableT();
        auto keys = this->generateKeys(100);
        for (const auto key : keys) {
            table1.insert(key, key);
            table2.insert(key, key);
        }

        this->assert_false(
            table1.equals(table2),
            "Tables of different types are not equal."
        );
    }
};

/**
 * @brief Tests all table operations mixed together
 * @tparam TableT Table type
 */
template<class TableT>
class TableTestScenario : public details::TableTestBase {
public:
    TableTestScenario() : details::TableTestBase("scenario", 997) {
    }

protected:
    void test() override {
        using base = details::TableTestBase;

        auto rngOp = std::mt19937_64(753);
        auto distOp = std::uniform_int_distribution<int>(0, 2);
        auto distKey = std::uniform_int_distribution<int>(0, 9999);
        auto rngKeyIndex = std::mt19937_64(654);
        auto table = TableT();
        auto keys = this->generateKeys(100);
        for (const auto key : keys) {
            table.insert(key, key);
        }

        const auto safeOpCount = static_cast<int>(keys.size());
        for (auto i = 0; i < safeOpCount; ++i) {
            const auto op = distOp(rngOp);
            switch (op) {
            case 0: // insert
                try {
                    const auto key = distKey(base::rngKey_);
                    table.insert(key, key);
                    keys.push_back(key);
                } catch (...) {
                }
                this->assert_equals(keys.size(), table.size());
                break;

            case 1: // find
            {
                auto distKeyIndex
                    = std::uniform_int_distribution<size_t>(0, size(keys) - 1);
                auto &key = keys[distKeyIndex(rngKeyIndex)];
                auto data = table.find(key);
                this->assert_equals(key, data);
            } break;

            case 2: // remove
            {
                auto distKeyIndex
                    = std::uniform_int_distribution<size_t>(0, size(keys) - 1);
                auto &key = keys[distKeyIndex(rngKeyIndex)];
                auto &lastKey = keys.back();
                auto data = table.remove(key);
                this->assert_equals(key, data);
                std::swap(key, lastKey);
                keys.pop_back();
                this->assert_equals(keys.size(), table.size());
            } break;

            default:
                // Unreachable
                std::terminate();
            }
        }
    }
};

/**
 * @brief All table leaf tests
 * @tparam TableT table ty[e
 */
template<class TableT>
class GeneralTableTest : public stest::CompositeTest {
public:
    GeneralTableTest(const std::string &name) : CompositeTest(name) {
        this->add_test(std::make_unique<TableTestInsert<TableT>>());
        this->add_test(std::make_unique<TableTestLookup<TableT>>());
        this->add_test(std::make_unique<TableTestRemove<TableT>>());
        this->add_test(std::make_unique<TableTestClear<TableT>>());
        this->add_test(std::make_unique<TableTestCopyAssign<TableT>>());
        this->add_test(std::make_unique<TableTestIterator<TableT>>());
        this->add_test(std::make_unique<TableTestEquals<TableT>>());
        this->add_test(std::make_unique<TableTestEqualsTypes<TableT>>());
        this->add_test(std::make_unique<TableTestScenario<TableT>>());
    }
};

/**
 * @brief All sequence table implementations tests
 */
class SequenceTableTest : public stest::CompositeTest {
public:
    SequenceTableTest() : CompositeTest("SequenceTable") {
        this->add_test(
            std::make_unique<
                GeneralTableTest<adt::UnsortedImplicitSequenceTable<int, int>>>(
                "UnsortedImplicitSequenceTable"
            )
        );
        this->add_test(
            std::make_unique<
                GeneralTableTest<adt::UnsortedExplicitSequenceTable<int, int>>>(
                "UnsortedExplicitSequenceTable"
            )
        );
        this->add_test(
            std::make_unique<
                GeneralTableTest<adt::SortedSequenceTable<int, int>>>(
                "SortedSequenceTable"
            )
        );
    }
};

/**
 * @brief All non-sequence table implementations tests
 */
class NonSequenceTableTest : public stest::CompositeTest {
public:
    NonSequenceTableTest() : CompositeTest("NonSequenceTable") {
        this->add_test(
            std::make_unique<GeneralTableTest<adt::HashTable<int, int>>>(
                "HashTable"
            )
        );
        this->add_test(
            std::make_unique<GeneralTableTest<adt::BinarySearchTree<int, int>>>(
                "BinarySearchTree"
            )
        );
        this->add_test(
            std::make_unique<GeneralTableTest<adt::Treap<int, int>>>("Treap")
        );
    }
};

/**
 * @brief All table tests
 */
class TableTest : public stest::CompositeTest {
public:
    TableTest() : CompositeTest("Table") {
        this->add_test(
            std::make_unique<
                GeneralTableTest<adt::UnsortedImplicitSequenceTable<int, int>>>(
                "UnsortedImplicitSequenceTable"
            )
        );
        this->add_test(
            std::make_unique<
                GeneralTableTest<adt::UnsortedExplicitSequenceTable<int, int>>>(
                "UnsortedExplicitSequenceTable"
            )
        );
        this->add_test(
            std::make_unique<
                GeneralTableTest<adt::SortedSequenceTable<int, int>>>(
                "SortedSequenceTable"
            )
        );
        this->add_test(
            std::make_unique<GeneralTableTest<adt::HashTable<int, int>>>(
                "HashTable"
            )
        );
        this->add_test(
            std::make_unique<GeneralTableTest<adt::BinarySearchTree<int, int>>>(
                "BinarySearchTree"
            )
        );
        this->add_test(
            std::make_unique<GeneralTableTest<adt::Treap<int, int>>>("Treap")
        );
    }
};

} // namespace ds::tests

#endif
