# Copyright 2022 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

local triggers =
{
	branch: [ "master", "develop", "feature/*" ]
};

local linux_pipeline(name, image, environment, packages = "", sources = [], arch = "amd64") =
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
				'set -e'
			] +
			(if sources != [] then [ ('apt-add-repository "' + source + '"') for source in sources ] else []) +
			(if packages != "" then [ "apt-get update; apt-get -y install " + packages ] else []) +
			[
				'SELF=system',

				'DRONE_BUILD_DIR=$(pwd)',
				'BOOST_BRANCH=develop',
				'if [ "$DRONE_BRANCH" = "master" ]; then BOOST_BRANCH=master; fi',
				'cd ..',
				'git clone -b $BOOST_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root',
				'cd boost-root',
				'git submodule update --init tools/boostdep',
				'cp -r $DRONE_BUILD_DIR/* libs/$SELF',
				'python tools/boostdep/depinst/depinst.py $SELF',
				'./bootstrap.sh',
				'./b2 -d0 headers',

				'echo "using $TOOLSET : : $COMPILER ;" > ~/user-config.jam',
				'./b2 -j3 libs/$SELF/test toolset=$TOOLSET cxxstd=$CXXSTD variant=debug,release ${ADDRMD:+address-model=$ADDRMD} ${UBSAN:+cxxflags=-fsanitize=undefined cxxflags=-fno-sanitize-recover=undefined linkflags=-fsanitize=undefined define=UBSAN=1 debug-symbols=on} ${LINKFLAGS:+linkflags=$LINKFLAGS}'
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
		"Linux 18.04 GCC 8",
		"cppalliance/droneubuntu1804:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '14', ADDRMD: '64' },
		"gcc-8",
	),

	linux_pipeline(
		"Linux 20.04 GCC 9",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '17', ADDRMD: '64' },
	),

	linux_pipeline(
		"Linux 20.04 GCC 9+",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '17', ADDRMD: '64' },
		"gcc-9",
	),

	linux_pipeline(
		"Linux 20.04 GCC 9 ARM",
		"cppalliance/droneubuntu2004:multiarch",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '17', ADDRMD: '64' },
		arch="arm64",
	),

	linux_pipeline(
		"Linux 20.04 Clang 13",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'clang', COMPILER: 'clang++-13', CXXSTD: '17', ADDRMD: '64' },
		"clang-13",
		["deb http://apt.llvm.org/focal/ llvm-toolchain-focal-13 main"],
	),
]
