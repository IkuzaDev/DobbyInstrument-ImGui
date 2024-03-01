//
// Created by FangCybertron
//
#pragma once

#include "FangCyR/Engine/Tools.hpp"
#include "FangCyR/Engine/Utils.hpp"
#include "il2cpp-api-types.hpp"

#define DO_API(r, n, p) r (*n) p
#include "il2cpp-api-functions.hpp"
#undef DO_API

class FangEngine {
private:
    bool FieldStatic(FieldInfo *field) {
        return (il2cpp_field_get_flags(field) & 0x10) != 0;
    }
    Il2CppClass *Il2CppGetClass(const char *namespaze, const char *clazz) {
        size_t size = 0;
        const Il2CppAssembly **assemblies = il2cpp_domain_get_assemblies(il2cpp_domain_get(), &size);
        for (int i = 0; i < size; i++) {
            const Il2CppImage *img = il2cpp_assembly_get_image(assemblies[i]);
            if (!img) {
                continue;
            }
            Il2CppClass *klass = il2cpp_class_from_name(img, namespaze, clazz);
            if (klass) {
                return klass;
            }
        }
        return nullptr;
    }
public:
    Il2CppClass *getRealClass;
    const char *getCharClass;
    
    FangEngine(const char *namespaze, const char *clazz) {
        Il2CppClass *klass = nullptr;
        int count = 0;
        do {
            klass = Il2CppGetClass(namespaze, clazz);
            if (count == 2 && !klass) {
                return;
            } else if (!klass) {
                sleep(1);
                count ++;
            }
        } while (!klass);
        getRealClass = klass;
        getCharClass = clazz;
    }
    
    Il2CppObject *Il2CppCreateClassInstance() {
        return (Il2CppObject *)((uintptr_t)il2cpp_object_new(getRealClass));
    }

    void Il2CppSetStaticField(FieldInfo * field, void *value){
        if (FieldStatic(field)) {
            il2cpp_field_static_set_value(field, value);
        }
    }
    
    FieldInfo *Il2CppGetField(const char *name) {
        FieldInfo *field = il2cpp_class_get_field_from_name(getRealClass, name);
        if (!field) {
            return nullptr;
        }
        if (FieldStatic(field)) {
            return (FieldInfo *)((uintptr_t)field->parent->static_fields + field->offset);
        }
        return (FieldInfo *)((uintptr_t)field->offset);
    }
    
    MethodInfo *Il2CppGetMethod(const char *name, int argsCount) {
        const MethodInfo *method = il2cpp_class_get_method_from_name(getRealClass, name, argsCount);
        if (!method) {
            return nullptr;
        }
        return (MethodInfo *)((uintptr_t)method->methodPointer);
    }
    
    static void Il2CppFindSymbol() {
        void *handle = dlopen(LibIl2cpp, RTLD_LAZY);
        while (!handle) {
            handle = dlopen(LibIl2cpp, RTLD_LAZY);
            sleep(1);
        }
        #define DO_API(r, n, p) {            \
            n = (r (*) p) dlsym(handle, #n); \
        }
        #include "il2cpp-api-functions.hpp"
        #undef DO_API
        //dlclose(handle);
    }
    
    static Il2CppThread *Il2CppThreadAttach() {
        return il2cpp_thread_attach(il2cpp_domain_get());
    }
    
    static void Il2CppThreadDetach() {
        return il2cpp_thread_detach(il2cpp_thread_current());
    }
    
    static Il2CppString *Il2CppCreateString(const char *s) {
        return il2cpp_string_new(s);
    }
    
};

std::string Utf16ToUtf8(const Il2CppChar *utf16String, int maximumSize) {
    const Il2CppChar *ptr = utf16String;
    size_t length = 0;
    while (*ptr) {
        ptr ++;
        length ++;
        if (maximumSize != -1 && length == maximumSize)
            break;
    }
    std::string utf8String;
    utf8String.reserve(length);
    utf8::unchecked::utf16to8(utf16String, ptr, std::back_inserter(utf8String));
    return utf8String;
}
 
std::string Utf16ToUtf8(const Il2CppChar *utf16String) {
    return Utf16ToUtf8(utf16String, -1);
}

template<typename T>
struct IL2CppArray : Il2CppObject  {
    Il2CppArrayBounds *bounds;
    il2cpp_array_size_t capacity;
    T m_Items[0];
    
    il2cpp_array_size_t getCapacity() {
        if (!this)
            return 0;
        return capacity;
    }
    
    T *getPointer() {
        if (!this)
            return nullptr;
        return m_Items;
    }
    
    std::vector<T> toCPPlist() {
        if (!this)
            return {};
            
    std::vector<T> ret;
        
    for (int i = 0; i < capacity; i++)
        ret.push_back(m_Items[i]);
        return std::move(ret);
    }
        
    bool copyFrom(const std::vector<T> &vec) {
        if (!this)
            return false;
        return copyFrom((T *)vec.data(), (int)vec.size());
    }
        
    bool copyFrom(T *arr, int size) {
            
        if (!this)
            return false;
        if (size < capacity)
            return false;
        memcpy(m_Items, arr, size  *sizeof(T));
        return true;
    }
        
    void copyTo(T *arr) {
        if (!this || !CheckObj(m_Items))
            return;
            memcpy(arr, m_Items, sizeof(T) *capacity);
    }
        
    T operator[] (int index) {
        if (getCapacity() < index)
        return {};
        return m_Items[index];
    }
        
    T at(int index) {
        if (!this || getCapacity() <= index || empty())
            return {};
        return m_Items[index];
    }
        
    bool empty() {
        if (!this)
            return false;
        return getCapacity() <= 0;
    }
        
    static IL2CppArray<T> *Create(int capacity) {
        auto monoArr = (IL2CppArray<T> *)malloc(sizeof(IL2CppArray) + sizeof(T)  *capacity);
        monoArr->capacity = capacity;
        return monoArr;
    }
        
    static IL2CppArray<T> *Create(const std::vector<T> &vec) {
        return Create(vec.data(), vec.size());
    }
        
    static IL2CppArray<T> *Create(T *arr, int size) {
        IL2CppArray<T> *monoArr = Create(size);
        monoArr->copyFrom(arr, size);
        return monoArr;
    }
};

template<typename T>
struct IL2CppList : Il2CppObject {
    IL2CppArray<T> *items;
    int size;
    int version;
    
    T *getItems() {
        return items->getPointer();
    }
    
    int getSize() {
        return size;
    }
    
    int getVersion() {
        return version;
    }
    
    std::vector<T> toCPPlist() {
        std::vector<T> ret;
        
    for (int i = 0; i < size; i++)
        ret.push_back(getItems()[i]);
        return std::move(ret);
    }
    
    void Add(T val) {
        GrowIfNeeded(1);
        items->m_Items[size] = val;
        size++;
        version++;
    }
    
    int IndexOf(T val) {
        for (int i = 0; i < size; i++)
        if (items->m_Items[i] == val)
            return i;
            return -1;
    }
    
    void RemoveAt(int index) {
        if (index != -1) {
            Shift(index, -1);
            version++;
        }
    }
    
    void Remove(T val) {
        RemoveAt(IndexOf(val));
    }
    
    bool Resize(int newCapacity) {
        if (!this)
            return false;
            
        if (newCapacity <= items->capacity)
            return false;
            
        auto nItems = IL2CppArray<T>::Create(newCapacity);
        nItems->klass = items->klass;
        nItems->monitor = items->monitor;
        nItems->bounds = items->bounds;
        nItems->capacity = newCapacity;
        if (items->capacity > 0)
            memcpy(nItems->m_Items, items->m_Items, items->capacity *sizeof(T));
            items = nItems;
            return true;
        }
        
        T operator[] (int index) {
            return items->m_Items[index];
        }
        
    private:
    void GrowIfNeeded(int n) {
        if (size + n > items->capacity)
            Resize(size + n);
    }
        
    void Shift(int start, int delta) {
        if (delta < 0)
            start -= delta;
        if (start < size)
            memcpy(items + start + delta, items + start, size - start);
            size += delta;
        if (delta < 0)
            memset(items + size + delta, 0, -delta  *sizeof(T));
    }
};

template<typename TKey, typename TValue>
struct IL2CppDictionary {
    
    struct Entry {
        int hashCode, next;
        TKey key;
        TValue value;
    };
    
    Il2CppClass *klass;
    MonitorData *monitor;
    IL2CppArray<int> *buckets;
    IL2CppArray<Entry> *entries;
    int count;
    int version;
    int freeList;
    int freeCount;
    void *comparer;
    IL2CppArray<TKey> *keys;
    IL2CppArray<TValue> *values;
    void *syncRoot;
    
    std::map<TKey, TValue> toMap() {
        std::map<TKey, TValue> ret;
        for (auto it = (Entry *)&entries->m_Items; it != ((Entry *)&entries->m_Items + count); ++it) ret.emplace(std::make_pair(it->key, it->value));
        return std::move(ret);
    }
    
    std::vector<TKey> getKeys() {
        std::vector<TKey> ret;
        for (int i = 0; i < count; ++i) ret.emplace_back(entries->at(i).key);
        return std::move(ret);
    }
    
    std::vector<TValue> getValues() {
        std::vector<TValue> ret;
        for (int i = 0; i < count; ++i) ret.emplace_back(entries->at(i).value);
        return std::move(ret);
    }
    
    int getSize() {
        return count;
    }
    
    int getVersion() {
        return version;
    }
    
    TValue Get(TKey key) {
        TValue ret;
        if (TryGet(key, &ret)) return ret;
        return {};
    }
    
    TValue operator[](TKey key) {
        return Get(key);
    }
};
