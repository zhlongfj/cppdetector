#include "../doctest.h"
#include "../nanobench.h"
#include <random>
namespace {

// Benchmarks how fast we can get 64bit random values from Rng.
template <typename Rng>
void bench(ankerl::nanobench::Bench* bench, char const* name) {
    std::random_device dev;
    Rng rng(dev());

    bench->run(name, [&]() {
        auto r = std::uniform_int_distribution<uint64_t>{}(rng);
        ankerl::nanobench::doNotOptimizeAway(r);
    });
}

} // namespace

TEST_CASE("example_random_number_generators") {
    // perform a few warmup calls, and since the runtime is not always stable
    // for each generator, increase the number of epochs to get more accurate
    // numbers.
    ankerl::nanobench::Bench b;
    b.title("Random Number Generators")
        .unit("uint64_t")
        .warmup(100)
        .relative(true);
    b.performanceCounters(true);

    // sets the first one as the baseline
    bench<std::default_random_engine>(&b, "std::default_random_engine");
    bench<std::mt19937>(&b, "std::mt19937");
    bench<std::mt19937_64>(&b, "std::mt19937_64");
    bench<std::ranlux24_base>(&b, "std::ranlux24_base");
    bench<std::ranlux48_base>(&b, "std::ranlux48_base");
    bench<std::ranlux24>(&b, "std::ranlux24_base");
    bench<std::ranlux48>(&b, "std::ranlux48");
    bench<std::knuth_b>(&b, "std::knuth_b");
    bench<ankerl::nanobench::Rng>(&b, "ankerl::nanobench::Rng");
}

#include <iostream>
#include <set>

TEST_CASE("tutorial_complexity_set_find") {
    // Create a single benchmark instance that is used in multiple benchmark
    // runs, with different settings for complexityN.
    ankerl::nanobench::Bench bench;

    // a RNG to generate input data
    ankerl::nanobench::Rng rng;

    std::set<uint64_t> set;

    // Running the benchmark multiple times, with different number of elements
    for (auto setSize :
        { 10U, 20U, 50U, 100U, 200U, 500U, 1000U, 2000U, 5000U, 10000U }) {

        // fill up the set with random data
        while (set.size() < setSize) {
            set.insert(rng());
        }

        // Run the benchmark, provide setSize as the scaling variable.
        bench.complexityN(set.size()).run("std::set find", [&] {
            ankerl::nanobench::doNotOptimizeAway(set.find(rng()));
            });
    }

    // calculate BigO complexy best fit and print the results
    std::cout << bench.complexityBigO() << std::endl;
}

TEST_CASE("tutorial_render_simple") {
    std::atomic<int> x(0);

    ankerl::nanobench::Bench()
        .output(nullptr)
        .run("std::vector",
            [&] {
                ++x;
            })
        .render(ankerl::nanobench::templates::csv(), std::cout);
}

#include <fstream>
#include <random>

namespace {

void gen(std::string const& typeName, char const* mustacheTemplate,
    ankerl::nanobench::Bench const& bench) {

    std::ofstream templateOut("mustache.template." + typeName);
    templateOut << mustacheTemplate;

    std::ofstream renderOut("mustache.render." + typeName);
    ankerl::nanobench::render(mustacheTemplate, bench, renderOut);
}

} // namespace

TEST_CASE("tutorial_mustache") {
    ankerl::nanobench::Bench bench;
    bench.title("Benchmarking std::mt19937_64 and std::knuth_b");

    std::mt19937_64 rng1;
    bench.run("std::mt19937_64", [&] {
        ankerl::nanobench::doNotOptimizeAway(rng1());
        });

    std::knuth_b rng2;
    bench.run("std::knuth_b", [&] {
        ankerl::nanobench::doNotOptimizeAway(rng2());
        });

    gen("json", ankerl::nanobench::templates::json(), bench);
    gen("html", ankerl::nanobench::templates::htmlBoxplot(), bench);
    gen("csv", ankerl::nanobench::templates::csv(), bench);
}