#pragma once

#include "Map.hpp"
#include "stdafx.h"
#include <memory>

namespace ds {
	template<class KeyType, class ValueType>
	class TreeMapImpl : public MapImpl<KeyType, ValueType> {
	public:
		TreeMapImpl() {
			m_root = nul();
		}
		~TreeMapImpl() {
		}
		void insert(const KeyType &key, const ValueType &value) {
			insert(m_root, key, value);
		}
		ValueType &find(const KeyType &key) {
			SBTNode::NodePtr nodePtr = find(m_root, key);
			if (nodePtr == nul()) {
				nodePtr = insert(m_root, key, ValueType());
			}
			return nodePtr->value();
		}
	private:
		class SBTNode {
		public:
			typedef std::shared_ptr<SBTNode> NodePtr;
			SBTNode() {
				child[0] = child[1] = nullptr;
				keyPtr = nullptr;
				valuePtr = nullptr;
				size = 1;
			}
			~SBTNode() {
				delete keyPtr;
				delete valuePtr;
			}
			KeyType &key() {
				return *keyPtr;
			}
			ValueType &value() {
				return *valuePtr;
			}

			NodePtr child[2];
			KeyType *keyPtr;
			ValueType *valuePtr;
			uint size;
		};
		typedef typename SBTNode::NodePtr NodePtr;
		NodePtr nul() {
			static NodePtr nul_;
			if (!nul_) {
				nul_ = NodePtr(new SBTNode());
				nul_->child[0] = nul_->child[1] = nul_;
				nul_->size = 0;
			}
			return nul_;
		}
		NodePtr newNode() {
			NodePtr ptr(new SBTNode());
			ptr->child[0] = ptr->child[1] = nul();
			return ptr;
		}
		inline void rotate(NodePtr &t, bool d) {
			NodePtr p = t->child[!d];
			t->child[!d] = p->child[d];
			p->child[d] = t;
			p->size = t->size;
			t->size = t->child[0]->size + t->child[1]->size + 1;
			t = p;
		}
		void maintain(NodePtr &t, bool d) {
			if (t == nul())
				return;
			if (t->child[d]->child[d]->size > t->child[!d]->size)
				rotate(t, !d);
			else if (t->child[d]->child[!d]->size > t->child[!d]->size) {
				rotate(t->child[d], d);
				rotate(t, !d);
			} else
				return;
			maintain(t->child[0], 0);
			maintain(t->child[1], 1);
			maintain(t, 0);
			maintain(t, 1);
		}
		NodePtr insert(NodePtr &t, const KeyType &key, const ValueType &value) {
			if (t == nul()) {
				t = newNode();
				t->keyPtr = new KeyType(key);
				t->valuePtr = new ValueType(value);
				return t;
			} else {
				t->size++;
				NodePtr res = insert(t->child[!(key < t->key())], key, value);
				maintain(t, !(key < t->key()));
				return res;
			}
		}
		NodePtr find(NodePtr root, const KeyType &key) {
			NodePtr now = root;
			while (true) {
				if (now == nul())
					return now;
				if (now->key() == key) 
					return now;
				now = now->child[key >= now->key()];
			}
		}
		NodePtr m_root;
	};
}