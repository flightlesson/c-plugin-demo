#ifndef plugin_h
#define plugin_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Optional, but if provided gets called before pluginDoSomething() or pluginDestroy() get called.
 * With C plugins can return anything;
 * With C++ plugins should 'return new SomeClass' w
 *
 * @return can be anything
 */
void *pluginCreate();

/**
 * Does something.
 * @param thisObject what pluginCreate() returned.
 * @return 0 indicates success; anything else indicates failure
 */
int pluginDoSomething(void *thisObject);

/**
 * @param thisObject what pluginCreate() returned.
 */
void pluginDestroy(void *thisObject);
  
#ifdef __cplusplus
}
#endif


#endif

