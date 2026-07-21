# C:\Users\20241427\RustroverProjects\EmbeddedPeach\dfu-util-0.11-binaries\win64\dfu-util.exe -a 0 -s 0x08000000:leave -D target/thumbv7em-none-eabihf/release/EmbeddedPeach.bin

# dfu-util -l
dfu-util -a 0 -s 0x08000000:leave -D build/EmbeddedPeach.bin
