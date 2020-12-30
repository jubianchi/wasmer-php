--TEST--
Module API functions arguments information

--FILE--
<?php

$reflection = new ReflectionFunction('wasm_module_new');
var_dump($reflection->getNumberOfParameters());
var_dump($reflection->getReturnType()->getName());

echo PHP_EOL;

$reflection = new ReflectionFunction('wasm_module_delete');
var_dump($reflection->getNumberOfParameters());
var_dump($reflection->getReturnType()->getName());

echo PHP_EOL;

$reflection = new ReflectionFunction('wasm_module_validate');
var_dump($reflection->getNumberOfParameters());
var_dump($reflection->getReturnType()->getName());

echo PHP_EOL;

$reflection = new ReflectionFunction('wasm_module_imports');
var_dump($reflection->getNumberOfParameters());
var_dump($reflection->getReturnType()->getName());

echo PHP_EOL;

$reflection = new ReflectionFunction('wasm_module_exports');
var_dump($reflection->getNumberOfParameters());
var_dump($reflection->getReturnType()->getName());

echo PHP_EOL;

$reflection = new ReflectionFunction('wasm_module_serialize');
var_dump($reflection->getNumberOfParameters());
var_dump($reflection->getReturnType()->getName());

--EXPECTF--
int(0)
string(4) "void"

int(0)
string(4) "void"

int(0)
string(4) "void"

int(0)
string(4) "void"

int(0)
string(4) "void"

int(0)
string(4) "void"
