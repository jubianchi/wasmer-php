#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasmer_wasm.h"

#include "../macros.h"
#include "../../wasmer.h"

WASMER_DECLARE_OWN(func)

WASMER_IMPORT_RESOURCE(functype)
WASMER_IMPORT_RESOURCE(store)
WASMER_IMPORT_RESOURCE(extern)

typedef struct {
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
} func_env;

wasm_trap_t *func_trampoline(void *env, const wasm_val_vec_t *args, wasm_val_vec_t *results) {
    func_env *fenv = (func_env *) env;
    zval retval;

    ZVAL_UNDEF(&retval);

    zend_fcall_info fci = fenv->fci;
    fci.retval = &retval;
    fci.object = NULL;

    // TODO(jubianchi): Fix tests
    //zend_result res = zend_call_function(&fci, &fenv->fcc);
    zend_call_function(&fci, &fenv->fcc);

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

    wasmer_res *func = emalloc(sizeof(wasmer_res));
    func->inner.func = wasm_func_new_with_env(
            WASMER_RES_P_INNER(store_val, store),
            WASMER_RES_P_INNER(functype_val, functype),
            &func_trampoline,
            env,
            // TODO(jubianchi): Implement env finalizer
            NULL
    );
    func->owned = true;

    if (!func->inner.func) {
        zend_throw_exception_ex(zend_ce_exception, 0, "%s", "Failed to create function");\
    }

    zend_resource *func_res = zend_register_resource(func, le_wasm_func);

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

    wasmer_res *functype = emalloc(sizeof(wasmer_res));
    functype->inner.functype = wasm_func_type(WASMER_RES_P_INNER(func_val, func));
    functype->owned = false;

    RETURN_RES(zend_register_resource(functype, le_wasm_functype));
}

PHP_FUNCTION (wasm_func_param_arity) {
    zval *func_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(func_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(func)

    size_t arity = wasm_func_param_arity(WASMER_RES_P_INNER(func_val, func));

    RETURN_LONG(arity);
}

PHP_FUNCTION (wasm_func_result_arity) {
    zval *func_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(func_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(func)

    size_t arity = wasm_func_result_arity(WASMER_RES_P_INNER(func_val, func));

    RETURN_LONG(arity);
}

PHP_FUNCTION (wasm_func_call) {
    zval *func_val;
    zval *args_val;
    zval *results_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
            Z_PARAM_RESOURCE(func_val)
            Z_PARAM_OBJECT(args_val)
            Z_PARAM_OBJECT(results_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(func)

    wasm_func_t *func = WASMER_RES_P_INNER(func_val, func);
    wasm_val_vec_c *args = Z_WASM_VAL_VEC_P(args_val);
    wasm_val_vec_c *results = Z_WASM_VAL_VEC_P(results_val);

    // TODO(jubianchi): Implements traps
    // TODO(jubianchi): Implements results
    wasm_func_call(func, &args->vec, &results->vec);

    RETURN_TRUE;
}

PHP_FUNCTION (wasm_func_as_extern) {
    zval *func_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(func_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(func)

    wasmer_res *wasm_extern = emalloc(sizeof(wasmer_res));
    wasm_extern->inner.xtern = wasm_func_as_extern(WASMER_RES_P_INNER(func_val, func));
    wasm_extern->owned = false;

    RETURN_RES(zend_register_resource(wasm_extern, le_wasm_extern));
}