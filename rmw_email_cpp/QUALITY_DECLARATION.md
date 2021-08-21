This document is a declaration of software quality for the `rmw_email_cpp` package, based on the guidelines in [REP-2004](https://www.ros.org/reps/rep-2004.html).

# `rmw_email_cpp` Quality Declaration

The package `rmw_email_cpp` claims to be in the **Quality Level 4** category.

Below are the rationales, notes, and caveats for this claim, organized by each requirement listed in the [Package Quality Categories in REP-2004](https://www.ros.org/reps/rep-2004.html).

## Version Policy [1]

### Version Scheme [1.i]
<!-- yes -->

`rmw_email_cpp` uses `semver` according to the recommendation for ROS Core packages in the [ROS 2 Developer Guide](https://docs.ros.org/en/rolling/Contributing/Developer-Guide.html#versioning).

### Version Stability [1.ii]
<!-- no -->

`rmw_email_cpp` is not yet at a stable version, i.e. `< 1.0.0`.
The current version can be found in its [package.xml](package.xml), and its change history can be found in its [CHANGELOG](CHANGELOG.rst).

### Public API Declaration [1.iii]
<!-- yes -->

`rmw_email_cpp`'s public API is [`rmw`'s public API](https://github.com/ros2/rmw/blob/master/rmw/QUALITY_DECLARATION.md#public-api-declaration-1iii).

### API Stability Within a Released ROS Distribution [1.iv]/[1.vi]
<!-- yes -->

`rmw_email_cpp` will not break public API within a released ROS distribution, i.e. no major releases once the ROS distribution is released, as per [`rmw`'s Quality Declaration](https://github.com/ros2/rmw/blob/master/rmw/QUALITY_DECLARATION.md#api-stability-within-a-released-ros-distribution-1iv1vi).

### ABI Stability Within a Released ROS Distribution [1.v]/[1.vi]
<!-- yes -->

`rmw_email_cpp` will maintain ABI stability within a ROS distribution, as per [`rmw`'s Quality Declaration](https://github.com/ros2/rmw/blob/master/rmw/QUALITY_DECLARATION.md#abi-stability-within-a-released-ros-distribution-1v1vi).

## Change Control Process [2]

`rmw_email_cpp` follows most of the recommended guidelines for ROS Core packages in the [ROS 2 Developer Guide](https://docs.ros.org/en/rolling/Contributing/Developer-Guide.html#change-control-process).

### Change Requests [2.i]
<!-- yes -->

All changes will occur through a pull request, check [ROS 2 Developer Guide](https://docs.ros.org/en/rolling/Contributing/Developer-Guide.html#change-control-process) for additional information.

### Contributor Origin [2.ii]
<!-- yes -->

This package uses DCO as its confirmation of contributor origin policy.
There is an [automated DCO check](../.github/workflows/dco.yml) for change requests.
More information can be found in [CONTRIBUTING](../CONTRIBUTING.md).

### Peer Review Policy [2.iii]
<!-- no -->

Not all pull requests are currently peer-reviewed.
<!-- , check [ROS 2 Developer Guide](https://docs.ros.org/en/rolling/Contributing/Developer-Guide.html#change-control-process) for additional information. -->

### Continuous Integration [2.iv]
<!-- yes -->

All pull requests must pass CI on Ubuntu.

### Documentation Policy [2.v]
<!-- yes -->

All pull requests must resolve related documentation changes before merging.

## Documentation [3]

### Feature Documentation [3.i]
<!-- yes -->

`rmw_email_cpp`'s feature list is based on [`rmw`'s feature list](https://github.com/ros2/rmw/blob/master/rmw/QUALITY_DECLARATION.md#feature-documentation-3i).
Some of `rmw` features are currently not supported and are [documented in this repository's README](../README.md#supported-features).

### Public API Documentation [3.ii]
<!-- yes -->

`rmw_email_cpp`'s API is based on [`rmw`'s API](https://github.com/ros2/rmw/blob/master/rmw/QUALITY_DECLARATION.md#public-api-documentation-3ii).

### License [3.iii]
<!-- yes -->

The license for `rmw_email_cpp` is Apache 2.0, and a summary is in each source file, the type is declared in the [`package.xml`](./package.xml) manifest file, and a full copy of the license is in the [`LICENSE`](../LICENSE) file.

There is an automated test using [`ament_copyright`](https://github.com/ament/ament_lint/tree/master/ament_copyright) through `ament_lint_common` that ensures each file has a license statement.

### Copyright Statements [3.iv]
<!-- yes -->

The copyright holders each provide a statement of copyright in each source code file in `rmw_email_cpp`.

There is an automated test using [`ament_copyright`](https://github.com/ament/ament_lint/tree/master/ament_copyright) through `ament_lint_common` that ensures each file has a license statement.

## Testing [4]

### Feature Testing [4.i]
<!-- no -->

All features in `rmw_email_cpp` have tests through [`rmw_implementation`](https://github.com/ros2/rmw_implementation/tree/master/rmw_implementation/test) and [`test_rmw_implementation`](https://github.com/ros2/rmw_implementation/tree/master/test_rmw_implementation/test) which simulate typical usage.
Some other feature-related unit tests are located in the [`test`](./test) directory.

Not all of those tests currently pass.

### Public API Testing [4.ii]
<!-- no -->

All parts of the public API have tests through [`rmw_implementation`](https://github.com/ros2/rmw_implementation/tree/master/rmw_implementation/test) and [`test_rmw_implementation`](https://github.com/ros2/rmw_implementation/tree/master/test_rmw_implementation/test).
The tests aim to cover both typical usage and corner cases, but are quantified by contributing to code coverage.

Not all of those tests currently pass.

### Coverage [4.iii]
<!-- yes & no -->

`rmw_email_cpp` tries to follow the recommendations for ROS Core packages in the [ROS 2 Developer Guide](https://docs.ros.org/en/rolling/Contributing/Developer-Guide.html#code-coverage), and opts to use line coverage instead of branch coverage.

This includes:

- tracking and reporting line coverage statistics
<!-- - achieving and maintaining a reasonable branch line coverage (90-100%) -->
<!-- - no lines are manually skipped in coverage calculations -->

Changes are required to make a best effort to keep or increase coverage before being accepted, but decreases are allowed if properly justified and accepted by reviewers.

Current coverage statistics can be viewed [here](https://app.codecov.io/gh/christophebedard/rmw_email).
<!-- `rmw_email_cpp` has a line coverage `>= 95%`, which is calculated over all directories within `rmw_email_cpp`. -->

### Performance [4.iv]
<!-- no -->

`rmw_email_cpp` has no performance tests.

### Linters and Static Analysis [4.v]
<!-- yes -->

`rmw_email_cpp` uses and passes all the ROS 2 standard linters and static analysis tools for a C++ package as described in the [ROS 2 Developer Guide](https://docs.ros.org/en/rolling/Contributing/Developer-Guide.html#linters-and-static-analysis).
Passing implies there are no linter/static errors when testing against CI of supported platforms.

Currently, the latest test results can be seen [here](https://github.com/christophebedard/rmw_email/actions/workflows/ci.yml).

## Dependencies [5]

Below are evaluations of each of `rmw_email_cpp`'s run-time and build-time dependencies that have been determined to influence the quality.

It has several "buildtool" dependencies, which do not affect the resulting quality of the package, because they do not contribute to the public library API.

It also has several test dependencies, which do not affect the resulting quality of the package, because they are only used to build and run the test code.

### Direct and Optional Runtime ROS Dependencies [5.i]/[5.ii]
<!-- no -->

`rmw_email_cpp` has the following runtime ROS dependencies:

#### `dynmsg`

The [`dynmsg` package](https://github.com/christophebedard/dynamic_message_introspection/tree/feature/dynmsg) provides an API to dynamically convert C and C++ messages to and from YAML.

It currently has no quality declaration.

#### `rcpputils`

The `rcpputils` package provides an API which contains common utilities and data structures useful when programming in C++.

It is **Quality Level 1**, see its [Quality Declaration document](https://github.com/ros2/rcpputils/blob/master/QUALITY_DECLARATION.md).

#### `rcutils`

The `rcutils` package provides an API which contains common utilities and data structures useful when programming in C.

It is **Quality Level 1**, see its [Quality Declaration document](https://github.com/ros2/rcutils/blob/master/QUALITY_DECLARATION.md).

#### `rmw`

The `rmw` package is itself the ROS middleware API.

It is **Quality Level 1**, see its [Quality Declaration document](https://github.com/ros2/rmw/blob/master/rmw/QUALITY_DECLARATION.md).

#### `rosidl_runtime_c`

The `rosidl_runtime_c` package provides definitions, initialization and finalization functions, and macros for getting and working with rosidl typesupport types in C.

It is **Quality Level 1**, see its [Quality Declaration document](https://github.com/ros2/rosidl/blob/master/rosidl_runtime_c/QUALITY_DECLARATION.md).

#### `rosidl_runtime_cpp`

The `rosidl_runtime_cpp` package provides definitions and templated functions for getting and working with rosidl typesupport types in C++.

It is **Quality Level 1**, see its [Quality Declaration document](https://github.com/ros2/rosidl/blob/master/rosidl_runtime_cpp/QUALITY_DECLARATION.md).

#### `rosidl_typesupport_introspection_c`

The `rosidl_typesupport_introspection_c` package provides an API to generate the message type support for dynamic message construction in C.

It currently has no quality declaration.

#### `rosidl_typesupport_introspection_cpp`

The `rosidl_typesupport_introspection_cpp` package provides an API to generate the message type support for dynamic message construction in C++.

It currently has no quality declaration.

#### `tracetools`

The `tracetools` package provides an API and tools to support instrumenting ROS packages, including core packages.

It is **Quality Level 1**, see its [Quality Declaration document](https://gitlab.com/ros-tracing/ros2_tracing/-/blob/master/tracetools/QUALITY_DECLARATION.md).

### Direct Runtime non-ROS Dependency [5.iii]
<!-- yes -->

`rmw_email_cpp` has the following run-time or build-time dependencies:

#### `email`

The `email` package provides an API to exchange strings with simple publish/subscribe & service middleware using emails.

It is **Quality Level 4**, see its [Quality Declaration document](../email/QUALITY_DECLARATION.md).

## Platform Support [6]
<!-- no -->

`rmw_email_cpp` does not currently officially support all of the tier 1 platforms as described in [REP-2000](https://www.ros.org/reps/rep-2000.html#support-tiers).

## Security

### Vulnerability Disclosure Policy [7.i]
<!-- no -->

This package has no formal Vulnerability Disclosure Policy, but it will try to conform to the policy described in [REP-2006](https://www.ros.org/reps/rep-2006.html).
Use the email address available on the profile of the owner of this repository.
~~Submit your vulnerability report using `email` directly or using ROS 2 with `rmw_email_cpp` by publishing a `std_msgs/String` message.~~

# Current Status

The table below compares the requirements in REP-2004 with the current state of the `rmw_email_cpp` package.

| Number | Requirement | Current state |
|--|--|--|
|1| **Version policy** ||
|1.i| Version policy | ✓ |
|1.ii| Stable version | x |
|1.iii| Strictly declared public API | ✓ |
|1.iv| API stability policy | ✓ |
|1.v| ABI stability policy | ✓ |
|1.vi| API/ABI stablility policy within ROS distribution | ✓ |
|2| **Change control process** ||
|2.i| All changes occur through change request | ✓ |
|2.ii| Confirmation of contributor origin | ✓ |
|2.iii| Peer review policy | x |
|2.iv| CI policy for change requests | ✓ |
|2.v| Documentation policy for change requests | ✓ |
|3| **Documentation** ||
|3.i| Per feature documentation | ✓ |
|3.ii| Public API documentation | ✓ |
|3.iii| Declared license(s) | ✓ |
|3.iv| Copyright in source files | ✓ |
|3.v.a| Quality declaration linked to from README | ✓ |
|3.v.b| Centralized declaration available for peer review |  |
|3.v.c| References any Level N lists the package belongs to | ✓ |
|4| **Testing** ||
|4.i| Feature items tests | x |
|4.ii| Public API tests | x |
|4.iii.a| Using coverage | ✓ |
|4.iii.b| Coverage policy | x |
|4.iv.a| Performance tests | x |
|4.iv.b| Performance tests policy | x |
|4.v.a| Code style enforcement (linters) | ✓ |
|4.v.b| Use of static analysis tools | ✓ |
|5| **Dependencies** ||
|5.i| Must not have lower level ROS dependencies | x |
|5.ii| Optional ROS lower level dependencies | ✓ |
|5.iii| Justifies quality use of non-ROS dependencies | ✓ |
|6| **Platform Support** ||
|6.i| Support targets tier 1 ROS platforms | x |
|7| **Security** ||
|7.i| Vulnerability Disclosure Policy | x |

Comparing this table to the [Quality Level Comparison Chart of REP-2004](https://www.ros.org/reps/rep-2004.html#quality-level-comparison-chart) led us to conclude that this package qualifies for Quality Level 4.
