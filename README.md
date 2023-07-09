# jwtpp
JSON Object Signing and Encryption library for C++

<a href="https://jwt.io"> <img src="https://jwt.io/img/badge-compatible.svg?sanitize=true" width="80"/></a>

#### Dependencies:
  - [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
  - OpenSSL

#### Built and tested with:
  - GCC
    - C++11
    - С++14
    - С++17
  - СLang
    - C++11
    - С++14
    - С++17

#### Supported features:
  - Sign
  - Verify

#### Supported algorithms
|Alg|Status|
|:---:|:------:|
| HS256 | **Supported** |
| HS384 | **Supported** |
| HS512 | **Supported** |
| RS256 | **Supported** |
| RS384 | **Supported** |
| RS512 | **Supported** |
| ES256 | **Supported** |
| ES384 | **Supported** |
| ES512 | **Supported** |
| PS256 | **Supported** |
| PS384 | **Supported** |
| PS512 | **Supported** |
| EdDSA | **Supported** |

#### Claims
|Claim|Options|Status|
|:---:|:---:|:----:|
|**_ess_**|set,verify| **Supported** 
|**_sub_**|set,verify| **Supported** 
|**_aud_**|set,verify| **Supported** 
|**_exp_**|set,verify| **Supported** 
|**_nbf_**|set,verify| **Supported** 
|**_iat_**|set,verify| **Supported** 
|**_jti_**|set,verify| **Supported** 

### How to use
Refer to tests dir

### How to build/install
#### CMake sources deps
add_subdirectory(<path to>)
#### System-wide installation
On MacOS OPENSSL_ROOT_DIR might need to be specified. Add `-DOPENSSL_ROOT_DIR=$(brew --prefix openssl)` to cmake stage

```bash
git clone https://github.com/dev-el/jwtpp
mkdir build && cd build
cmake -Wno-dev -DCMAKE_INSTALL_PREFIX=<install prefix> ..
make install
```

### TODO
- Documentation
- Examples
- Tests

## How to contribute
Just do it! :)
