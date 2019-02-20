echo off
cd shaders
for /r %%i in (*.frag, *.vert) do %VULKAN_SDK%\Bin\glslangValidator.exe -V %%i