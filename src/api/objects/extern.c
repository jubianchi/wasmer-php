#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(extern)

WASMER_DELETE_WITHOUT_DTOR(extern)

PHP_FUNCTION (wasm_extern_kind) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_type) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_as_func) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_as_global) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_as_table) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_as_memory) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_extern_copy) {
    zval *extern_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(extern_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(extern)

    wasm_extern_t *extern_ = wasm_extern_copy(Z_RES_P(extern_val)->ptr);

    zend_resource *extern_res;
    extern_res = zend_register_resource((void *) extern_, le_wasm_extern);

    RETURN_RES(extern_res);
}

// TODO(jubianchi): Implement wasm_extern_vec_t