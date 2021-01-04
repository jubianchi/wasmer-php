--TEST--
GlobalType API: Wasm\Vec\GlobalType::offsetSet()

--FILE--
<?php
$valtype1 = wasm_valtype_new(WASM_I32);
$globaltype1 = wasm_globaltype_new($valtype1, WASM_CONST);
$valtype2 = wasm_valtype_new(WASM_I32);
$globaltype2 = wasm_globaltype_new($valtype2, WASM_CONST);
$valtypes = [$globaltype1];
$vec = new Wasm\Vec\GlobalType($valtypes);
var_dump($vec[0]);
var_dump($vec[1]);

$vec[1] = $globaltype2;
var_dump($vec[1]);
--EXPECTF--
resource(%d) of type (wasm_globaltype_t)
NULL
resource(%d) of type (wasm_globaltype_t)
