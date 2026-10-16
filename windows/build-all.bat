@echo off
for %%x in (%*) do (
    if "%%x"=="32" set do32=1
    if "%%x"=="64" set do64=1
    if "%%x"=="dec" set dodec=1
    if "%%x"=="bin" set dobin=1
)
if not "%do32%"=="1" (
    if not "%do64%"=="1" (
        set do32=1
        set do64=1
    )
)
if not "%dodec%"=="1" (
    if not "%dobin%"=="1" (
        set dodec=1
        set dobin=1
    )
)

call vcvars32
call copy-files
rmdir /s /q Release
msbuild keymap2cpp.vcxproj /p:Configuration=Release
Release\keymap2cpp
rmdir /s /q Release
msbuild skin2cpp.vcxproj /p:Configuration=Release
Release\skin2cpp

if "%do32%"=="1" (
    rmdir /s /q 32
    mkdir 32
    if "%dobin%"=="1" (
        rmdir /s /q Release
        msbuild Free42Binary32.vcxproj /p:Configuration=Release
        move Release\Free42Binary.exe 32
    )
    if "%dodec%"=="1" (
        rmdir /s /q Release
        msbuild Free42Decimal32.vcxproj /p:Configuration=Release
        move Release\Free42Decimal.exe 32
    )
)
if "%do64%"=="1" (
    call vcvars64
    if "%dobin%"=="1" (
        rmdir /s /q Release
        msbuild Free42Binary64.vcxproj /p:Configuration=Release
        move Release\Free42Binary.exe .
    )
    if "%dodec%"=="1" (
        rmdir /s /q Release
        msbuild Free42Decimal64.vcxproj /p:Configuration=Release
        move Release\Free42Decimal.exe .
    )
)
rmdir /s /q Release
