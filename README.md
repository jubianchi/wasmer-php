<div align="center">
  <a href="https://wasmer.io" target="_blank" rel="noopener noreferrer">
    <img width="300" src="https://raw.githubusercontent.com/wasmerio/wasmer/master/assets/logo.png" alt="Wasmer logo">
  </a>
  
  <h1>Wasmer PHP</h1>
  
  <p>
    <a href="https://github.com/wasmerio/llvm-custom-builds/actions?query=workflow%3A%22Build%22">
      <img src="https://github.com/wasmerio/llvm-custom-builds/workflows/Build/badge.svg" alt="Build Status">
    </a>
    <a href="https://github.com/wasmerio/llvm-custom-builds/blob/master/LICENSE">
      <img src="https://img.shields.io/github/license/wasmerio/llvm-custom-builds.svg" alt="License">
    </a>
  </p>

  <h3>
    <a href="https://wasmer.io/">Website</a>
    <span> • </span>
    <a href="https://docs.wasmer.io">Docs</a>
    <span> • </span>
    <a href="https://slack.wasmer.io/">Slack Channel</a>
  </h3>

</div>

<hr/>

A complete and mature WebAssembly runtime for PHP based on [Wasmer].

**You are seeing the readme for the latest Wasmer Go version, if you are using an older version, please go to:**
* [1.0.0-alpha1]

[Wasmer]: https://github.com/wasmerio/wasmer
[1.0.0-alpha1]: https://github.com/wasmerio/wasmer-php/tree/1.0.0-alpha1/README.md

# Features

* **Easy to use**: The `wasmer` API mimics the standard WebAssembly C API,
* **Fast**: `wasmer` executes the WebAssembly modules as fast as possible, close to **native speed**,
* **Safe**: All calls to WebAssembly will be fast, but more importantly, completely safe and sandboxed.

# Install

To install the library, follow the classical:

```bash
git clone https://github.com/wasmerio/wasmer-php
cd wasmer-php
phpize
./configure --enable-wasmer
make
make test
make install
```

> Note: Wasmer doesn't work on Windows yet.

# Examples

```php
<?php declare(strict_types=1);

$engine = wasm_engine_new();
$store = wasm_store_new($engine);
$wasm = file_get_contents(__DIR__ . DIRECTORY_SEPARATOR . 'hello.wasm');
$module = wasm_module_new($store, $wasm);

function hello_callback() {
    echo 'Calling back...' . PHP_EOL;
    echo '> Hello World!' . PHP_EOL;

    return null;
}

$functype = wasm_functype_new(new Wasm\Vec\ValType(), new Wasm\Vec\ValType());
$func = wasm_func_new($store, $functype, 'hello_callback');
wasm_functype_delete($functype);

$extern = wasm_func_as_extern($func);
$externs = new Wasm\Vec\Extern([$extern]);
$instance = wasm_instance_new($store, $module, $externs);

wasm_func_delete($func);

$exports = wasm_instance_exports($instance);
$run = wasm_extern_as_func($exports[0]);

wasm_module_delete($module);
wasm_instance_delete($instance);

$results = wasm_func_call($run, new Wasm\Vec\Val());

wasm_store_delete($store);
wasm_engine_delete($engine);
```

This example covers the most basic Wasm use case: we take a Wasm module (in its text representation form), create
an instance from it, get an exported function and run it.

You can go through more advanced examples in the [dedicated directory][examples].

[examples]: ./examples

# Supported platforms and features

## Platforms

| Platform | Architecture | Status |
|----------|--------------|:------:|
| Linux    | `amd64`      | ✅      |
| Linux    | `aarch64`    | ❌      |
| Windows  | `amd64`      | ❌      |
| Darwin   | `amd64`      | ✅      |
| Darwin   | `aarch64`    | ❌      |

| PHP | Status |
|-----|:------:|
| 8.0 | ✅      |
| 7.4 | ❌      |
| 7.3 | ❌      |

## Features

## Compilers and engines

| Compiler   | Status |
|------------|:------:|
| Cranelift  | ❌      |
| LLVM       | ❌      |
| Singlepass | ✅      |

| Engine      | Status |
|-------------|:------:|
| Native      | ✅      |
| JIT         | ✅      | 
| Object File | ❌      |

## Runtime

| Object      | Status |
|-------------|:------:|
| config      | ✅      |
| engine      | ✅      | 
| store       | ✅      |

## Types

| Type       | Status |
|------------|:------:|
| valtype    | ✅      |
| functype   | ✅      |
| globaltype | ✅      |
| tabletype  | ✅      |
| memorytype | ✅      |
| externtype | ✅      |
| importtype | ✅      |
| exporttype | ✅      |

## Objects

| Object | Status |
|----------|:------:|
| val      | ✅      |
| frame    | ✅      |
| trap     | ✅      |
| foreign  | ✅      |
| module   | ✅      |
| func     | ✅      |
| global   | ✅      |
| table    | ✅      |
| memory   | ✅      |
| extern   | ✅      |
| instance | ✅      |

## Misc

| Feature           | Status |
|-------------------|:------:|
| WAT               | ✅      |
| WASI              | ❌      |
| Cross Compilation | ❌      |

# License

The entire project is under the MIT License. Please read [the
`LICENSE` file][license].


[license]: https://github.com/wasmerio/wasmer/blob/master/LICENSE