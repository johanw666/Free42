IntelRDFPMathLib20U1.tar.gz

This is version 2.0u1 of the Intel Decimal Floating-Point Math Library, used to
build the FP_INTEL and FP_BINARY_INTEL targets. Note that there is a later
version, 2.0u2, but I'm not using it because the bugs that it fixes are all
bugs that I already have workarounds for, or that don't affect Free42 to begin
with.

intel-conv.tgz

This is an excerpt from the Intel library, containing only the conversion
functions needed by the FP_DECNUM and FP_BINARY targets.

decNumber.tgz

This is a subset of the files from decNumber-icu-368.zip, used to build the
FP_DECNUM target. The patches from decNumber368-patches-20210522.zip have been
applied.

wp34s-math.cc
wp34s-math.h

decNumber-based functions for use with the decNumber library, by Paul Dale,
copied from the WP 34S calculator project. The original files are called decn.c
and decn.h, respectively. The versions here were slightly modified to compile
only the functions Free42 requires.
