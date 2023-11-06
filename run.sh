#!/bin/bash

# if you have windows or ubuntu use this
#sudo qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 #-soundhw pcspk
# if you have macOs use this
#qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev coreaudio,id=audio0 -machine pcspk-audiodev=audio0 #if it doesnt work change sdl for coreaudio

if [[ "$1" == "gdb" ]];
then
     qemu-system-x86_64 -s -S -hda Image/x64BareBonesImage.qcow2 -m 512 -d int
elif [[ "$1" == "-na" ]]; #no audio
then
     qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -soundhw pcspk
else
     qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512
fi