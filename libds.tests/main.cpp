#include "mm/system_memory_manager.test.hpp"
#include "mm/compact_memory_trivial_manager.test.hpp"
#include "mm/compact_memory_object_manager.test.hpp"
#include "amt/implicit_sequence.test.hpp"
#include "amt/explicit_sequence.test.hpp"

#include <libstest/run.hpp>
#include <libstest/test.hpp>


int main(int argc, char *argv[]) {
    using namespace ds::tests;

    stest::CompositeTest tests("Tests");

    tests.add_test<SystemMemoryManagerTest>();
    tests.add_test<TrivialCMMTests>();
    tests.add_test<ObjectCMMTests>();

    tests.add_test<ImplicitSequenceTests>();
    tests.add_test<SinglyLinkedSequenceTests>();
    tests.add_test<DoublyLinkedSequenceTests>();

    stest::run(argc, argv, tests);
}
