cc_library(
    name = "bad_input-lib",
    hdrs = ["bad_input.h"],
    visibility = ["//core:__pkg__"],
)

cc_library(
    name = "vehicle-lib",
    srcs = ["vehicle.cc"],
    hdrs = ["vehicle.h"],
)

cc_library(
    name = "problem_map-lib",
    srcs = ["problem_map.cc"],
    hdrs = ["problem_map.h"],
    deps = [":vehicle-lib"],
)

cc_library(
    name = "datetime-lib",
    hdrs = ["datetime.h"],
    srcs = ["datetime.cc"],
    visibility = ["//core:__pkg__"]
)

cc_library(
    name = "order-lib",
    srcs = ["order.cc"],
    hdrs = ["order.h"],
    visibility = ["//core:__pkg__"],
    deps = [
        ":bad_input-lib",
        ":problem_map-lib",
        ":vehicle-lib",
        ":datetime-lib",
    ],
)
