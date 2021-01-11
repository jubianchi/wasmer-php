#include "php.h"
#include "Zend/zend_exceptions.h"

#include "wasmer_wasm.h"

#include "../macros.h"
#include "../../wasmer.h"

WASMER_IMPORT_RESOURCE(instance)
WASMER_IMPORT_RESOURCE(store)
WASMER_IMPORT_RESOURCE(module)

extern zend_class_entry *wasm_vec_extern_ce;

WASMER_DECLARE_OWN(instance)

// TODO(jubianchi): Implements imports
// TODO(jubianchi): Implements traps
PHP_FUNCTION (wasm_instance_new) {
    zval *store_val;
    zval *module_val;
    zval *externs_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
            Z_PARAM_RESOURCE(store_val)
            Z_PARAM_RESOURCE(module_val)
            Z_PARAM_OBJECT(externs_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(store)
    WASMER_FETCH_RESOURCE(module)

    wasm_store_t *store = Z_RES_P(store_val)->ptr;
    wasm_module_t *module = Z_RES_P(module_val)->ptr;

    wasm_extern_vec_c *externs = Z_WASM_EXTERN_VEC_P(externs_val);

    wasm_instance_t *instance = wasm_instance_new(store, module, &externs->vec, NULL);

    WASMER_HANDLE_ERROR

    zend_resource *instance_res = zend_register_resource(instance, le_wasm_instance);

    RETURN_RES(instance_res);
}

PHP_FUNCTION (wasm_instance_exports) {
    zval *instance_val;

    ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 1)
            Z_PARAM_RESOURCE(instance_val)
    ZEND_PARSE_PARAMETERS_END();

    WASMER_FETCH_RESOURCE(instance)

    wasm_instance_t *instance = Z_RES_P(instance_val)->ptr;

    wasm_extern_vec_t *externs = emalloc(sizeof(wasm_extern_vec_t));
    wasm_instance_exports(instance, externs);

    zval obj;
    object_init_ex(&obj, wasm_vec_extern_ce);
    wasm_extern_vec_c *ce = Z_WASM_EXTERN_VEC_P(&obj);
    ce->vec = *externs;

    efree(externs);

    RETURN_OBJ(Z_OBJ(obj));
}

WASMER_COPY(instance)
