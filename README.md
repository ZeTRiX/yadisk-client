## Yandex Disk Client

### Install

```bash
$ cmake -H. -B_build
$ cmake --build _build
$ cmake --build _build --target install
```

### Usage

```cmake

include("cmake/HunterGate.cmake")
HunterGate(
    URL  "https://github.com/yadisk-operations/hunter/archive/v0.18.47.1.tar.gz"
    SHA1 "f0524772c8b1c226ff4ef8d1474aecc27e85987e"
    LOCAL
)

hunter_add_package(yadisk-client)
find_package(yadisk-client)

target_link_library(... yadisk-client::ydclient)
```
