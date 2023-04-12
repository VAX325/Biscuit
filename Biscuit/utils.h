#ifndef UTILS_H
#define UTILS_H

typedef void* Pointer_t;

typedef struct VectorIterator
{
	Pointer_t m_pObjectPtr;
	struct VectorIterator* m_pPrev;
	struct VectorIterator* m_pNext;
} VectorIterator_t, *VectorIteratorPtr_t;

typedef struct VectorContainer
{
	VectorIteratorPtr_t* m_pElements;
	size_t m_ziTypeSize;
	size_t m_ziSize;
} VectorContainer_t, *VectorContainerPtr_t;

static inline void PushBack(VectorContainerPtr_t vec, Pointer_t obj)
{
	if (vec->m_ziSize == 0)
	{
		VectorIteratorPtr_t it = malloc(sizeof(VectorIterator_t));
		it->m_pPrev = NULL;
		it->m_pNext = NULL;

		it->m_pObjectPtr = malloc(vec->m_ziTypeSize);
		memcpy(it->m_pObjectPtr, obj, vec->m_ziTypeSize);

		vec->m_pElements = malloc(sizeof(Pointer_t) * 2);
		vec->m_pElements[0] = it;
	}
	else
	{
		VectorIteratorPtr_t it = malloc(sizeof(VectorIterator_t));
		it->m_pNext = NULL;
		it->m_pPrev = vec->m_pElements[vec->m_ziSize - 1];

		it->m_pObjectPtr = malloc(vec->m_ziTypeSize);
		memcpy(it->m_pObjectPtr, obj, vec->m_ziTypeSize);

		vec->m_pElements[vec->m_ziSize - 1]->m_pNext = it;

		vec->m_pElements = realloc(vec->m_pElements, sizeof(Pointer_t) * (vec->m_ziSize + 1));
		vec->m_pElements[vec->m_ziSize] = it;
	}

	vec->m_ziSize++;
}

static inline VectorIteratorPtr_t GetElementByID(VectorContainerPtr_t vec, size_t id)
{
#ifdef _DEBUG
	if (id >= vec->m_ziSize) return NULL;
#endif
	return vec->m_pElements[id];
}

static inline void Clear(VectorContainerPtr_t vec)
{
	for (size_t i = 0; i < vec->m_ziSize; i++)
		free(vec->m_pElements[i]);
	free(vec->m_pElements);

	vec->m_ziSize = 0;
}

static inline void* ToPtr(size_t o)
{
	void* ptr = malloc(sizeof(void*));
	memcpy(ptr, &o, sizeof(o));
	return ptr;
}

#endif
