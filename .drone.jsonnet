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
			name: "everything",
			image: image,
			environment: environment,
			commands:
			[
				'set -e',
				'wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -',
			] +
			(if sources != [] then [ ('apt-add-repository "' + source + '"') for source in sources ] else []) +
			(if packages != "" then [ 'apt-get update', 'apt-get -y install ' + packages ] else []) +
			[
				'export SELF=system',
				'./.drone/drone.sh',
			]
		}
    ]
};

local macos_pipeline =
{
};

local windows_pipeline(name, image, environment, arch = "amd64") =
{
	name: name,
	kind: "pipeline",
	type: "docker",
	trigger: triggers,
	platform:
	{
		os: "windows",
		arch: arch
	},
	"steps":
	[
		{
			name: "everything",
			image: image,
			environment: environment,
			commands:
			[
				'set SELF=system',

				'set DRONE_BUILD_DIR=%CD%',
				'set BOOST_BRANCH=develop',
				'if "%DRONE_BRANCH%" == "master" set BOOST_BRANCH=master',
				'cd ..',
				'git clone -b %BOOST_BRANCH% --depth 1 https://github.com/boostorg/boost.git boost-root',
				'cd boost-root',
				'git submodule update --init tools/boostdep',
				'xcopy /s /e /q %DRONE_BUILD_DIR% libs\\\\%SELF%\\\\',
				'python tools/boostdep/depinst/depinst.py %SELF%',
				'cmd /c bootstrap',
				'b2 -d0 headers',
				'if not "%CXXSTD%" == "" set CXXSTD=cxxstd=%CXXSTD%',
				'if not "%ADDRMD%" == "" set ADDRMD=address-model=%ADDRMD%',
				'b2 -j3 libs/%SELF%/test toolset=%TOOLSET% %CXXSTD% %ADDRMD% variant=debug,release embed-manifest-via=linker',
			]
		}
	]
};

[
	linux_pipeline(
		"Linux 14.04 GCC 4.4",
		"cppalliance/droneubuntu1404:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++-4.4', CXXSTD: '98,0x' },
		"g++-4.4",
		[ "ppa:ubuntu-toolchain-r/test" ],
	),

	linux_pipeline(
		"Linux 14.04 GCC 4.6",
		"cppalliance/droneubuntu1404:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++-4.6', CXXSTD: '98,0x' },
		"g++-4.6",
		[ "ppa:ubuntu-toolchain-r/test" ],
	),

	linux_pipeline(
		"Linux 14.04 GCC 4.8*",
		"cppalliance/droneubuntu1404:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '03,11' },
	),

	linux_pipeline(
		"Linux 14.04 GCC 4.9",
		"cppalliance/droneubuntu1404:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++-4.9', CXXSTD: '03,11' },
		"g++-4.9",
		[ "ppa:ubuntu-toolchain-r/test" ],
	),

	linux_pipeline(
		"Linux 16.04 GCC 5*",
		"cppalliance/droneubuntu1604:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '03,11,14' },
	),

	linux_pipeline(
		"Linux 18.04 GCC 6",
		"cppalliance/droneubuntu1804:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++-6', CXXSTD: '03,11,14' },
		"g++-6",
	),

	linux_pipeline(
		"Linux 18.04 GCC 7* 32/64",
		"cppalliance/droneubuntu1804:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '03,11,14,17', ADDRMD: '32,64' },
	),

	linux_pipeline(
		"Linux 18.04 GCC 8",
		"cppalliance/droneubuntu1804:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++-8', CXXSTD: '03,11,14,17' },
		"g++-8",
	),

	linux_pipeline(
		"Linux 20.04 GCC 9* 32/64",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '03,11,14,17,2a', ADDRMD: '32,64' },
	),

	linux_pipeline(
		"Linux 20.04 GCC 9 ARM64 32/64",
		"cppalliance/droneubuntu2004:multiarch",
		{ TOOLSET: 'gcc', COMPILER: 'g++', CXXSTD: '03,11,14,17,2a', ADDRMD: '32,64' },
		arch="arm64",
	),

	linux_pipeline(
		"Linux 20.04 GCC 10",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'gcc', COMPILER: 'g++-10', CXXSTD: '03,11,14,17,20' },
		"g++-10",
	),

	linux_pipeline(
		"Linux 20.04 Clang 13",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'clang', COMPILER: 'clang++-13', CXXSTD: '03,11,14,17,20' },
		"clang-13",
		["deb http://apt.llvm.org/focal/ llvm-toolchain-focal-13 main"],
	),

	linux_pipeline(
		"Linux 20.04 Clang 14",
		"cppalliance/droneubuntu2004:1",
		{ TOOLSET: 'clang', COMPILER: 'clang++-14', CXXSTD: '03,11,14,17,20' },
		"clang-14",
		["deb http://apt.llvm.org/focal/ llvm-toolchain-focal-14 main"],
	),

	windows_pipeline(
		"Windows VS2015 msvc-14.0",
		"cppalliance/dronevs2015",
		{ TOOLSET: 'msvc-14.0', CXXSTD: '14,latest' },
	),
]
