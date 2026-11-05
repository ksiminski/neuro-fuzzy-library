# GrIMP: granular imputation of missing data

`ksi::data_modifier_imputer_granular` fills missing numerical attributes using
Gaussian information granules learned from the complete rows of the input
dataset. It implements the existing `data_modifier` interface: call `modify`,
use it through a `data_modifier` pointer, or compose it with `addModifier`.

## Algorithm

1. Separate complete rows from incomplete rows.
2. Partition only the complete rows with the supplied `partitioner` (for example,
   `ksi::fcm`).
3. For each incomplete row and each granule, replace its missing attributes
   temporarily with that granule's centres.
4. Compute Gaussian attribute memberships
   `exp(-0.5 * ((x - centre) / spread)^2)` and aggregate them with the supplied
   t-norm. The temporary values have membership 1, so only observed attributes
   distinguish granules.
5. Fill each missing attribute with the membership-weighted average of the
   corresponding granule centres.

A zero spread is interpreted as a singleton: membership is 1 at its centre and
0 elsewhere. A wholly missing row receives the unweighted mean of the granule
centres, provided the dataset contains complete rows to build those granules.
The mean is over granules, without weighting by cluster size.

Observed values, row order, IDs, labels, decisions, weights, and other row
metadata are preserved. GrIMP follows the original implementation's metadata
semantics; it does not assign the reduced weights/new IDs used by some other
imputers. Imputed attributes become existing crisp numbers.

## Use

Include `source/common/data-modifier-imputer-granular.h` in your application.
The partitioner and t-norm are cloned on construction; copies and `clone()`
also own independent copies of these strategies.

```cpp
ksi::fcm partitioner(2, 100); // granules, clustering iterations
ksi::t_norm_product tnorm;
ksi::data_modifier_imputer_granular grimp(partitioner, tnorm);
grimp.modify(data);
```

Missingness uses `number::exists()`, as elsewhere in the library. Use the
incomplete-data reader or `datum::make_attribute_incomplete(index)` to mark
missing attributes; an unmarked NaN is invalid input.

The complete runnable example in [examples/grimp.cpp](../examples/grimp.cpp)
constructs its data in memory and prints an imputed value of `20`:

```sh
bash ./configure
make -C source _release
make -C source -j4 _release/main
make -C source example-grimp
make -C source test-grimp
```

The project uses GNU Make and a C++23 compiler with `std::format` support
(tested with GCC 13 on Ubuntu 24.04). `configure` contains compiler settings;
the checked-in `source/makefile` supplies the actual build rules.

`get_number_of_complete_items_in_dataset()` and
`get_number_of_incomplete_items_in_dataset()` describe the input to the last
successful call, before filling its missing values; do not rely on these counts
after a failure. Empty and already complete datasets skip partitioning and still
reach the next chained modifier.

## Preconditions and limitations

- Input must be rectangular, with finite observed values. At least one complete
  row is required if anything needs imputing.
- The partitioner must return a nonempty partition with one Gaussian descriptor
  per input attribute, finite centres and finite, nonnegative spreads.
  The imputer reads these from the existing cluster descriptor API.
- Partitioning parameters and degeneracies remain the responsibility of the
  supplied partitioner. In particular, the current FCM can produce non-finite
  parameters on degenerate inputs (such as zero-distance centres); GrIMP rejects
  those results instead of filling the dataset with NaNs.
- If every membership is zero, including from Gaussian/product underflow or a
  t-norm with zero support, `modify` throws `ksi::exception`. It does not silently
  fall back to a different imputation method. Small *nonzero* weights are scaled
  before averaging. Invalid t-norm outputs also throw.
- GrIMP computes a complete result before replacing the input. Its own failures
  leave input values and missingness unchanged and do not invoke the next
  modifier. A subsequent modifier has its own exception semantics.
- Each call fits granules to its own input; this is not a separate fit/transform
  API. For supervised evaluation, keep training and held-out data separate and
  exclude target labels from the attributes used for imputation.
- FCM initialization is stochastic. The numerical regression tests use known
  partitions; a separate one-cluster FCM test checks integration without relying
  on a particular random initialization. This contribution does not establish
  benchmark accuracy or superiority over other imputers.

## Verification

`make -C source test-grimp` runs ten groups of regression tests covering numerical
imputation with product and minimum t-norms, complete-row-only training,
metadata preservation, wholly missing rows, empty/complete input, reuse and
chaining, copy/clone/move ownership, zero spreads, invalid inputs and atomic
failure, small weights/large centres, and integration with FCM. It exits nonzero
on a failed check, including in release builds.

For an AddressSanitizer/UndefinedBehaviorSanitizer build, use fresh debug
objects (or a separate build directory):

```sh
make -C source _debug
make -C source -j4 _debug/main debug=-g \
  optyDebug="-O1 -fno-omit-frame-pointer" sanitizer="-fsanitize=address,undefined"
make -C source test-grimp test_folder=_debug \
  test_flags="-g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer"
```

## Provenance and upstream integration

This is a focused port of Konrad Wnuk and Krzysztof Simiński's implementation on
[`vnuczek/neuro-fuzzy-library:fcm`](https://github.com/vnuczek/neuro-fuzzy-library/tree/8ae4e3fde2c3cd558eb3c69f26cede5359bc165a),
whose GrIMP development began in August 2024. The `badania` branch merged that
work and uses it in experiments 027/127/227; its later imputer changes add
diagnostics and exception context rather than a different algorithm.

The port is based on upstream `master` at
`d63323eb2b9eca6ffd5bfb4dcf21f021f28f7c5d`. It retains the centre estimates,
Gaussian memberships, configurable t-norm, and weighted averaging from `fcm`,
while using upstream's `description`/`print`, `dataset::set`,
`number::exists`, and Gaussian descriptor accessors. It therefore does not
require the fork's broad modifier-interface changes, extra datum setters, or
duplicated partition fuzzification matrix. The original branches and commit
history are preserved; research datasets, results, and experiment runners are
not part of this port.
