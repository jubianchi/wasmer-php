<?php

$vec = new Wasm\Vec\ValType();
$vec = new Wasm\Vec\ValType(2);
var_dump($vec);
var_dump(count($vec));

$valtype1 = wasm_valtype_new(WASM_I32);
$valtype2 = wasm_valtype_new(WASM_I64);
$valtype3 = wasm_valtype_new(WASM_F32);
$valtypes = [$valtype1, $valtype2, $valtype3];
$vec = new Wasm\Vec\ValType(count($valtypes) + 1, $valtypes);
//var_dump($vec);
//var_dump(count($vec));
var_dump(isset($vec[0]), $vec[0]);
var_dump(isset($vec[0]), $vec[0]);

var_dump(isset($vec[1]), $vec[1]);
var_dump(isset($vec[1]), $vec[1]);

var_dump(isset($vec[2]), $vec[2]);
var_dump(isset($vec['foo']), $vec['foo']);

/*
$vec[3] = wasm_valtype_new(WASM_F64);
var_dump(isset($vec[3]), $vec[3]);
var_dump(isset($vec[4]));
*/
unset($vec[4]);