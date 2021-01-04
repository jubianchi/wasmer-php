#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "Zend/zend_interfaces.h"
#include "ext/standard/info.h"

#include "wasm.h"

#include "php_wasmer.h"
#include "wasmer_arginfo.h"
#include "macros.h"
#include "wasmer.h"

WASMER_RESOURCE_LE(config)
WASMER_RESOURCE(engine)
WASMER_RESOURCE_LE(exporttype)
WASMER_RESOURCE_LE(extern)
WASMER_RESOURCE_LE(externtype)
WASMER_RESOURCE_LE(foreign)
WASMER_RESOURCE_LE(frame)
WASMER_RESOURCE_LE(func)
WASMER_RESOURCE_LE(functype)
WASMER_RESOURCE_LE(global)
WASMER_RESOURCE_LE(globaltype)
WASMER_RESOURCE_LE(importtype)
WASMER_RESOURCE_LE(instance)
WASMER_RESOURCE_LE(limits)
WASMER_RESOURCE_LE(memory)
WASMER_RESOURCE_LE(memorytype)
WASMER_RESOURCE_LE(module)
WASMER_RESOURCE(store)
WASMER_RESOURCE_LE(table)
WASMER_RESOURCE_LE(tabletype)
WASMER_RESOURCE_LE(trap)
WASMER_RESOURCE_LE(val)
WASMER_RESOURCE_LE(valtype)

zend_class_entry *wasm_vec_valtype_ce;
static zend_object_handlers wasm_valtype_vec_object_handlers;
zend_object *wasm_valtype_vec_create(zend_class_entry *ce)
{
    wasm_valtype_vec_c *wasm_valtype_vec = zend_object_alloc(sizeof(wasm_valtype_vec_c), ce);

    zend_object_std_init(&wasm_valtype_vec->std, ce);
    wasm_valtype_vec->std.handlers = &wasm_valtype_vec_object_handlers;

    return &wasm_valtype_vec->std;
}

zend_class_entry *wasm_vec_globaltype_ce;
static zend_object_handlers wasm_globaltype_vec_object_handlers;
zend_object *wasm_globaltype_vec_create(zend_class_entry *ce)
{
    wasm_globaltype_vec_c *wasm_globaltype_vec = zend_object_alloc(sizeof(wasm_globaltype_vec_c), ce);

    zend_object_std_init(&wasm_globaltype_vec->std, ce);
    wasm_globaltype_vec->std.handlers = &wasm_valtype_vec_object_handlers;

    return &wasm_globaltype_vec->std;
}

zend_class_entry *wasm_vec_tabletype_ce;
static zend_object_handlers wasm_tabletype_vec_object_handlers;
zend_object *wasm_tabletype_vec_create(zend_class_entry *ce)
{
    wasm_tabletype_vec_c *wasm_tabletype_vec = zend_object_alloc(sizeof(wasm_tabletype_vec_c), ce);

    zend_object_std_init(&wasm_tabletype_vec->std, ce);
    wasm_tabletype_vec->std.handlers = &wasm_valtype_vec_object_handlers;

    return &wasm_tabletype_vec->std;
}

zend_class_entry *wasm_vec_memorytype_ce;
static zend_object_handlers wasm_memorytype_vec_object_handlers;
zend_object *wasm_memorytype_vec_create(zend_class_entry *ce)
{
    wasm_memorytype_vec_c *wasm_memorytype_vec = zend_object_alloc(sizeof(wasm_memorytype_vec_c), ce);

    zend_object_std_init(&wasm_memorytype_vec->std, ce);
    wasm_memorytype_vec->std.handlers = &wasm_valtype_vec_object_handlers;

    return &wasm_memorytype_vec->std;
}

/*
static zend_class_entry* fetch_internal_class(const char* class_name)
{
    zend_class_entry* ce;

    if ((ce = zend_hash_str_find_ptr(CG(class_table), class_name, strlen(class_name)))) {
        return ce;
    }

    return NULL;
}
*/

PHP_MINIT_FUNCTION (wasmer) {
    WASMER_RESOURCE_REGISTER(config)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(engine)
    WASMER_RESOURCE_REGISTER(exporttype)
    WASMER_RESOURCE_REGISTER(extern)
    WASMER_RESOURCE_REGISTER(externtype)
    WASMER_RESOURCE_REGISTER(foreign)
    WASMER_RESOURCE_REGISTER(frame)
    WASMER_RESOURCE_REGISTER(func)
    WASMER_RESOURCE_REGISTER(functype)
    WASMER_RESOURCE_REGISTER(global)
    WASMER_RESOURCE_REGISTER(globaltype)
    WASMER_RESOURCE_REGISTER(importtype)
    WASMER_RESOURCE_REGISTER(instance)
    WASMER_RESOURCE_REGISTER(limits)
    WASMER_RESOURCE_REGISTER(memorytype)
    WASMER_RESOURCE_REGISTER(memory)
    WASMER_RESOURCE_REGISTER(module)
    WASMER_RESOURCE_REGISTER_WITH_DTOR(store)
    WASMER_RESOURCE_REGISTER(table)
    WASMER_RESOURCE_REGISTER(tabletype)
    WASMER_RESOURCE_REGISTER(trap)
    WASMER_RESOURCE_REGISTER(val)
    WASMER_RESOURCE_REGISTER(valtype)

    REGISTER_LONG_CONSTANT("WASM_I32", WASM_I32, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_I64", WASM_I64, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_F32", WASM_F32, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_F64", WASM_F64, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_ANYREF", WASM_ANYREF, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_FUNCREF", WASM_FUNCREF, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_CONST", WASM_CONST, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_VAR", WASM_VAR, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_EXTERN_FUNC", WASM_EXTERN_FUNC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_GLOBAL", WASM_EXTERN_GLOBAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_TABLE", WASM_EXTERN_TABLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WASM_EXTERN_MEMORY", WASM_EXTERN_MEMORY, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_LIMITS_MAX_DEFAULT", wasm_limits_max_default, CONST_CS | CONST_PERSISTENT);

    REGISTER_LONG_CONSTANT("WASM_MEMORY_PAGE_SIZE", MEMORY_PAGE_SIZE, CONST_CS | CONST_PERSISTENT);

    zend_class_entry ce;

    Z_WASMER_DECLARE_VEC_CLASS(ValType, valtype)
    Z_WASMER_DECLARE_VEC_CLASS(GlobalType, globaltype)
    Z_WASMER_DECLARE_VEC_CLASS(TableType, tabletype)
    Z_WASMER_DECLARE_VEC_CLASS(MemoryType, memorytype)

    return SUCCESS;
}

PHP_RINIT_FUNCTION(wasmer) {
#if defined(ZTS) && defined(COMPILE_DL_WASMER)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(wasmer) {
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(wasmer) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION (wasmer) {
    php_info_print_table_start();
    php_info_print_table_header(2, "Wasmer support", "enabled");
    php_info_print_table_end();
}

zend_module_entry wasmer_module_entry = {
        STANDARD_MODULE_HEADER,
        "wasmer",
        ext_functions,
        PHP_MINIT(wasmer),
        PHP_MSHUTDOWN(wasmer),
        PHP_RINIT(wasmer),
        PHP_RSHUTDOWN(wasmer),
        PHP_MINFO(wasmer),
        PHP_WASMER_VERSION,
        STANDARD_MODULE_PROPERTIES};

#ifdef COMPILE_DL_WASMER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(wasmer)
#endif