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
				'SELF=system',

				if sources != "" then "apt-add-repository " + sources else "",
				if packages != "" then "apt-get install " + packages else "",

				'DRONE_BUILD_DIR=$(pwd)',
				'BOOST_BRANCH=develop && [ "$DRONE_BRANCH" == "master" ] && BOOST_BRANCH=master || true',
				'cd ..',
				'git clone -b $BOOST_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root',
				'cd boost-root',
				'git submodule update --init tools/boostdep',
				'cp -r $DRONE_BUILD_DIR/* libs/$SELF',
				'python tools/boostdep/depinst/depinst.py $SELF',
				'./bootstrap.sh',
				'./b2 headers',

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
		"Linux 20.04 GCC 9",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '03,11,14,17,2a', ADDRMD: '32,64' }
	),
]
