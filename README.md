## Yandex Disk Client

### Install

```bash
$ cmake -H. -B_build
$ cmake --build _build
$ cmake --build _build --target install
```

### Usage

```bash
$ cat >> CMakeLists.txt <<EOF
include("cmake/HunterGate.cmake")
HunterGate(
    URL  "https://github.com/yadisk-ops/hunter/archive/v0.18.47.2.tar.gz"
    SHA1 "fe0f3a4d337ae08dbea640fd1ebc1e448919fcd3"
    LOCAL
)

hunter_add_package(yadisk-client)
find_package(yadisk-client)

target_link_libraries(... yadisk-client::yadisk-client)
EOF
```

```bash
$ cat > cmake/Hunter/config.cmake <<EOF
hunter_config(OpenSSL VERSION 1.0.2j)
EOF
```

```bash
$ cat > sources/main.cpp
#include <yadisk/client.hpp>
EOF
```
