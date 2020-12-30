#define WASMER_RESOURCE_LE(name)\
int le_wasm_##name;\
const char *le_wasm_##name##_name = "wasm_"#name"_t";

#define WASMER_RESOURCE_DTOR(name)\
static ZEND_RSRC_DTOR_FUNC(wasm_##name##_dtor) {\
    wasm_##name##_t *name = (wasm_##name##_t *)res->ptr;\
    wasm_##name##_delete(name);\
}

#define WASMER_RESOURCE(name)\
WASMER_RESOURCE_LE(name)\
WASMER_RESOURCE_DTOR(name)

#define WASMER_RESOURCE_REGISTER(name)\
le_wasm_##name = zend_register_list_destructors_ex(\
    NULL,\
    NULL,\
    le_wasm_##name##_name,\
    module_number\
);\
\
if (le_wasm_engine == FAILURE) {\
    return FAILURE;\
}

#define WASMER_RESOURCE_REGISTER_WITH_DTOR(name)\
le_wasm_##name = zend_register_list_destructors_ex(\
    wasm_##name##_dtor,\
    NULL,\
    le_wasm_##name##_name,\
    module_number\
);\
\
if (le_wasm_engine == FAILURE) {\
    return FAILURE;\
}
