# Copyright 2022 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

local triggers =
{
	branch: [ "master", "develop", "feature/*" ]
};

local linux_pipeline(name, image, environment, arch = "amd64", sources = "", packages = "") =
{
	name: name,
    kind: "pipeline",
    type: "docker",
    trigger: triggers,
    platform:
    {
		os: "linux",
		arch: arch
    },
    steps:
    [
		{
			"name": "everything",
			"image": image,
			"environment": environment,
			"commands":
			[
				"uname -a",
				if sources != "" then "apt-add-repository " + sources else "",
				if packages != "" then "apt-get install " + packages else "",
			]
		}
    ]
};

local macos_pipeline =
{
};

local windows_pipeline =
{
};

[
	linux_pipeline(
		"Linux 20.04 GCC 9",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '03,11,14,17,2a', ADDRMD: '32,64' }
	),
]
