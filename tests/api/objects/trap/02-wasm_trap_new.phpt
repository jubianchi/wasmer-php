--TEST--
ExportType API: wasm_trap_new

--FILE--
<?php

$message = "trap message";
$engine = wasm_engine_new();
$store = wasm_store_new($engine);
$trap = wasm_trap_new($store, $message);
var_dump($trap);

?>
--EXPECTF--
resource(%d) of type (wasm_trap_t)
