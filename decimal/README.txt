IntelRDFPMathLib20U1.tar.gz

This is version 2.0u1 of the Intel Decimal Floating-Point Math Library, used to
build the FP_INTEL target. Note that there is a later version, 2.0u2, but I'm
not using it because the bugs that it fixes are all bugs that I already have
workarounds for, or that don't affect Free42 to begin with. On top of that,
there are enough changes throughout the code that I would have to completely
redo my patch scripts, and those were a royal pain to create. No thanks. :-)

decNumber.tgz

This is a subset of the files from decNumber-icu-368.zip, used to build the
FP_DECNUM target. The patches from decNumber368-patches-20210522.zip have been
applied.
