# a + b

``` bash
# install WABT: (The WebAssembly Binary Toolkit)
git clone --recursive https://github.com/WebAssembly/wabt.git
mkdir wabt/build
cd wabt/build
cmake ..
make -j8
sudo make install

# convert program.wat to program.wasm
wat2wasm program.wat -o program.wasm
```
