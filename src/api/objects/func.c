#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasmer_wasm.h"

#include "../macros.h"

WASMER_IMPORT_RESOURCE(func)
WASMER_IMPORT_RESOURCE(functype)
WASMER_IMPORT_RESOURCE(store)
WASMER_IMPORT_RESOURCE(extern)

WASMER_DECLARE_OWN(func)

typedef struct {
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
} func_env;

wasm_trap_t *func_trampoline(void *env, const wasm_val_vec_t *args, wasm_val_vec_t *results) {
    func_env *fenv = (func_env *) env;
    zval retval;
    zval inval;

    ZVAL_UNDEF(&retval);

    zend_fcall_info fci = fenv->fci;
    fci.retval = &retval;

    // TODO(jubianchi): Fix tests
    zend_result res = zend_call_function(&fci, &fenv->fcc);

    return NULL;
}

PHP_FUNCTION (wasm_func_new) {
    zval *store_val;
    zval *functype_val;
    func_env *env = malloc(sizeof(func_env));

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
            Z_PARAM_RESOURCE(store_val)
            Z_PARAM_RESOURCE(functype_val)
            Z_PARAM_FUNC(env->fci, env->fcc)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(store)
    WASMER_FETCH_RESOURCE(functype)

    wasm_func_t *func = wasm_func_new_with_env(
            Z_RES_P(store_val)->ptr,
            Z_RES_P(functype_val)->ptr,
            &func_trampoline,
            env,
            // TODO(jubianchi): Implement env finalizer
            NULL
    );

    if (!func) {
        zend_throw_exception_ex(zend_ce_exception, 0, "%s", "Failed to create function");\
    }

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
    zval *func_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(func_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(func)

    wasm_func_t *func = Z_RES_P(func_val)->ptr;
    size_t arity = wasm_func_param_arity(func);

    RETURN_LONG(arity);
}

PHP_FUNCTION (wasm_func_result_arity) {
    zval *func_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(func_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(func)

    wasm_func_t *func = Z_RES_P(func_val)->ptr;
    size_t arity = wasm_func_result_arity(func);

    RETURN_LONG(arity);
}

PHP_FUNCTION (wasm_func_call) {
    ZEND_PARSE_PARAMETERS_NONE();

    // TODO(jubianchi): Implement
    zend_throw_error(NULL, "Not yet implemented");
}

PHP_FUNCTION (wasm_func_as_extern) {
    zval *func_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(func_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(func)

    const wasm_extern_t *wasm_extern = wasm_func_as_extern(Z_RES_P(func_val)->ptr);

    zend_resource *extern_res;
    extern_res = zend_register_resource((void *) wasm_extern, le_wasm_extern);

    RETURN_RES(extern_res);
}