#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasm.h"

#include "../macros.h"
#include "../../wasmer.h"

WASMER_IMPORT_RESOURCE(externtype)

WASMER_DECLARE_TYPE(FuncType, FUNCTYPE, functype)

extern zend_class_entry *wasm_vec_valtype_ce;

PHP_FUNCTION (wasm_functype_new) {
    zval *params_val;
    zval *results_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 2)
            Z_PARAM_OBJECT(params_val)
            Z_PARAM_OBJECT(results_val)
    ZEND_PARSE_PARAMETERS_END();

    wasm_valtype_vec_c *params = Z_WASM_VALTYPE_VEC_P(params_val);
    wasm_valtype_vec_c *results = Z_WASM_VALTYPE_VEC_P(results_val);

    wasm_functype_t *functype = wasm_functype_new(&params->vec, &results->vec);

    zend_resource *functype_res;
    functype_res = zend_register_resource(functype, le_wasm_functype);

    RETURN_RES(functype_res);
}

PHP_FUNCTION (wasm_functype_params) {
    zval *functype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(functype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(functype)

    wasm_functype_t *functype = Z_RES_P(functype_val)->ptr;

    const wasm_valtype_vec_t *valtypes = wasm_functype_params(functype);

    zval obj;
    object_init_ex(&obj, wasm_vec_valtype_ce);
    wasm_valtype_vec_c *ce = Z_WASM_VALTYPE_VEC_P(&obj);
    ce->vec = *valtypes;

    RETURN_OBJ(Z_OBJ(obj));
}

PHP_FUNCTION (wasm_functype_results) {
    zval *functype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(functype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(functype)

    wasm_functype_t *functype = Z_RES_P(functype_val)->ptr;

    const wasm_valtype_vec_t *valtypes = wasm_functype_results(functype);

    zval obj;
    object_init_ex(&obj, wasm_vec_valtype_ce);
    wasm_valtype_vec_c *ce = Z_WASM_VALTYPE_VEC_P(&obj);
    ce->vec = *valtypes;

    RETURN_OBJ(Z_OBJ(obj));
}

PHP_FUNCTION (wasm_functype_as_externtype) {
    zval *functype_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(functype_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(functype)

    const wasm_externtype_t *externtype = wasm_globaltype_as_externtype(Z_RES_P(functype_val)->ptr);

    zend_resource *externtype_res;
    externtype_res = zend_register_resource((void *) externtype, le_wasm_externtype);

    RETURN_RES(externtype_res);
}
