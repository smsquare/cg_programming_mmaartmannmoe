// System.List.h
///////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef NULL
#define NULL 0
#endif

namespace System {
	namespace List {
		template <class T>
		class Node {
		public:
			Node() {
				this->m_pNext = NULL;
				this->m_pPrev = NULL;
				this->m_pData = NULL;
			}

			Node<T> *m_pNext, *m_pPrev;
			T* m_pData;
		};

		template <class T>
		class List {
			Node<T>* m_pCurrent;
			Node<T>* m_pRoot;

		public:

			List() {
				this->m_pCurrent = NULL;
				this->m_pRoot = NULL;
			}

			T* operator[](int nIndex) {
				BeginEnumerate();
				int n = 0;
				for(T* ptr = NULL;ptr = GetNextData(); n++) {
					if(n == nIndex) return ptr;
				}
				return NULL;
			}

			int Length() {
				BeginEnumerate();
				int length = 0;
				for(T* ptr = NULL;ptr = GetNextData();) {
					length++;
				}
				return length;
			}

			void BeginEnumerate() {
				this->m_pCurrent = this->m_pRoot;
			}

			bool HasData() {
				return m_pRoot != NULL;
			}

			T* GetRootData() {
				if(!HasData()) return NULL;
				return m_pRoot->m_pData;
			}

			Node<T>* GetNextNode() {
				Node<T>* pRet = this->m_pCurrent;
				if(this->m_pCurrent != NULL) {
					this->m_pCurrent = this->m_pCurrent->m_pNext;
				}
				return pRet;
			}

			T* GetNextData() {
				Node<T>* pRet = this->m_pCurrent;
				if(this->m_pCurrent != NULL) {
					this->m_pCurrent = this->m_pCurrent->m_pNext;
				}
				return pRet != NULL ? pRet->m_pData : NULL;
			}
		
			void Add(Node<T>* pNode) {
				if(pNode == NULL) return;
				if(this->m_pRoot == NULL) {
					this->m_pRoot = pNode;
				} else {
					Node<T>* pCurr = this->m_pRoot;
					while(pCurr->m_pNext != NULL) {
						pCurr = pCurr->m_pNext;
					}
					pCurr->m_pNext = pNode;
					pNode->m_pPrev = pCurr;
					pNode->m_pNext = NULL;
				}
			}

			void Add(T* pData) {
				Node<T>* pNode = new Node<T>();
				if(pNode == NULL) return;

				pNode->m_pData = pData;
				this->Add(pNode);
			}

			void RemoveAll() {
				Node<T>* pCurr = this->m_pRoot;
				this->m_pRoot = NULL;

				while(pCurr != NULL) {
					Node<T>* pNext = pCurr->m_pNext;
					delete pCurr;
					pCurr = pNext;
				}
			}

			void Remove(Node<T>* pNode) {
				if(pNode == NULL) return;
				Node<T>* pCurr = this->m_pRoot;
				while(pCurr != pNode && pCurr != NULL) {
					pCurr = pCurr->m_pNext;
				}
				if(pCurr == pNode) {
					if(this->m_pCurrent == pCurr) {
						this->m_pCurrent = pCurr->m_pNext;
					}
					if(pCurr->m_pPrev != NULL) {
						pCurr->m_pPrev->m_pNext = pCurr->m_pNext;
					}
					if(pCurr->m_pNext != NULL) {
						pCurr->m_pNext->m_pPrev = pCurr->m_pPrev;
					}
					delete pNode;
				}
			}

			void Remove(T* pData) {
				if(pData == NULL) return;
				Node<T>* pCurr = this->m_pRoot;
				while(pCurr != NULL && pCurr->m_pData != pData) {
					pCurr = pCurr->m_pNext;
				}
				if(pCurr != NULL && pCurr->m_pData == pData) {
					Node<T>* pNode = pCurr;
					if(pCurr == this->m_pRoot) {
						this->m_pRoot = pCurr->m_pNext;
					}
					if(pCurr->m_pPrev != NULL) {
						pCurr->m_pPrev->m_pNext = pCurr->m_pNext;
					}
					if(pCurr->m_pNext != NULL) {
						pCurr->m_pNext->m_pPrev = pCurr->m_pPrev;
					}
					delete pNode;
				}
			}
		};
	}
}