# Core

## Third-party Sources (第三方代码)

There some sources in this directory are modified from repository <https://github.com/capdevc/toyfs> 
(it is licensed under MIT license).   
And I added following comment line in the front of these file.

``` cpp
// This code is modified from https://github.com/capdevc/toyfs (Original repository is licensed under MIT license)
``` 

这个目录下有一些源代码文件是改自仓库 <https://github.com/capdevc/toyfs>. 我在这些文件的开头标注了出处.

## Structure (结构)

- `FSEntry`: (Directory/File)
	- `FSInode`: Inode
		- `FSDataBlock`: Data block
			- `****Device`: StorageDevice
