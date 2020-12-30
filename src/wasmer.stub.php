<?php

/** @generate-function-entries */

// TODO(jubianchi): Add valtype_vec
namespace Wasm\Vec {
    final class ValType implements \Countable, \ArrayAccess {
        public function __construct(?int $size = null, ?array $valtypes = null) {}
        public function count(): int {}
        public function offsetExists(mixed $offset): bool {}
        /** @return resource */
        public function offsetGet(mixed $offset): mixed {}
        /** @param resource $value */
        public function offsetSet(mixed $offset, mixed $value): void {}
        public function offsetUnset(mixed $offset): void {}
    }
}

namespace {

    ///////////////////////////////////////////////////////////////////////////////
    // Runtime Environment

    // Configuration

    /** @return resource */
    function wasm_config_new() {}


    // Engine

    /** @return resource */
    function wasm_engine_new() {}
    /**
     * @param resource $config
     *
     * @return resource
     */
    function wasm_engine_new_with_config($config) {}
    /** @param resource $engine */
    function wasm_engine_delete($engine): bool {}


    // Store

    /**
     * @param resource $engine
     *
     * @return resource
     */
    function wasm_store_new($engine) {}
    /** @param resource $store */
    function wasm_store_delete($store): bool {}


    ///////////////////////////////////////////////////////////////////////////////
    // Type Representations

    // Value Types

    /** @return resource */
    function wasm_valtype_new(int $kind) {}
    /** @param resource $valtype */
    function wasm_valtype_delete($valtype): bool {}
    /** @param resource $valtype */
    function wasm_valtype_kind($valtype): int {}
    /** @param resource $valtype */
    function wasm_valtype_is_num($valtype): bool {}
    /** @param resource $valtype */
    function wasm_valtype_is_ref($valtype): bool {}
    /**
     * @param resource $valtype
     *
     * @return resource
     */
    function wasm_valtype_copy($valtype) {}

    function wasm_valkind_is_num(int $kind): bool {}
    function wasm_valkind_is_ref(int $kind): bool {}


    // Function Types

    // TODO(jubianchi): Add functype
    // TODO(jubianchi): Add functype_vec
    // TODO(jubianchi): Add functype_as_externtype


    // Global Types

    /**
     * @param resource $valtype
     *
     * @return resource
     */
    function wasm_globaltype_new($valtype, int $mutability) {}
    /** @param resource $globaltype */
    function wasm_globaltype_delete($globaltype): bool {}
    /**
     * @param resource $globaltype
     *
     * @return resource
     */
    function wasm_globaltype_content($globaltype) {}
    /** @param resource $globaltype */
    function wasm_globaltype_mutability($globaltype): int {}
    /**
     * @param resource $globaltype
     *
     * @return resource
     */
    function wasm_globaltype_copy($globaltype) {}
    /**
     * @param resource $globaltype
     *
     * @return resource
     */
    function wasm_globaltype_as_externtype($globaltype) {}

    // TODO(jubianchi): Add globaltype_vec

    /** @return resource */
    function wasm_limits_new(int $min, int $max) {}
    /** @param resource $limits */
    function wasm_limits_min($limits): int {}
    /** @param resource $limits */
    function wasm_limits_max($limits): int {}


    // Table Types

    /**
     * @param resource $valtype
     * @param resource $limits
     *
     * @return resource
     */
    function wasm_tabletype_new($valtype, $limits) {}
    /** @param resource $tabletype */
    function wasm_tabletype_delete($tabletype): bool {}
    /**
     * @param resource $tabletype
     *
     * @return resource
     */
    function wasm_tabletype_element($tabletype) {}
    /**
     * @param resource $tabletype
     *
     * @return resource
     */
    function wasm_tabletype_limits($tabletype) {}
    /**
     * @param resource $tabletype
     *
     * @return resource
     */
    function wasm_tabletype_copy($tabletype) {}
    /**
     * @param resource $tabletype
     *
     * @return resource
     */
    function wasm_tabletype_as_externtype($tabletype) {}

    // TODO(jubianchi): Add tabletype_vec


    // Memory Types

    /**
     * @param resource $limits
     *
     * @return resource
     */
    function wasm_memorytype_new($limits) {}
    /** @param resource $memorytype */
    function wasm_memorytype_delete($memorytype): bool {}
    /**
     * @param resource $memorytype
     *
     * @return resource
     */
    function wasm_memorytype_limits($memorytype) {}
    /**
     * @param resource $memorytype
     *
     * @return resource
     */
    function wasm_memorytype_copy($memorytype) {}
    /**
     * @param resource $memorytype
     *
     * @return resource
     */
    function wasm_memorytype_as_externtype($memorytype) {}

    // TODO(jubianchi): Add memorytype_vec


    // Extern Types

    /**
     * @param resource $externtype
     *
     * @return resource
     */
    function wasm_externtype_kind($externtype) {}
    /**
     * @param resource $externtype
     *
     * @return resource
     */
    function wasm_externtype_as_functype($externtype) {}
    /**
     * @param resource $externtype
     *
     * @return resource
     */
    function wasm_externtype_as_globaltype($externtype) {}
    /**
     * @param resource $externtype
     *
     * @return resource
     */
    function wasm_externtype_as_tabletype($externtype) {}
    /**
     * @param resource $externtype
     *
     * @return resource
     */
    function wasm_externtype_as_memorytype($externtype) {}

    // TODO(jubianchi): Add externtype_vec


    // Import Types

    /**
     * @param resource $externtype
     *
     * @return resource
     */
    function wasm_importtype_new(string $module, string $name, $externtype) {}
    /** @param resource $importype */
    function wasm_importtype_delete($importype): bool {}
    /** @param resource $importype */
    function wasm_importtype_module($importype): string {}
    /** @param resource $importype */
    function wasm_importtype_name($importype): string {}
    /**
     * @param resource $importype
     *
     * @return resource
     */
    function wasm_importtype_type($importype) {}
    /**
     * @param resource $importype
     *
     * @return resource
     */
    function wasm_importtype_copy($importype) {}

    // TODO(jubianchi): Add importtype_vec


    // Export Types

    /**
     * @param resource $externtype
     *
     * @return resource
     */
    function wasm_exporttype_new(string $name, $externtype) {}
    /** @param resource $exportype */
    function wasm_exporttype_delete($exportype): bool {}
    /** @param resource $exportype */
    function wasm_exporttype_name($exportype): string {}
    /**
     * @param resource $exportype
     *
     * @return resource
     */
    function wasm_exporttype_type($exportype) {}
    /**
     * @param resource $exportype
     *
     * @return resource
     */
    function wasm_exporttype_copy($exportype) {}

    // TODO(jubianchi): Add exporttype_vec


    ///////////////////////////////////////////////////////////////////////////////
    // Runtime Objects

    //Values

    /** @param resource $val */
    function wasm_val_delete($val): bool {}
    /**
     * @param resource $val
     *
     * @return resource
     */
    function wasm_val_copy($val) {}

    // TODO(jubianchi): Add val_vec


    // References

    // TODO(jubianchi): Add ref


    // Frames

    // TODO(jubianchi): Add frame


    // Traps

    // TODO(jubianchi): Add trap


    // Foreign Objects

    // TODO(jubianchi): Add foreign


    // Modules

    function wasm_module_new(): void {}
    function wasm_module_delete(): void {}
    function wasm_module_validate(): void {}
    function wasm_module_imports(): void {}
    function wasm_module_exports(): void {}
    function wasm_module_serialize(): void {}


    // Function Instances

    // TODO(jubianchi): Add func


    // Global Instances

    // TODO(jubianchi): Add global


    // Table Instances

    // TODO(jubianchi): Add table


    // Memory Instances

    // TODO(jubianchi): Add memory


    // Externals

    // TODO(jubianchi): Add extern


    // Module Instances

    // TODO(jubianchi): Add instance
}
