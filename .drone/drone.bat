@ECHO ON

set DRONE_BUILD_DIR=%CD%

IF "%DRONE_BRANCH%" == "" (
  for /F %%i in ("%GITHUB_REF%") do @set DRONE_BRANCH=%%~nxi
)

for /F %%i in ("%DRONE_REPO%") do @set SELF=%%~nxi

set BOOST_BRANCH=develop
if "%DRONE_BRANCH%" == "master" set BOOST_BRANCH=master
cd ..
git clone -b %BOOST_BRANCH% --depth 1 https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule update --init tools/boostdep
xcopy /s /e /q %DRONE_BUILD_DIR% libs\%SELF%\
python tools/boostdep/depinst/depinst.py %SELF%
cmd /c bootstrap
b2 -d0 headers

if not "%CXXSTD%" == "" set CXXSTD=cxxstd=%CXXSTD%
if not "%ADDRMD%" == "" set ADDRMD=address-model=%ADDRMD%
b2 -j3 libs/%SELF%/test toolset=%TOOLSET% %CXXSTD% %ADDRMD% variant=debug,release embed-manifest-via=linker
