--TEST--
Engine API: wasm_engine_new

--FILE--
<?php

$config = wasm_config_new();
var_dump($config);

?>
--EXPECTF--
resource(%d) of type (wasm_config_t)
