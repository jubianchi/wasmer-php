#include "php.h"

#include "wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(func)
WASMER_IMPORT_RESOURCE(functype)
WASMER_IMPORT_RESOURCE(store)

WASMER_DECLARE_OWN(func)

PHP_FUNCTION (wasm_func_new) {
    zval *store_val;
    zval *functype_val;
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
            Z_PARAM_RESOURCE(store_val)
            Z_PARAM_RESOURCE(functype_val)
            Z_PARAM_FUNC(fci, fcc)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(store)
    WASMER_FETCH_RESOURCE(functype)

    wasm_store_t *store = Z_RES_P(store_val)->ptr;
    wasm_functype_t *functype = Z_RES_P(functype_val)->ptr;

    // TODO(jubianchi): Implement callback
    wasm_func_t *func = wasm_func_new(store, functype, NULL);

    zend_resource *func_res;
    func_res = zend_register_resource(func, le_wasm_func);

    RETURN_RES(func_res);
}

PHP_FUNCTION (wasm_func_new_with_env) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_func_type) {
    zval *func_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(func_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(func)

    wasm_func_t *func = Z_RES_P(func_val)->ptr;
    wasm_functype_t *functype = wasm_func_type(func);

    zend_resource *functype_res;
    functype_res = zend_register_resource(functype, le_wasm_functype);

    RETURN_RES(functype_res);
}

PHP_FUNCTION (wasm_func_param_arity) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_func_result_arity) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_func_call) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_func_as_extern) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}