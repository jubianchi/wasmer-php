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

#define Z_WASMER_DECLARE_VEC_CLASS(class_name, name)\
INIT_NS_CLASS_ENTRY(ce, "Wasm\\Vec", #class_name, class_Wasm_Vec_##class_name##_methods)\
wasm_vec_##name##_ce = zend_register_internal_class(&ce);\
wasm_vec_##name##_ce->ce_flags |= ZEND_ACC_FINAL;\
wasm_vec_##name##_ce->create_object = wasm_##name##_vec_create;\
\
memcpy(&wasm_##name##_vec_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));\
wasm_##name##_vec_object_handlers.offset = XtOffsetOf(struct wasm_##name##_vec_c, std);\
\
zend_class_implements(wasm_vec_##name##_ce, 1, zend_ce_countable);\
zend_class_implements(wasm_vec_##name##_ce, 1, zend_ce_arrayaccess);
