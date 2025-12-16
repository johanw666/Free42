#!/bin/sh -e

if [ $# -ne 1 ]
then
    echo "Usage: $0 (32|64)"
    exit 1
fi

if [ -f cl111libbid$1.lib ]; then exit 0; fi

TOOLSET=`grep PlatformToolset Free42Decimal$1.vcxproj | head -1 | sed 's/^.*>v\([0-9]*\)<.*$/\1/'`
TOOLSETVER=
for TOOLSETDIR in `ls /cygdrive/c/Program\ Files/Microsoft\ Visual\ Studio/18/Community/VC/Tools/MSVC`
do
    TOOLSETNUMBER=`echo $TOOLSETDIR | sed 's/\([0-9][0-9]\)\.\([0-9]\).*/\1\2/'`
    if [ $TOOLSETNUMBER -ge $TOOLSET ]
    then
        TOOLSETVER=`echo $TOOLSETDIR | sed 's/^\(.....\).*$/\1/'`
        break
    fi
done

rm -rf IntelRDFPMathLib20U1
tar xvfz ../inteldecimal/IntelRDFPMathLib20U1.tar.gz
cd IntelRDFPMathLib20U1
patch -p0 <../intel-lib-windows.patch
cd LIBRARY

cmd /c ..\\..\\build-intel-lib.bat $1 $TOOLSETVER
mv libbid.lib ../../cl111libbid$1.lib
cd ../..
( echo '#ifdef FREE42_FPTEST'; echo 'const char *readtest_lines[] = {'; tr -d '\r' < IntelRDFPMathLib20U1/TESTS/readtest.in | sed 's/^\(.*\)$/"\1",/'; echo '0 };'; echo '#endif' ) > readtest_lines.cpp
cp IntelRDFPMathLib20U1/TESTS/readtest.c .
