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
    URL  "https://github.com/yadisk-operations/hunter/archive/v0.18.47.1.tar.gz"
    SHA1 "f0524772c8b1c226ff4ef8d1474aecc27e85987e"
    LOCAL
)

hunter_add_package(yadisk-client)
find_package(yadisk-client)

target_link_library(... yadisk-client::ydclient)
EOF
```

```bash
$ cat > cmake/Hunter/config.cmake <<EOF
hunter_config(OpenSSL VERSION 1.0.2j)
EOF
```
