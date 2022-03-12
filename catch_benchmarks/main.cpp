#include <benchmark/benchmark.h>
#include <iostream>
void SomeFunction()
{
    std::cout << 10 << std::endl;
}
static void BM_SomeFunction(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        SomeFunction();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);
// Run the benchmark
BENCHMARK_MAIN();