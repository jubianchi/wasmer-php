--TEST--
ExportType API: wasm_exporttype_new

--FILE--
<?php

$wat = 'foo';

try {
    $wasm = wat2wasm($wat);
} catch (\Exception $e) {
    var_dump($e->getMessage());
}

--EXPECTF--
string(62) "expected `(`
     --> <anon>:1:1
      |
    1 | foo
      | ^"