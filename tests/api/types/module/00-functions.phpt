--TEST--
Module API functions

--FILE--
<?php

var_dump(
    function_exists('wasm_module_new'),
    function_exists('wasm_module_delete'),
    function_exists('wasm_module_validate'),
    function_exists('wasm_module_imports'),
    function_exists('wasm_module_exports'),
    function_exists('wasm_module_serialize'),
);

--EXPECTF--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
