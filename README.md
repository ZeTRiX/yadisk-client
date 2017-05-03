## Yandex Disk Client

### Install

```bash
$ cmake -H. -B_build
$ cmake --build _build
$ cmake --build _build --target install
```

### Usage

```cmake
hunter_add_package(yadisk-client)
find_package(yadisk-client)

target_link_library(... yadisk-client::ydclient)
```
