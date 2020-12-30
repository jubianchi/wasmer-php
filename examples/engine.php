<?php

$engine = wasm_engine_new();

var_dump($engine);
wasm_engine_delete($engine);

var_dump($engine);
wasm_engine_delete($engine);

