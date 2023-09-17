# Ubuntu + vscode  + cmake 平台编写c++

## CMake 重要指令
1. cmake_minimum_required -指定CMake的最小版本要求
```c++
    cmake_minimum_required(VERSION 2.8.3)
```
2. project -定义工程名称，可指定工程支持语言
```c++
    project(projectName [CXX][C][Java])
```
3. set -显式的定义变量
```c++
    set(setName xxx1.cpp xxx2.cpp)  setName为变量名
```
4. include_directories  添加头文件搜索路径
```c++
    include_directories(/../../../include ./inlcude) //多个路径
```
5. link_directories -向工程添加多个特定的库文件搜索路径，添加lib 、a文件
```c++
    link_directories(../../user/lib/debug  ./lib/debug) //多个lib路径
```

6. add_library -生产库文件，指定生产文件名及动态库dll名称
```c++
  add_library(libname [SHARED|STATIC|MODULE|EXCLUDE_FROM_ALL] source1 source2)
    //SHARED 为动态库  STATIC 静态库
  set(SRC xxx1.cpp xxx2.cpp)
  add_library(hello SHARED ${SRC})  //生产一个hello的动态库 
```

7. aaadd_complie_options -添加编译参数
```c++
    add_complie_options(-Wall -std=c++11 -o2)
```

8. add_executable -生产可执行文件
```c++
    add_executable(exeNamme source1 source2 ...)
```

9. target_link_libraries -为target添加需要链接的共享库

```c++
    target_link_libraries(target library1<debug | release>  library2 ...)

    如：
    add_library(hello shared ${SRC})
    add_executable(exeName source1 source2 ...)
    target_link_libraries(exeName hello)  将hello动态库链接到 exeName可执行文件里
```

10. add_subdirectory -向当前工程添加存放源文件的子目录，并可以指令中间二进制和目标二进制存放的位置

```c++
    add_subdirectory(source_dir [binary_dir][EXECLUDE_FROM_ALL])

    add_subdirectory(src)  // src 为子目录 ，src需要有一个CMakeLists.txt
```

1.  aux_source_directory -发现一个目录下所有源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表
```c++
    aux_source_directory(dir VARIABLE)

    //定义SRC变量，其值为当前目录下所有源代码文件
    aux_source_directory(. SRC)

    //编译SRC变量所代表的源代码文件，生产main可执行文件
    add_executable(main {SRC})
```

## Cmake常用变量

* CMAKE_C_FLAGS gcc编译选项
* CMAKE_CXX_FLAGS G++编译选项

```c++
    在CMAKE_CXX_FLAGS 编译选项后追加 -std=c++11
    set(CMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS}" -std=c++11)
```
* CMAKE_BUILD_TYPE 编译类型(Debug , Release)
```c++
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_BUILD_TYPE Release)
```

* CMAKE_SOURCE_DIR / PROJECT_SOURCE_DIR / _SOURCE_DIR
  不论采用何种编译方式、都是工程顶层目录


* CMAKE_C_COMPILER:指定c 编译器
* CMAKE_CXX_COMPILER:指定c++编译器
* EXECUTABLE_OUTPUT_PATH ：可执行文件输出的存放路径
* LIBRARY_OUTPUT_PATH:库文件输出的存放路径


## CMake编译工程