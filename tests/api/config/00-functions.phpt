--TEST--
Config API functions

--FILE--
<?php

var_dump(
    function_exists('wasm_config_new'),
);

--EXPECTF--
bool(true)
